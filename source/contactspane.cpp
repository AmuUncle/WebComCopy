#include "contactspane.h"
#include "friendslist.h"
#include <QVariant>
#include <QHBoxLayout>
#include <QVBoxLayout>

CContactsPane::CContactsPane(QWidget *parent) : QWidget(parent)
{
    m_pFriendsList = NULL;

    CreateAllChildWnd();
    InitCtrl();
    InitSolts();
    Relayout();
}

void CContactsPane::CreateAllChildWnd()
{
#define NEW_OBJECT(pObj, TYPE) \
    if (NULL == pObj) { pObj = new TYPE(this); }

    NEW_OBJECT(m_pFriendsList, CFriendsList);
}

void CContactsPane::InitCtrl()
{
    m_pFriendsList->setFixedWidth(250);
    m_pFriendsList->SetContactMode(true);
}

void CContactsPane::InitSolts()
{

}

void CContactsPane::Relayout()
{
    QHBoxLayout *layoutMain = new QHBoxLayout();
    layoutMain->addWidget(m_pFriendsList);
    layoutMain->addStretch();
    layoutMain->setSpacing(0);
    layoutMain->setMargin(0);

    setLayout(layoutMain);
}
