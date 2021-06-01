#include "weatherpane.h"
#include <QPainter>
#include <QDebug>
#include <QDate>
#include <QJsonObject>
#include <QJsonParseError>
#include <QJsonArray>
#include "public.h"
#include "msgqueue.h"
#include "iconhelper.h"



// 目前代码存在很多魔数，皆为示意编码，实际编码请按规范书写，避免魔数

CWeatherPane::CWeatherPane(QWidget *parent) : QWidget(parent)
{
    m_nCurTemperature = 20;
    m_nImageRotate = 0;
    m_pUpdateTimer = new QTimer(this);
    m_pUpdateWeatherTimer = new QTimer(this);
    m_pUpdateWeatherTimer->start(10 * 60 * 1000);

    for (int i = 1; i < 13; i++)
    {
        m_apixWeather[i - 1].load(QString(":/qss/res/img/weather/%1.png").arg(i));
    }

    connect(MSGQUEUE, SIGNAL(SignalRecvMsg(QByteArray, QObject *)), this, SLOT(OnRecvMsg(QByteArray, QObject *)));
    connect(m_pUpdateTimer, SIGNAL(timeout()), this, SLOT(OnTimerUpdateTimeOut()));
    connect(m_pUpdateWeatherTimer, SIGNAL(timeout()), this, SLOT(OnTimerUpdateWeatherTimeOut()));

    UpdateWeather();
}

void CWeatherPane::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);         // 创建画家对象

//    painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform | QPainter::TextAntialiasing, true); // 抗锯齿和使用平滑转换算法

//    QRect rcClient = rect();
//    rcClient.marginsRemoved(QMargins(20, 20, 20, 20));

//    int nSapce = 10;
//    int nItemW = (rcClient.width() - 60) / 3;
//    int nItemH = rcClient.height() / 4 - 2;

//    QFont ft = painter.font();



//    painter.save();

//    QLinearGradient batteryGradient(QPointF(0, 0), QPointF(0, height()));
//    QColor normalColorStart = QColor("#49A0B3");
//    QColor normalColorEnd = QColor("#3BABB9");
//    batteryGradient.setColorAt(0.0, normalColorStart);
//    batteryGradient.setColorAt(1.0, normalColorEnd);

//    QRect rectMain(rcClient);
//    rectMain.setLeft(rectMain.left() + 50);
//    rectMain.setRight(rectMain.right() - 50);
//    rectMain.setTop(rcClient.top() + 20);
//    rectMain.setBottom(rectMain.top() + 2 * nItemH - 20);

//    painter.setPen(Qt::NoPen);
//    painter.setBrush(batteryGradient);
//    painter.drawRoundedRect(rectMain, 10, 10);

//    painter.restore();

//    painter.save();

//    QRect rectCity(rectMain);
//    rectCity.setLeft(rectCity.left() + 20);
//    rectCity.setTop(rectCity.top() + 20);

//    QFont ftTemp = ft;
//    ftTemp.setPointSize(25);
//    painter.setFont(ftTemp);
//    painter.setPen(QColor("#FFFFFF"));
//    painter.drawText(rectCity, Qt::AlignTop | Qt::AlignLeft, "上海");
//    painter.setFont(ft);

//    painter.restore();


//    painter.save();

//    QRect rectIcon(rectMain);

//    ftTemp = IconHelper::GetFont();
//    ftTemp.setPointSize(50);
//    painter.setFont(ftTemp);
//    painter.setPen(QColor("#FFFFFF"));
//    painter.drawText(rectIcon, Qt::AlignCenter, QChar(0xe663));
//    painter.setFont(ft);

//    painter.restore();

    int nBottom = DrawWeather(&painter);
    DrawWeatherForecast(&painter, nBottom);
}

