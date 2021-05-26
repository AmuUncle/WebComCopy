#include "msgpane.h"
#include "friendslist.h"
#include <QVariant>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include "chattoptoolbar.h"

CMsgPane::CMsgPane(QWidget *parent) : QWidget(parent)
{
    m_pFriendsList = NULL;
    m_pTopToolbar = NULL;

    CreateAllChildWnd();
    InitCtrl();
    InitSolts();
    Relayout();
}

void CMsgPane::CreateAllChildWnd()
{
#define NEW_OBJECT(pObj, TYPE) \
    if (NULL == pObj) { pObj = new TYPE(this); }

    NEW_OBJECT(m_pFriendsList, CFriendsList);
    NEW_OBJECT(m_pTopToolbar, CChatTopToolbar);
}

void CMsgPane::InitCtrl()
{
    setAttribute(Qt::WA_StyledBackground);  // 禁止父窗口样式影响子控件样式
    setProperty("form", "msgpane");

    m_pFriendsList->setFixedWidth(250);
}

void CMsgPane::InitSolts()
{
    connect(m_pFriendsList, SIGNAL(SignalFriendChange(TUserInfo)), m_pTopToolbar, SLOT(OnFriendChange(TUserInfo)));
}

void CMsgPane::Relayout()
{
    QVBoxLayout *layoutRMain = new QVBoxLayout();
    layoutRMain->addWidget(m_pTopToolbar);
    layoutRMain->addStretch();

    QHBoxLayout *layoutMain = new QHBoxLayout();
    layoutMain->addWidget(m_pFriendsList);
    layoutMain->addLayout(layoutRMain);
    layoutMain->setSpacing(0);
    layoutMain->setMargin(0);

    setLayout(layoutMain);
}
