#include "wecomwnd.h"
#include "ui_wecomwnd.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include "navpane.h"

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
}

void WeComWnd::InitSolts()
{
    connect(m_pNavPane, SIGNAL(SignalTabChange(EMainTabTitle)), this, SLOT(OnTabChange(EMainTabTitle)));
    connect(this, SIGNAL(SignalTabChange(EMainTabTitle)), m_pNavPane, SLOT(OnMainTabChange(EMainTabTitle)));
}

void WeComWnd::Relayout()
{
    QHBoxLayout *layoutMain = new QHBoxLayout();
    layoutMain->addWidget(m_pNavPane);
    layoutMain->addWidget(m_pStackedWidget);
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

}

void WeComWnd::OnTabChange( EMainTabTitle eMainTabTitle )
{
    m_eMainTabTitle = eMainTabTitle;

    ChangePage();
}
