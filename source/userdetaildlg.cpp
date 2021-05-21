#include "userdetaildlg.h"
#include "pushbuttonex.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include "iconhelper.h"

#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif

CUserDetailDlg::CUserDetailDlg(QWidget *parent) : QWidget(parent)
{
    m_widgetTop = NULL;
    m_btnUserIcon = NULL;
    m_labUserName = NULL;
    m_labSex = NULL;

    m_labSeparatorLine = NULL;

    m_labTel = NULL;
    m_labTelValue = NULL;
    m_labMail = NULL;
    m_labMailValue = NULL;
    m_labDepartment = NULL;
    m_labDepartmentValue = NULL;

    m_btnSendMsg = NULL;

    setAttribute(Qt::WA_StyledBackground);  // 禁止父窗口样式影响子控件样式
    setProperty("form", "userdetail");

    CreateAllChildWnd();
    InitCtrl();
    Relayout();
}

void CUserDetailDlg::CreateAllChildWnd()
{
#define NEW_OBJECT(pObj, TYPE) \
    if (NULL == pObj) { pObj = new TYPE(this); }

    NEW_OBJECT(m_widgetTop, QWidget);
    NEW_OBJECT(m_btnUserIcon, CPushButtonEx);
    NEW_OBJECT(m_labUserName, QLabel);
    NEW_OBJECT(m_labSex, QLabel);
    NEW_OBJECT(m_labSeparatorLine, QLabel);
    NEW_OBJECT(m_labTel, QLabel);
    NEW_OBJECT(m_labTelValue, QLabel);
    NEW_OBJECT(m_labMail, QLabel);
    NEW_OBJECT(m_labMailValue, QLabel);
    NEW_OBJECT(m_labDepartment, QLabel);
    NEW_OBJECT(m_labDepartmentValue, QLabel);
    NEW_OBJECT(m_btnSendMsg, CPushButtonEx);
}

void CUserDetailDlg::InitCtrl()
{
    setFixedSize(280, 270);
    setWindowFlags(Qt::Popup);

    m_btnUserIcon->setFixedSize(70, 70);
    m_btnUserIcon->setIcon(QIcon(":/qss/res/usricon.jpeg"));
    m_btnUserIcon->setIconSize(m_btnUserIcon->size());

    m_labSeparatorLine->setFixedHeight(1);
    m_labSeparatorLine->setStyleSheet("background-color:#E5E5E5");

    m_labTel->setProperty("title", "true");
    m_labMail->setProperty("title", "true");
    m_labDepartment->setProperty("title", "true");
    m_labUserName->setProperty("username", "true");
    m_labSex->setProperty("sex", "true");
    m_btnSendMsg->setProperty("sendmsg", "true");

    m_labUserName->setText(tr("逍遥子"));
    m_labTel->setText(tr("手机"));
    m_labTelValue->setText(tr("15088888888"));
    m_labMail->setText(tr("邮箱"));
    m_labMailValue->setText(tr("hudejie2018@163.com"));
    m_labDepartment->setText(tr("部门"));
    m_labDepartmentValue->setText(tr("行业服务部/开发应用组"));

    m_btnSendMsg->setText(tr("发消息"));

    IconHelper::SetIcon(m_labSex, QChar(0xe646), 14);
}

void CUserDetailDlg::Relayout()
{
    QHBoxLayout *layoutMain = new QHBoxLayout();
    layoutMain->addWidget(m_btnUserIcon);
    layoutMain->addWidget(m_labUserName);
    layoutMain->addWidget(m_labSex);
    layoutMain->addStretch();
    layoutMain->setSpacing(6);
    layoutMain->setMargin(0);

    int nIndex = 0;
    QGridLayout *layoutTop = new QGridLayout();
    layoutTop->addLayout(layoutMain, 0, 0, 1, 5);

    nIndex++;
    layoutTop->addWidget(m_labSeparatorLine, nIndex, 0, 1, 5);

    nIndex++;
    layoutTop->addWidget(m_labTel, nIndex, 0, 1, 1);
    layoutTop->addWidget(m_labTelValue, nIndex, 1, 1, 4);

    nIndex++;
    layoutTop->addWidget(m_labMail, nIndex, 0, 1, 1);
    layoutTop->addWidget(m_labMailValue, nIndex, 1, 1, 4);

    nIndex++;
    layoutTop->addWidget(m_labDepartment, nIndex, 0, 1, 1);
    layoutTop->addWidget(m_labDepartmentValue, nIndex, 1, 1, 4);

    nIndex++;
    layoutTop->addWidget(m_btnSendMsg, nIndex, 0, 1, 5);

    layoutTop->setSpacing(6);
    layoutTop->setContentsMargins(20, 20, 20, 20);
    setLayout(layoutTop);
}