void CWeatherPane::OnRecvMsg(QByteArray strMsg, QObject *obj)
{
    if (obj != this)
        return;

    QDate current_date = QDate::currentDate();

    QJsonParseError jsonError;
    QJsonDocument doucment = QJsonDocument::fromJson(strMsg, &jsonError);
    if (!doucment.isNull() && (jsonError.error == QJsonParseError::NoError))
    {
        if (doucment.isObject())
        {
            QJsonObject object = doucment.object();
            if (object.contains("status"))
            {
                QJsonValue status = object.value("status");
                int nStatus = status.toInt();
                if (nStatus != 1000)
                    return;
            }

            if (object.contains("data"))
            {
                QJsonValue data = object.value("data");
                QJsonObject dataObj = data.toObject();
                if(dataObj.contains("yesterday"))
                {
                    QJsonValue yesterday = dataObj.value("yesterday");
                    QJsonObject yesterdayObj = yesterday.toObject();

                    QString strDate = yesterdayObj.take("date").toString();
                    QString strHigh = yesterdayObj.take("high").toString();
                    QString strLow = yesterdayObj.take("low").toString();
                    QString strType = yesterdayObj.take("type").toString();
                    QString strFengxiang = yesterdayObj.take("fengxiang").toString();

                    QStringList strList = strDate.split("日");
                    int nDate = strList.at(0).toInt();
                    if (nDate > current_date.day())
                        m_atDayWeather[0].strDate = QString("%1月%2日").arg(current_date.month() - 1).arg(nDate);
                    else
                        m_atDayWeather[0].strDate = QString("%1月%2日").arg(current_date.month()).arg(nDate);

                    m_atDayWeather[0].strWeek = strList.at(1);
                    m_atDayWeather[0].strTemperRange = QString("%1~%2℃").arg(strLow.split(" ").at(1)).arg(strHigh.split(" ").at(1));
                    m_atDayWeather[0].strType = strType;
                    m_atDayWeather[0].strWind = strFengxiang;
                }

                if(dataObj.contains("forecast"))
                {
                    QJsonValue forecast = dataObj.value("forecast");
                    if (forecast.isArray())
                    {
                        QJsonArray arrForecast = forecast.toArray();
                        for (int i = 0; i < arrForecast.size() && i < 5; i++)
                        {
                            QJsonValue data = arrForecast.at(i);

                            if (data.isObject())
                            {
                                QJsonObject dayObj = data.toObject();

                                QString strDate = dayObj.take("date").toString();
                                QString strHigh = dayObj.take("high").toString();
                                QString strLow = dayObj.take("low").toString();
                                QString strType = dayObj.take("type").toString();
                                QString strFengxiang = dayObj.take("fengxiang").toString();

                                QStringList strList = strDate.split("日");
                                int nDate = strList.at(0).toInt();
                                m_atDayWeather[i + 1].strDate = QString("%1月%2日").arg(current_date.month()).arg(nDate);
                                m_atDayWeather[i + 1].strWeek = strList.at(1);
                                m_atDayWeather[i + 1].strTemperRange = QString("%1~%2℃").arg(strLow.split(" ").at(1)).arg(strHigh.split(" ").at(1));
                                m_atDayWeather[i + 1].strType = strType;
                                m_atDayWeather[i + 1].strWind = strFengxiang;
                            }
                        }
                    }
                }

                if(dataObj.contains("wendu"))
                {
                    QJsonValue wendu = dataObj.value("wendu");
                    m_nCurTemperature = wendu.toString().toInt();
                }
            }
        }
    }

    update();

    QTimer::singleShot(1000, this, [&]()
    {
        m_pUpdateTimer->stop();
        update();
    });


}

void CWeatherPane::OnMainTabChange(EMainTabTitle eMainTabTitle)
{
    if (TABTITLE_CALENDAR == eMainTabTitle)
        UpdateWeather();
}

void CWeatherPane::OnTimerUpdateTimeOut()
{
    m_nImageRotate += 45;
    if(m_nImageRotate == 360)
        m_nImageRotate = 0;

    update();
}

void CWeatherPane::OnTimerUpdateWeatherTimeOut()
{
    UpdateWeather();
}

void CWeatherPane::UpdateWeather()
{
    m_pUpdateTimer->start(80);

    TMsgItem item;
    item.strUrl = QString("http://wthrcdn.etouch.cn/weather_mini?city=上海");
    item.pObj = this;
    MSGQUEUE->Push(item);
}

QPixmap CWeatherPane::GetPixByType( QString strType )
{
    if (strType.contains("阴"))
        return m_apixWeather[10];

    if (strType.contains("多云"))
        return m_apixWeather[0];

    if (strType.contains("小雨"))
        return m_apixWeather[6];

    if (strType.contains("晴"))
        return m_apixWeather[1];

    if (strType.contains("雷"))
        return m_apixWeather[4];

    if (strType.contains("雨"))
        return m_apixWeather[3];

    return m_apixWeather[0];
}

