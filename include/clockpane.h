#ifndef CCLOCKPANE_H
#define CCLOCKPANE_H

#include <QWidget>

class CClockPane : public QWidget
{
    Q_OBJECT
public:
    explicit CClockPane(QWidget *parent = 0);

protected:
    void paintEvent(QPaintEvent *);

private:
    void DrawClock(QPainter *p, QRect rcClock);

private:
    QTimer *m_pUpdateTimer;
};

#endif // CCLOCKPANE_H
