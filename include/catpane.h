#ifndef CCATPANE_H
#define CCATPANE_H

#include <QWidget>
#include <QTimer>

class CCatPane : public QWidget
{
    Q_OBJECT
public:
    explicit CCatPane(QWidget *parent = 0);

protected:
    void paintEvent(QPaintEvent *);

private:
    void mouseMoveEvent(QMouseEvent *event);

    void DrawCloud(QPainter *p, QRect rectMain);
    void DrawCat(QPainter *p, QRect rectMain);

public slots:
    void OnTimerCloudTimeOut();

private:
    double m_fXRadio;
    double m_fYRadio;

    QPixmap m_pixCat;
    QPixmap m_pixCatEyeWrite;
    QPixmap m_pixCatEyeBlack;
    QPixmap m_pixCatEyeBg;

    double m_nScaleCloud1;
    double m_nScaleCloud2;
    double m_nScaleCloud3;

    QPixmap m_pixCloud001;
    QPixmap m_pixCloud002;
    QPixmap m_pixCloud003;
    QPixmap m_pixCloud004;
    QPixmap m_pixSun;
    QPixmap m_pixRain;

    QTimer *m_pCloudTimer;
};

#endif // CCATPANE_H