int CWeatherPane::DrawWeather(QPainter *painter)
{
    TDayWeather tDayWeather = m_atDayWeather[1];
    QDate current_date = QDate::currentDate();

    painter->save();

    painter->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform | QPainter::TextAntialiasing, true); // 抗锯齿和使用平滑转换算法

    QRect rcClient = rect();
    rcClient.marginsRemoved(QMargins(20, 20, 20, 20));

    int nSapce = 10;
    int nItemW = (rcClient.width() - 60) / 3;
    int nItemH = rcClient.height() / 4 - 2;

    QFont ft = painter->font();

    double fRadio = 500.0 / 220.0;
    double fMainRadio = 800.0 / 500.0;

    int nMainWidth = rcClient.width() / fMainRadio;

    QRect rectMain(rcClient);
    rectMain.setLeft(rectMain.left() + (rcClient.width() - nMainWidth) / 2);
    rectMain.setRight(rectMain.right() - (rcClient.width() - nMainWidth) / 2);
    rectMain.setTop(rcClient.top() + 20);
    rectMain.setBottom(rectMain.top() + rectMain.width() / fRadio);

    painter->translate(rectMain.left(), rectMain.top());  // 移动绘制原点

    painter->scale(rectMain.width() / 500.0, rectMain.height() / 220.0);       // 700*300 相当于下面的绘制都基于700*300

    QRect rectBase(0, 0, 500.0, 220.0);

    painter->save();

    QLinearGradient batteryGradient(QPointF(0, 0), QPointF(0, rectBase.height()));
    QColor normalColorStart = QColor("#49A0B3");
    QColor normalColorEnd = QColor("#3BABB9");
    batteryGradient.setColorAt(0.0, normalColorStart);
    batteryGradient.setColorAt(1.0, normalColorEnd);

    painter->setPen(Qt::NoPen);
    painter->setBrush(batteryGradient);
    painter->drawRoundedRect(rectBase, 10, 10);
    painter->restore();

    painter->save();

    QRect rectCity(20, 20, 180, 70);
    QFont ftTemp = ft;
    ftTemp.setPointSize(25);
    painter->setFont(ftTemp);
    painter->setPen(QColor("#FFFFFF"));
    painter->drawText(rectCity, Qt::AlignTop | Qt::AlignLeft, "上海");
    painter->setFont(ft);

    painter->restore();

    painter->save();
    QRect rectIcon(170, 40, 160, 160);
    ftTemp = IconHelper::GetFont();
    ftTemp.setPixelSize(160);
    painter->setFont(ftTemp);
    painter->setPen(QColor("#FFFFFF"));
    painter->drawText(rectIcon, Qt::AlignCenter, QChar(0xe663));
    painter->setFont(ft);
    painter->restore();

    painter->save();
    QRect rectWeek(20, 70, 90, 40);
    ftTemp = ft;
    ftTemp.setPointSize(18);
    painter->setPen(QColor("#FFFFFF"));
    painter->drawText(rectWeek, Qt::AlignTop | Qt::AlignLeft, tDayWeather.strWeek);

    QRect rectDate(20, 90, 90, 40);
    painter->setPen(QColor("#FFFFFF"));
    painter->drawText(rectDate, Qt::AlignTop | Qt::AlignLeft, QString("%1/%2/%3").arg(current_date.day()).arg(current_date.month()).arg(current_date.year()));

    QRect rectWind(45, 110, 100, 40);
    painter->setPen(QColor("#FFFFFF"));
    painter->drawText(rectWind, Qt::AlignTop | Qt::AlignLeft, tDayWeather.strWind);
    painter->setFont(ft);
    painter->restore();

    painter->save();
    QRect rectWindIcon(20, 107, 30, 30);
    ftTemp = IconHelper::GetFont();
    ftTemp.setPixelSize(20);
    painter->setFont(ftTemp);
    painter->setPen(QColor("#FFFFFF"));
    painter->drawText(rectWindIcon, Qt::AlignTop | Qt::AlignLeft, QChar(0xe9be));
    painter->setFont(ft);
    painter->restore();

    painter->save();
    QRect rectTemperature(340, 20, 120, 120);
    ftTemp = ft;
    ftTemp.setPixelSize(70);
    ftTemp.setBold(true);
    painter->setFont(ftTemp);
    painter->setPen(QColor("#FFFFFF"));
    painter->drawText(rectTemperature, Qt::AlignCenter, QString("%1°").arg(m_nCurTemperature));
    painter->setFont(ft);
    painter->restore();

    if (m_pUpdateTimer->isActive())
    {
        painter->save();
        QRect rectUpdateIcon(460, 20, 30, 30);
        ftTemp = IconHelper::GetFont();
        ftTemp.setPixelSize(20);
        painter->setFont(ftTemp);
        painter->setPen(QColor("#FFFFFF"));

        /* 设定旋转中心点 */
        painter->translate(rectUpdateIcon.center());
        /* 旋转的角度 */
        painter->rotate(m_nImageRotate);

        painter->drawText(QRect(-15, -15, 30, 30), Qt::AlignCenter/* | Qt::AlignLeft*/, QChar(0xe69a));
        /* 恢复中心点 */
        painter->resetTransform();

        painter->setFont(ft);
        painter->restore();
    }

    painter->restore();

    return rectMain.bottom();
}

