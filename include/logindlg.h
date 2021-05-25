#ifndef CLOGINDLG_H
#define CLOGINDLG_H

#include <QWidget>
#include "basedlg.h"

class CLoginDlg : public CBaseDlg
{
    Q_OBJECT
public:
    explicit CLoginDlg(QWidget *parent = 0);

private:
    void CreateAllChildWnd();
    void InitCtrl();
    void InitSolts();
    void Relayout();

signals:
    void SignalLoginFinish();

public slots:
    void OnLoginFinish();
    void OnLoging();
    void OnBtnCloseClicked();

private:
    QLabel *m_labCompany;
    QLabel *m_labUserIcon;
    QLabel *m_labUserName;
    QLabel *m_labTip;
    CPushButtonEx *m_btnCfg;

    QLabel *m_labQRcode;
};

#endif // CLOGINDLG_H
