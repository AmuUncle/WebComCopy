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

private:
    void CreateAllChildWnd();
    void InitCtrl();
    void InitSolts();
    void Relayout();
    void ChangePage();
    void UpdateCtrlText();

signals:
    void SignalTabChange(EMainTabTitle eMainTabTitle);

private slots:
    void OnTabChange(EMainTabTitle eMainTabTitle);
    void OnMinWindows();
    void OnMaxWindows();
    void OnClose();

private:
    Ui::WeComWnd *ui;
    QStackedWidget *m_pStackedWidget;
    NavPane *m_pNavPane;

    QWidget *m_widgetTitle;
    CPushButtonEx *m_btnMin;
    CPushButtonEx *m_btnMax;
    CPushButtonEx *m_btnClose;

    EMainTabTitle m_eMainTabTitle;
    bool m_bMaxWindows;
};

#endif // WECOMWND_H