void CWeatherPane::DrawWeatherForecast(QPainter *painter, int nTop)
{
    QRect rcClient = rect();
    rcClient.marginsRemoved(QMargins(20, 20, 20, 20));

    int nSapce = 10;
    int nItemW = (rcClient.width() - 60) / 3;
    int nItemH = (rcClient.height() - nTop) / 2 - 2;

    QFont ft = painter->font();

    int nDayIndex = 0;
    QRect rcItem;
    for (int j = 0; j < 2; j++)
    {
        rcItem = QRect();
        rcItem.setTop(rcItem.top() + j * nItemH + nSapce + nTop);

        for (int i = 0; i < 3; i++)
        {
            TDayWeather tDayWeather = m_atDayWeather[nDayIndex];

            rcItem.setLeft(rcItem.right() + nSapce);
            rcItem.setRight(rcItem.left() + nItemW);
            rcItem.setBottom(rcItem.top() + nItemH);

            painter->save();
            QRect rcWeek(rcItem);
            rcWeek.setBottom(rcItem.top() + 40);
            painter->setPen(QColor(5, 167, 17));
            QFont ftTemp = ft;
            ftTemp.setPointSize(15);
            painter->setFont(ftTemp);
            QString strWeek = tDayWeather.strWeek;
            if (0 == nDayIndex)
                strWeek = tr("昨天");
            else if (1 == nDayIndex)
                strWeek = tr("今天");
            else if (2 == nDayIndex)
                strWeek = tr("明天");

            painter->drawText(rcWeek, Qt::AlignHCenter | Qt::AlignBottom, strWeek);
            painter->setFont(ft);
            painter->restore();

            painter->save();
            QRect rcDate(rcItem);
            rcDate.setTop(rcWeek.bottom() + 2);
            rcDate.setBottom(rcWeek.bottom() + 25);
            painter->setPen(QColor(5, 167, 17));
            painter->setFont(ft);
            painter->drawText(rcDate, Qt::AlignHCenter | Qt::AlignBottom, tDayWeather.strDate);
            painter->restore();

            QRect rcImg(rcItem);
            rcImg.setTop(rcDate.bottom() + 2);
            rcImg.setBottom(rcImg.top() + rcItem.height() - 135);
            rcImg.setLeft(rcImg.left() + (rcImg.width() - rcImg.height()) / 2);
            rcImg.setRight(rcImg.left() + rcImg.height());

            QPixmap p = GetPixByType(tDayWeather.strType).scaled(rcImg.size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
            painter->drawPixmap(rcImg, p);

            painter->save();
            QRect rcWeather(rcItem);
            rcWeather.setTop(rcImg.bottom() + 2);
            rcWeather.setBottom(rcWeather.top() + 25);
            painter->setPen(QColor(5, 167, 17));
            painter->setFont(ft);
            painter->drawText(rcWeather, Qt::AlignHCenter | Qt::AlignBottom, tDayWeather.strType);
            painter->restore();

            painter->save();
            QRect rcTemperature(rcItem);
            rcTemperature.setTop(rcWeather.bottom() + 2);
            rcTemperature.setBottom(rcTemperature.top() + 25);
            painter->setPen(QColor(5, 167, 17));
            painter->setFont(ft);
            painter->drawText(rcTemperature, Qt::AlignHCenter | Qt::AlignBottom, tDayWeather.strTemperRange);
            painter->restore();

            if (i < 2)
            {
                painter->save();
                painter->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform | QPainter::TextAntialiasing, false); // 抗锯齿和使用平滑转换算法
                QPen tmp(QColor("#DBDBDB"));
                tmp.setWidth(1);
                QVector<qreal>dashes;
                qreal space = 4;
                dashes << 3 << space << 3 << space << 3 << space << 3 << space << 3 << space;
                tmp.setDashPattern(dashes);
                painter->setPen(tmp);
                painter->drawLine(rcItem.right() + nSapce /2, rcItem.top() + nSapce, rcItem.right() + nSapce /2, rcItem.bottom() - nSapce);
                painter->restore();
            }

            if (nDayIndex < 5)
                nDayIndex++;
        }

        if (j < 1)
        {
            painter->save();
            painter->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform | QPainter::TextAntialiasing, false); // 抗锯齿和使用平滑转换算法
            QPen tmp(QColor("#DBDBDB"));
            tmp.setWidth(1);
            QVector<qreal>dashes;
            qreal space = 4;
            dashes << 3 << space << 3 << space << 3 << space << 3 << space << 3 << space;
            tmp.setDashPattern(dashes);
            painter->setPen(tmp);
            painter->drawLine(rcClient.left() + nSapce, rcItem.bottom() + nSapce / 5, rcItem.right(), rcItem.bottom() + nSapce / 5);
            painter->restore();
        }
    }
}
