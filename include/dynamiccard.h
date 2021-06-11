#ifndef CDYNAMICCARD_H
#define CDYNAMICCARD_H

#include <QWidget>
#include <QTimer>

class CCard : public QWidget
{
    Q_OBJECT
public:
    explicit CCard(QWidget *parent = 0);

public:
    void SetValue(int nValue);
    void SetIcon(QChar icon) { m_icon = icon; }
    void SetTitle(QString strTitle) { m_strTitle = strTitle; }
    void SetBgColor(QColor colorBg) { m_colorBg = colorBg; }

private:
    void paintEvent(QPaintEvent *event);
    void resizeEvent(QResizeEvent *event);
    void showEvent(QShowEvent *event);

public slots:
    void OnTimerUpdateTimeOut();

private:
    QTimer *m_pUpdateTimer;

    int m_nValue;
    int m_nCurValue;
    int m_nIndex;

    QChar m_icon;
    QString m_strTitle;
    QColor m_colorBg;
};

class CDynamicCard : public QWidget
{
    Q_OBJECT
public:
    explicit CDynamicCard(QWidget *parent = 0);

public:
    void SetValue(int nValue);
    void SetIcon(QChar icon) { m_pCard->SetIcon(icon); }
    void SetTitle(QString strTitle) { m_pCard->SetTitle(strTitle); }
    void SetBgColor(QColor colorBg) { m_pCard->SetBgColor(colorBg); }


private:
    void CreateAllChildWnd();
    void InitCtrl();
    void InitSolts();
    void Relayout();

private:
    CCard *m_pCard;
};

#endif // CDYNAMICCARD_H
