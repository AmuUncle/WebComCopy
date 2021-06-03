#include "clockpane.h"
#include <QPainter>
#include <QTime>
#include <QTimer>


CClockPane::CClockPane(QWidget *parent) : QWidget(parent)
{
    m_pUpdateTimer = new QTimer(this);
    connect(m_pUpdateTimer, SIGNAL(timeout()), this, SLOT(update()));
    m_pUpdateTimer->start(100);
}

void CClockPane::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);

    DrawClock(&painter, rect());
}

void CClockPane::DrawClock(QPainter *p, QRect rcClock)
{
    p->save();

    QTime time = QTime::currentTime();
    int nMs = time.second() * 1000 + time.msec();

    p->setRenderHint(QPainter::Antialiasing);

    // 原点、比例转换
    p->translate(rcClock.left() + rcClock.width() / 2, rcClock.top() + rcClock.height() / 2);

    int side = qMin(rcClock.width(), rcClock.height());
    p->scale(side / 200.0, side / 200.0);       // 画面比例为200*200 相当于下面的绘制都基于200*200

    // 绘制背景
    QRect rcBg(-95, -95, 190, 190);
    QLinearGradient batteryGradient(QPointF(-95, -95), QPointF(190, 190));

    if (time.second() < 10)
    {
        batteryGradient.setColorAt(0.0, QColor(QString("#FF9A9E")));
        batteryGradient.setColorAt(1.0, QColor(QString("#FAD0C4")));
    }
    else if (time.second() < 20)
    {
        batteryGradient.setColorAt(0.0, QColor(QString("#F2ECD2")));
        batteryGradient.setColorAt(1.0, QColor(QString("#FCB69F")));
    }
    else if (time.second() < 30)
    {
        batteryGradient.setColorAt(0.0, QColor(QString("#FF9A9E")));
        batteryGradient.setColorAt(1.0, QColor(QString("#FECFEF")));
    }
    else if (time.second() < 40)
    {
        batteryGradient.setColorAt(0.0, QColor(QString("#CFD9DF")));
        batteryGradient.setColorAt(1.0, QColor(QString("#E2EBF0")));
    }
    else if (time.second() < 50)
    {
        batteryGradient.setColorAt(0.0, QColor(QString("#66FEEA")));
        batteryGradient.setColorAt(1.0, QColor(QString("#764BA2")));
    }
    else if (time.second() < 60)
    {
        batteryGradient.setColorAt(0.0, QColor(QString("#FDFCFB")));
        batteryGradient.setColorAt(1.0, QColor(QString("#E2D1C3")));
    }
    else
    {
        batteryGradient.setColorAt(0.0, QColor(QString("#A1C4FD")));
        batteryGradient.setColorAt(1.0, QColor(QString("#C2E9FB")));
    }

    p->setPen(Qt::NoPen);
    p->setBrush(batteryGradient);
    p->drawRoundedRect(rcBg, 10, 10);

    // 绘制刻度
    p->save();
    p->setPen(Qt::NoPen);
    p->setPen(QColor(255, 255, 255));
    int nCur = 0;
    for (int j = 0; j < 120; ++j)
    {
        p->drawLine(0, -70, 0, -80);

        if ( 0 == nCur && j * 500 < nMs && (j + 1) * 500 > nMs)
            nCur = j;

        p->rotate(3.0);
    }
    p->restore();

    // 绘制当前时间波形
    p->save();
    const int nRange = 6;

    p->setPen(Qt::NoPen);
    p->setPen(QColor(255, 255, 255));
    p->rotate(3.0 * (nCur - nRange));

    int nLastLen = 10;
    for (int j = 0; j <= nRange; ++j)
    {
        p->drawLine(0, -80, 0, -80 - (++nLastLen - 10));
        p->rotate(3.0);
    }

    for (int j = 0; j < nRange; ++j)
    {
        p->drawLine(0, -80, 0, -80 - (--nLastLen  - 10));
        p->rotate(3.0);
    }
    p->restore();

    // 绘制小红点
    p->save();
    p->setPen(Qt::NoPen);
    p->setBrush(QColor("#E82B00"));
    p->rotate(1.0 * (nMs / (1.0 / 6.0 * 1000)));
    p->drawEllipse(QPointF(0, -62), 4, 4);
    p->restore();

    // 绘制时间文字
    p->save();
    QFont ft = p->font();
    QFont ftTmp = ft;
    ftTmp.setPointSize(30);
    p->setFont(ftTmp);
    p->setPen(QColor("#FFFFFF"));
    p->drawText(QRect(-70, -70, 140, 140), Qt::AlignCenter, time.toString("hh:mm"));
    p->restore();

    p->restore();
}
