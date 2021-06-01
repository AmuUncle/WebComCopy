#ifndef WECOMWND_H
#define WECOMWND_H

#include <QWidget>
#include <QtWidgets>
#include "public.h"

namespace Ui {
class WeComWnd;
}

class NavPane;
class CPushButtonEx;
class CLoginDlg;
class CMsgPane;
class CContactsPane;
class CWeatherPane;


class WeComWnd : public QWidget
{
    Q_OBJECT

public:
    explicit WeComWnd(QWidget *parent = 0);
    ~WeComWnd();

    enum EMenuItem
    {
        MENUITEM_CLOSE              = 1,
        MENUITEM_CHANGE_1S          = 2,
        MENUITEM_CHANGE_2S          = 3,
        MENUITEM_CHANGE_5S          = 4,
        MENUITEM_CHANGE_10S         = 5,
        MENUITEM_CHANGE_30S         = 6,
        MENUITEM_CHANGE_60S         = 7,
        MENUITEM_CHANGE_PAUSE       = 8,
        MENUITEM_RELOAD             = 9,
        MENUITEM_FULLSCREEN         = 10,
        MENUITEM_MODIFYTITLE        = 11,
    };

public:
    void Login();

private:
    void CreateAllChildWnd();
    void InitCtrl();
    void InitSolts();
    void Relayout();
    void ChangePage();
    void UpdateCtrlText();
    void InitTrayIcon();

    void mouseDoubleClickEvent( QMouseEvent *event );
    void paintEvent(QPaintEvent *event);

signals:
    void SignalTabChange(EMainTabTitle eMainTabTitle);

private slots:
    void OnTabChange(EMainTabTitle eMainTabTitle);
    void OnMinWindows();
    void OnMaxWindows();
    void OnClose();
    void OnSystemTrayIconActivated(QSystemTrayIcon::ActivationReason reason);

private:
    Ui::WeComWnd *ui;
    QStackedWidget *m_pStackedWidget;
    NavPane *m_pNavPane;

    QWidget *m_widgetTitle;
    CPushButtonEx *m_btnMin;
    CPushButtonEx *m_btnMax;
    CPushButtonEx *m_btnClose;
    QSystemTrayIcon *m_trayIcon;
    QMenu *m_systemTrayMenu;
    CLoginDlg *m_Logindlg;

    CMsgPane *m_pMsgPane;
    CContactsPane *m_pContactsPane;
    CWeatherPane *m_pWeatherPane;

    EMainTabTitle m_eMainTabTitle;
    bool m_bMaxWindows;
};

#endif // WECOMWND_H
