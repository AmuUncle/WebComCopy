#ifndef NAVPANE_H
#define NAVPANE_H

#include <QWidget>
#include <QtWidgets>
#include "public.h"


class CPushButtonEx;
class CUserDetailDlg;

class NavPane : public QWidget
{
    Q_OBJECT
public:
    explicit NavPane(QWidget *parent = 0);

private:
    void CreateAllChildWnd();
    void InitCtrl();
    void InitSolts();
    void Relayout();

signals:
    void SignalTabChange(EMainTabTitle eMainTabTitle);

public slots:
    void OnBtnUserIconClicked();

private slots:
    void OnSignalPushedMapped(int nCmd);
    void OnMainTabChange(EMainTabTitle eMainTabTitle);
    void OnBtnMoreClicked();
    void OnMenuTriggered(QAction *action);

private:
    CPushButtonEx *m_btnUserIcon;
    CPushButtonEx *m_btnMsg;
    CPushButtonEx *m_btnContacts;
    CPushButtonEx *m_btnCalendar;
    CPushButtonEx *m_btnWorkspace;
    CPushButtonEx *m_btnWeDoc;
    CPushButtonEx *m_btnWeDrive;
    CPushButtonEx *m_btnMeeting;
    CPushButtonEx *m_btnMore;
    QLabel *m_labSeparatorLine;

    CUserDetailDlg *m_pUserDetail;
};

#endif // NAVPANE_H
