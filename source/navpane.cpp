#include "navpane.h"
#include "pushbuttonex.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include "iconhelper.h"
#include "userdetaildlg.h"

NavPane::NavPane(QWidget *parent) : QWidget(parent)
{
    m_btnUserIcon = NULL;
    m_btnMsg = NULL;
    m_btnContacts = NULL;
    m_btnCalendar = NULL;
    m_btnWorkspace = NULL;
    m_btnWeDoc = NULL;
    m_btnWeDrive = NULL;
    m_btnMeeting = NULL;
    m_btnMore = NULL;
    m_labSeparatorLine = NULL;
    m_pUserDetail = NULL;

    setAttribute(Qt::WA_StyledBackground);  // 禁止父窗口样式影响子控件样式
    setProperty("form", "nav");

    CreateAllChildWnd();
    InitCtrl();
    InitSolts();
    Relayout();
}

void NavPane::CreateAllChildWnd()
{
#define NEW_OBJECT(pObj, TYPE) \
    if (NULL == pObj) { pObj = new TYPE(this); }

    NEW_OBJECT(m_btnUserIcon, CPushButtonEx);
    NEW_OBJECT(m_btnMsg, CPushButtonEx);
    NEW_OBJECT(m_btnContacts, CPushButtonEx);
    NEW_OBJECT(m_btnCalendar, CPushButtonEx);
    NEW_OBJECT(m_btnWorkspace, CPushButtonEx);
    NEW_OBJECT(m_btnWeDoc, CPushButtonEx);
    NEW_OBJECT(m_btnWeDrive, CPushButtonEx);
    NEW_OBJECT(m_btnMeeting, CPushButtonEx);
    NEW_OBJECT(m_btnMore, CPushButtonEx);
    NEW_OBJECT(m_labSeparatorLine, QLabel);
    NEW_OBJECT(m_pUserDetail, CUserDetailDlg);
}

void NavPane::InitCtrl()
{
    m_btnUserIcon->setFixedSize(35, 35);

    QSize sizeBtn(50, 50);
    m_btnMsg->setFixedSize(sizeBtn);
    m_btnContacts->setFixedSize(sizeBtn);
    m_btnCalendar->setFixedSize(sizeBtn);
    m_btnWorkspace->setFixedSize(sizeBtn);
    m_btnWeDoc->setFixedSize(sizeBtn);
    m_btnWeDrive->setFixedSize(sizeBtn);
    m_btnMeeting->setFixedSize(sizeBtn);
    m_btnMore->setFixedSize(sizeBtn);

    m_btnUserIcon->setIcon(QIcon(":/qss/res/usricon.jpeg"));
    m_btnUserIcon->setIconSize(m_btnUserIcon->size());

    IconHelper::SetIcon(m_btnMsg, QChar(0xe645));
    IconHelper::SetIcon(m_btnContacts, QChar(0xe636));
    IconHelper::SetIcon(m_btnCalendar, QChar(0xe669));
    IconHelper::SetIcon(m_btnWorkspace, QChar(0xe64c));
    IconHelper::SetIcon(m_btnWeDoc, QChar(0xe632));
    IconHelper::SetIcon(m_btnWeDrive, QChar(0xe641));
    IconHelper::SetIcon(m_btnMeeting, QChar(0xe647));
    IconHelper::SetIcon(m_btnMore, QChar(0xe642));

    m_labSeparatorLine->setFixedHeight(1);
    m_labSeparatorLine->setStyleSheet("background-color:#4A7ABA");
    m_pUserDetail->hide();
}

void NavPane::InitSolts()
{
    connect(m_btnUserIcon, SIGNAL(clicked()), this, SLOT(OnBtnUserIconClicked()));
}

void NavPane::Relayout()
{
    QVBoxLayout *layoutUserIcon = new QVBoxLayout();
    layoutUserIcon->addWidget(m_btnUserIcon);
    layoutUserIcon->setContentsMargins(4, 28, 16, 18);

    QVBoxLayout *layoutCenter = new QVBoxLayout();
    layoutCenter->addLayout(layoutUserIcon);
    layoutCenter->addWidget(m_btnMsg);
    layoutCenter->addWidget(m_btnContacts);
    layoutCenter->addWidget(m_btnCalendar);
    layoutCenter->addWidget(m_btnWorkspace);
    layoutCenter->addWidget(m_labSeparatorLine);
    layoutCenter->addWidget(m_btnWeDoc);
    layoutCenter->addWidget(m_btnWeDrive);
    layoutCenter->addWidget(m_btnMeeting);
    layoutCenter->addStretch();
    layoutCenter->addWidget(m_btnMore);

    layoutCenter->setSpacing(0);
    layoutCenter->setMargin(0);

    QHBoxLayout *layoutMain = new QHBoxLayout();
    layoutMain->addStretch();
    layoutMain->addLayout(layoutCenter);
    layoutMain->addStretch();
    layoutMain->setSpacing(0);
    layoutMain->setContentsMargins(6, 1, 6, 1);
    setLayout(layoutMain);
}

void NavPane::OnBtnUserIconClicked()
{
    m_pUserDetail->show();

    QPoint ptBtn = m_btnUserIcon->mapToGlobal(m_btnUserIcon->pos());
    QPoint point(ptBtn);
    point.setX(ptBtn.x() - m_btnUserIcon->pos().x() + m_btnUserIcon->width() + 2);
    point.setY(ptBtn.y() - m_btnUserIcon->pos().y());
    m_pUserDetail->move(point);
}
