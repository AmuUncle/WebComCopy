#include "msgpane.h"
#include "friendslist.h"
#include <QVariant>
#include <QHBoxLayout>
#include <QVBoxLayout>


CMsgPane::CMsgPane(QWidget *parent) : QWidget(parent)
{
    m_pFriendsList = NULL;


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
}

void CMsgPane::InitCtrl()
{
    setAttribute(Qt::WA_StyledBackground);  // 禁止父窗口样式影响子控件样式
    setProperty("form", "msgpane");

    m_pFriendsList->setFixedWidth(250);
}

void CMsgPane::InitSolts()
{

}

void CMsgPane::Relayout()
{
    QHBoxLayout *layoutMain = new QHBoxLayout();
    layoutMain->addWidget(m_pFriendsList);
    layoutMain->addStretch();
    layoutMain->setSpacing(0);
    layoutMain->setMargin(0);

    setLayout(layoutMain);
}
