#ifndef WECOMWND_H
#define WECOMWND_H

#include <QWidget>
#include <QtWidgets>
#include "public.h"

namespace Ui {
class WeComWnd;
}

class NavPane;

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

private:
    Ui::WeComWnd *ui;
    QStackedWidget *m_pStackedWidget;
    NavPane *m_pNavPane;

    EMainTabTitle m_eMainTabTitle;
};

#endif // WECOMWND_H
