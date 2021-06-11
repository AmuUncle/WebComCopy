#include "navpane.h"
#include "pushbuttonex.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include "iconhelper.h"
#include "userdetaildlg.h"
#include <QDebug>


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

    //QSize sizeBtn(50, 50);
    int sizeBtn = 50;
    m_btnMsg->setFixedHeight(sizeBtn);
    m_btnContacts->setFixedHeight(sizeBtn);
    m_btnCalendar->setFixedHeight(sizeBtn);
    m_btnWorkspace->setFixedHeight(sizeBtn);
    m_btnWeDoc->setFixedHeight(sizeBtn);
    m_btnWeDrive->setFixedHeight(sizeBtn);
    m_btnMeeting->setFixedHeight(sizeBtn);
    m_btnMore->setFixedHeight(sizeBtn);

    m_btnUserIcon->setIcon(QIcon(":/qss/res/usricon.jpeg"));
    m_btnUserIcon->setIconSize(m_btnUserIcon->size());

    IconHelper::SetIcon(m_btnMsg, QChar(0xe645));
    IconHelper::SetIcon(m_btnContacts, QChar(0xe63a));
    IconHelper::SetIcon(m_btnCalendar, QChar(0xe603), 24);
    IconHelper::SetIcon(m_btnWorkspace, QChar(0xe6a9));
    IconHelper::SetIcon(m_btnWeDoc, QChar(0xe670));
    IconHelper::SetIcon(m_btnWeDrive, QChar(0xe663));
    IconHelper::SetIcon(m_btnMeeting, QChar(0xe673));
    IconHelper::SetIcon(m_btnMore, QChar(0xe642));

    m_labSeparatorLine->setFixedHeight(1);
    m_labSeparatorLine->setStyleSheet("background-color:#4A7ABA");
    m_pUserDetail->hide();

    // 初始化tab
    QSignalMapper *pSignalMapperPushed = new QSignalMapper(this);
    pSignalMapperPushed->setMapping(m_btnMsg, TABTITLE_MESSAGE);
    pSignalMapperPushed->setMapping(m_btnContacts, TABTITLE_CONTACTS);
    pSignalMapperPushed->setMapping(m_btnCalendar, TABTITLE_CALENDAR);
    pSignalMapperPushed->setMapping(m_btnWorkspace, TABTITLE_WORKSPACE);
    pSignalMapperPushed->setMapping(m_btnWeDoc, TABTITLE_WEDOC);
    pSignalMapperPushed->setMapping(m_btnWeDrive, TABTITLE_WEDRIVE);
    pSignalMapperPushed->setMapping(m_btnMeeting, TABTITLE_MEETING);

    QList<CPushButtonEx *> listBtns = findChildren<CPushButtonEx *>();
    foreach (QPushButton *btn, listBtns)
    {
        if (btn != m_btnUserIcon)
            connect(btn, SIGNAL(clicked()), pSignalMapperPushed, SLOT(map()));
    }

    connect(pSignalMapperPushed, SIGNAL(mapped(int)), this, SLOT(OnSignalPushedMapped(int)));

    m_btnMsg->setCheckable(true);
    m_btnContacts->setCheckable(true);
    m_btnCalendar->setCheckable(true);
    m_btnWorkspace->setCheckable(true);
    m_btnWeDoc->setCheckable(true);
    m_btnWeDrive->setCheckable(true);
    m_btnMeeting->setCheckable(true);
}

void NavPane::InitSolts()
{
    connect(m_btnUserIcon, SIGNAL(clicked()), this, SLOT(OnBtnUserIconClicked()));
    connect(m_btnMore, SIGNAL(clicked()), this, SLOT(OnBtnMoreClicked()));
}

void NavPane::Relayout()
{
    QHBoxLayout *layoutUserIcon = new QHBoxLayout();
    layoutUserIcon->addWidget(m_btnUserIcon);
    layoutUserIcon->setContentsMargins(10, 28, 16, 18);

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
    layoutMain->setContentsMargins(1, 1, 1, 1);
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

void NavPane::OnSignalPushedMapped(int nCmd)
{
    emit SignalTabChange(EMainTabTitle(nCmd));
}

void NavPane::OnMainTabChange(EMainTabTitle eMainTabTitle)
{
    m_btnMsg->setChecked(false);
    m_btnContacts->setChecked(false);
    m_btnCalendar->setChecked(false);
    m_btnWorkspace->setChecked(false);
    m_btnWeDoc->setChecked(false);
    m_btnWeDrive->setChecked(false);
    m_btnMeeting->setChecked(false);

    switch (eMainTabTitle)
    {
    case TABTITLE_MESSAGE:
        {
            m_btnMsg->setChecked(true);
        }
        break;

    case TABTITLE_CONTACTS:
        {
            m_btnContacts->setChecked(true);
        }
        break;

    case TABTITLE_CALENDAR:
        {
            m_btnCalendar->setChecked(true);
        }
        break;

    case TABTITLE_WORKSPACE:
        {
            m_btnWorkspace->setChecked(true);
        }
        break;

    case TABTITLE_WEDOC:
        {
            m_btnWeDoc->setChecked(true);
        }
        break;

    case TABTITLE_WEDRIVE:
        {
            m_btnWeDrive->setChecked(true);
        }
        break;

    case TABTITLE_MEETING:
        {
            m_btnMeeting->setChecked(true);
        }
        break;
    }
}

void NavPane::OnBtnMoreClicked()
{
    //创建菜单对象
    QMenu *pMenu = new QMenu();

    QAction *pCollect = new QAction(tr("收藏"), pMenu);
    QAction *pMsgMgr = new QAction(tr("消息管理器"), pMenu);
    QAction *pInvite = new QAction(tr("邀请同事加入"), pMenu);
    QAction *pSign = new QAction(tr("工作签名"), pMenu);

    QAction *pRest = new QAction(tr("休息一下"), pMenu);
    QAction *pGoOffwork = new QAction(tr("下班了"), pMenu);

    QMenu *pChildRest = new QMenu(pMenu);
    pChildRest->setTitle(tr("休息一下"));
    pChildRest->addAction(pRest);
    pChildRest->addAction(pGoOffwork);

    QAction *pSetting = new QAction(tr("设置"), pMenu);
    QAction *pAbout = new QAction(tr("关于"), pMenu);
    QAction *pFeedback = new QAction(tr("吐个槽"), pMenu);

    //把QAction对象添加到菜单上
    pMenu->addAction(pCollect);
    pMenu->addAction(pMsgMgr);
    pMenu->addSeparator();//添加分割线
    pMenu->addAction(pInvite);
    pMenu->addSeparator();//添加分割线
    pMenu->addAction(pSign);
    pMenu->addMenu(pChildRest);
    pMenu->addSeparator();//添加分割线
    pMenu->addAction(pSetting);
    pMenu->addAction(pAbout);
    pMenu->addSeparator();//添加分割线
    pMenu->addAction(pFeedback);

    connect(pMenu, SIGNAL(triggered(QAction*)), this, SLOT(OnMenuTriggered(QAction*)));

    QPoint ptMenu = mapToGlobal(pos());
    ptMenu.setX(ptMenu.x() + width());
    ptMenu.setY(ptMenu.y() + height());
    ptMenu.setY(ptMenu.y() - 252);
    pMenu->exec(ptMenu);

    //释放内存
    QList<QAction*> list = pMenu->actions();
    foreach (QAction* pAction, list)
        delete pAction;

    delete pMenu;
}

void NavPane::OnMenuTriggered(QAction *action)
{

}
