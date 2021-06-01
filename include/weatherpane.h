#ifndef CWEATHERPANE_H
#define CWEATHERPANE_H

#include <QWidget>
#include <QTimer>
#include "public.h"


struct TDayWeather
{
    QString strDate;
    QString strTemperRange;
    QString strType;
    QString strWeek;
    QString strWind;
};

class CWeatherPane : public QWidget
{
    Q_OBJECT

public:
    explicit CWeatherPane(QWidget *parent = 0);


public slots:
    void OnRecvMsg(QByteArray strMsg, QObject *obj);
    void OnMainTabChange(EMainTabTitle eMainTabTitle);
    void OnTimerUpdateTimeOut();
    void OnTimerUpdateWeatherTimeOut();

private:
    void paintEvent(QPaintEvent *event);
    void UpdateWeather();
    QPixmap GetPixByType(QString strType);

    int DrawWeather(QPainter *painter);
    void DrawWeatherForecast(QPainter *painter, int nTop);

private:
    QPixmap m_apixWeather[12];
    TDayWeather m_atDayWeather[6];
    int m_nCurTemperature;
    int m_nImageRotate;
    QTimer *m_pUpdateTimer;
    QTimer *m_pUpdateWeatherTimer;
};

#endif // CWEATHERPANE_H
