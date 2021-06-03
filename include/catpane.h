#ifndef CCATPANE_H
#define CCATPANE_H

#include <QWidget>

class CCatPane : public QWidget
{
    Q_OBJECT
public:
    explicit CCatPane(QWidget *parent = 0);

protected:
    void paintEvent(QPaintEvent *);

private:
    void mouseMoveEvent(QMouseEvent *event);

    void DrawCat(QPainter *p, QRect rectMain);

private:
    double m_fXRadio;
    double m_fYRadio;

    QPixmap m_pixCat;
    QPixmap m_pixCatEyeWrite;
    QPixmap m_pixCatEyeBlack;
    QPixmap m_pixCatEyeBg;
};

#endif // CCATPANE_H
