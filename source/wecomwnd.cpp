#include "wecomwnd.h"
#include "ui_wecomwnd.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include "navpane.h"
#include "pushbuttonex.h"
#include "iconhelper.h"


#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif

WeComWnd::WeComWnd(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WeComWnd)
{
    ui->setupUi(this);

    m_pStackedWidget = NULL;
    m_pNavPane = NULL;
    m_eMainTabTitle = TABTITLE_MESSAGE;

    m_widgetTitle = NULL;
    m_btnMin = NULL;
    m_btnMax = NULL;
    m_btnClose = NULL;

    m_bMaxWindows = false;

    setWindowFlags(windowFlags() | Qt::FramelessWindowHint | Qt::WindowMinMaxButtonsHint);
    setProperty("form", "mainwnd");
    setProperty("canMove", "true");

    CreateAllChildWnd();
    InitCtrl();
    InitSolts();
    Relayout();
    ChangePage();
}

WeComWnd::~WeComWnd()
{
    delete ui;
}

void WeComWnd::CreateAllChildWnd()
{
#define NEW_OBJECT(pObj, TYPE) \
    if (NULL == pObj) { pObj = new TYPE(this); }

    NEW_OBJECT(m_pStackedWidget, QStackedWidget);
    NEW_OBJECT(m_pNavPane, NavPane);
    NEW_OBJECT(m_widgetTitle, QWidget);
    NEW_OBJECT(m_btnMin, CPushButtonEx);
    NEW_OBJECT(m_btnMax, CPushButtonEx);
    NEW_OBJECT(m_btnClose, CPushButtonEx);
}

void WeComWnd::InitCtrl()
{
    m_pNavPane->setFixedWidth(60);

    m_pStackedWidget->insertWidget(TABTITLE_MESSAGE, new QLabel(tr("消息会话")));
    m_pStackedWidget->insertWidget(TABTITLE_CONTACTS, new QLabel(tr("通讯录")));
    m_pStackedWidget->insertWidget(TABTITLE_CALENDAR, new QLabel(tr("日程")));
    m_pStackedWidget->insertWidget(TABTITLE_WORKSPACE, new QLabel(tr("工作台")));
    m_pStackedWidget->insertWidget(TABTITLE_WEDOC, new QLabel(tr("微文档")));
    m_pStackedWidget->insertWidget(TABTITLE_WEDRIVE, new QLabel(tr("微盘")));
    m_pStackedWidget->insertWidget(TABTITLE_MEETING, new QLabel(tr("会议")));

    m_btnMin->setFixedSize(36, 26);
    m_btnMax->setFixedSize(36, 26);
    m_btnClose->setFixedSize(36, 26);
    IconHelper::SetIcon(m_btnMin, QChar(0xe7d8), 15);
    IconHelper::SetIcon(m_btnMax, QChar(0xe693), 15);
    IconHelper::SetIcon(m_btnClose, QChar(0xe64f), 15);
    m_btnMin->setProperty("toolbar", "true");
    m_btnMax->setProperty("toolbar", "true");
    m_btnClose->setProperty("toolbar_close", "true");
}

void WeComWnd::InitSolts()
{
    connect(m_pNavPane, SIGNAL(SignalTabChange(EMainTabTitle)), this, SLOT(OnTabChange(EMainTabTitle)));
    connect(this, SIGNAL(SignalTabChange(EMainTabTitle)), m_pNavPane, SLOT(OnMainTabChange(EMainTabTitle)));

    connect(m_btnMin, SIGNAL(clicked()), this, SLOT(OnMinWindows()));
    connect(m_btnMax, SIGNAL(clicked()), this, SLOT(OnMaxWindows()));
    connect(m_btnClose, SIGNAL(clicked()), this, SLOT(OnClose()));
}

void WeComWnd::Relayout()
{
    QHBoxLayout *layoutTitle = new QHBoxLayout(m_widgetTitle);
    layoutTitle->addStretch();
    layoutTitle->addWidget(m_btnMin);
    layoutTitle->addWidget(m_btnMax);
    layoutTitle->addWidget(m_btnClose);
    layoutTitle->setSpacing(0);
    layoutTitle->setMargin(0);

    QVBoxLayout *layoutMainPane = new QVBoxLayout();
    layoutMainPane->addWidget(m_widgetTitle);
    layoutMainPane->addWidget(m_pStackedWidget);
    layoutMainPane->setSpacing(0);
    layoutMainPane->setMargin(0);

    QHBoxLayout *layoutMain = new QHBoxLayout();
    layoutMain->addWidget(m_pNavPane);
    layoutMain->addLayout(layoutMainPane);
    layoutMain->setSpacing(0);
    layoutMain->setMargin(0);

    setLayout(layoutMain);
}

void WeComWnd::ChangePage()
{
    m_pStackedWidget->setCurrentIndex(m_eMainTabTitle);

    emit SignalTabChange(m_eMainTabTitle);
}

void WeComWnd::UpdateCtrlText()
{
    if (m_bMaxWindows)
    {
        m_btnMax->setToolTip(tr("向下还原"));
        IconHelper::SetIcon(m_btnMax, QChar(0xe64e), 15);
        setProperty("canMove", "false");
    }
    else
    {
        m_btnMax->setToolTip(tr("最大化"));
        IconHelper::SetIcon(m_btnMax, QChar(0xe693), 15);
        setProperty("canMove", "true");
    }
}

void WeComWnd::OnTabChange( EMainTabTitle eMainTabTitle )
{
    m_eMainTabTitle = eMainTabTitle;

    ChangePage();
}

void WeComWnd::OnMinWindows()
{
    setWindowState(Qt::WindowMinimized);
    update();
}

void WeComWnd::OnMaxWindows()
{
    m_bMaxWindows = !m_bMaxWindows;

    if (m_bMaxWindows)
        setWindowState(Qt::WindowMaximized);
    else
        setWindowState(Qt::WindowNoState);

    UpdateCtrlText();
    update();
}

void WeComWnd::OnClose()
{
    close();
}
