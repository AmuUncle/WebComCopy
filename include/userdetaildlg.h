#ifndef CUSERDETAILDLG_H
#define CUSERDETAILDLG_H

#include <QWidget>
#include <QtWidgets>

class CPushButtonEx;

class CUserDetailDlg : public QWidget
{
    Q_OBJECT
public:
    explicit CUserDetailDlg(QWidget *parent = 0);

private:
    void CreateAllChildWnd();
    void InitCtrl();
    void Relayout();

private:
    QWidget *m_widgetTop;
    CPushButtonEx *m_btnUserIcon;
    QLabel *m_labUserName;
    QLabel *m_labSex;

    QLabel *m_labSeparatorLine;

    QLabel *m_labTel;
    QLabel *m_labTelValue;
    QLabel *m_labMail;
    QLabel *m_labMailValue;
    QLabel *m_labDepartment;
    QLabel *m_labDepartmentValue;

    CPushButtonEx *m_btnSendMsg;
};

#endif // CUSERDETAILDLG_H
