#ifndef CCHATTOPTOOLBAR_H
#define CCHATTOPTOOLBAR_H

#include <QWidget>
#include <QtWidgets>
#include "public.h"


class CPushButtonEx;
class CUserDetailDlg;

class CChatTopToolbar : public QWidget
{
    Q_OBJECT
public:
    explicit CChatTopToolbar(QWidget *parent = 0);

public slots:
    void OnFriendChange(TUserInfo tUserInfo);

private:
    bool eventFilter(QObject *obj, QEvent *event);

private:
    void CreateAllChildWnd();
    void InitCtrl();
    void Relayout();

private:
    QLabel *m_labUserName;
    QLabel *m_labState;
    QLabel *m_labEmail;
    QLabel *m_labEmailValue;

    QLabel *m_labSeparatorLine;

    QLabel *m_labPart;
    QLabel *m_labPartValue;

    QLabel *m_labSign;
    QLabel *m_labSignValue;

    CPushButtonEx *m_btnAddUser;

    CUserDetailDlg *m_pUserDetail;

    TUserInfo m_tUserInfo;
};

#endif // CCHATTOPTOOLBAR_H
