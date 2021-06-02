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

    p->setRenderHint(QPainter::Antialiasing);

    // 原点、比例转换
    p->translate(rcClock.left() + rcClock.width() / 2, rcClock.top() + rcClock.height() / 2);

    int side = qMin(rcClock.width(), rcClock.height());
    p->scale(side / 200.0, side / 200.0);       // 画面比例为200*200 相当于下面的绘制都基于200*200

    // 绘制背景
    QRect rcBg(-95, -95, 190, 190);
    QLinearGradient batteryGradient(QPointF(-95, -95), QPointF(190, 190));
    batteryGradient.setColorAt(0.0, QColor(50, 205, 51));
    batteryGradient.setColorAt(1.0, QColor("#5BB3E3"));
    p->setPen(Qt::NoPen);
    p->setBrush(batteryGradient);
    p->drawRoundedRect(rcBg, 10, 10);

    QTime time = QTime::currentTime();
    int nMs = time.second() * 1000 + time.msec();

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
