#include "wecomwnd.h"
#include "ui_wecomwnd.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPainter>
#include "navpane.h"
#include "pushbuttonex.h"
#include "iconhelper.h"
#include "logindlg.h"
#include "msgpane.h"


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
    m_trayIcon = NULL;
    m_systemTrayMenu = NULL;
    m_Logindlg = NULL;

    m_pMsgPane = NULL;

    m_bMaxWindows = false;

    setAttribute(Qt::WA_StyledBackground);  // 禁止父窗口样式影响子控件样式
    setWindowFlags(windowFlags() | Qt::FramelessWindowHint | Qt::WindowMinMaxButtonsHint);
    setProperty("form", "mainwnd");
    setProperty("canMove", "true");

    CreateAllChildWnd();
    InitCtrl();
    InitSolts();
    Relayout();
    ChangePage();
    InitTrayIcon();
}

WeComWnd::~WeComWnd()
{
    delete ui;
}

void WeComWnd::Login()
{
    if (m_Logindlg)
    {
        m_Logindlg->show();
        m_Logindlg->setModal(true);
    }
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
    NEW_OBJECT(m_trayIcon, QSystemTrayIcon);
    NEW_OBJECT(m_systemTrayMenu, QMenu);
    NEW_OBJECT(m_Logindlg, CLoginDlg);

    NEW_OBJECT(m_pMsgPane, CMsgPane);
}

void WeComWnd::InitCtrl()
{
    m_pNavPane->setFixedWidth(60);

    QLabel *label1 = new QLabel();
    label1->setStyleSheet("background-image: url(:/qss/res/img/compass_01.png);background-position:center;background-repeat:no-repeat;");

    QLabel *label2 = new QLabel();
    label2->setStyleSheet("background-image: url(:/qss/res/img/compass_02.png);background-position:center;background-repeat:no-repeat;");

    QLabel *label3 = new QLabel();
    label3->setStyleSheet("background-image: url(:/qss/res/img/compass_03.png);background-position:center;background-repeat:no-repeat;");

    QLabel *label4 = new QLabel();
    label4->setStyleSheet("background-image: url(:/qss/res/img/File Vault.png);background-position:center;background-repeat:no-repeat;");

    QLabel *label5 = new QLabel();
    label5->setStyleSheet("background-image: url(:/qss/res/img/Folder Actions Setup.png);background-position:center;background-repeat:no-repeat;");

    QLabel *label6 = new QLabel();
    label6->setStyleSheet("background-image: url(:/qss/res/img/Generic Application.png);background-position:center;background-repeat:no-repeat;");

    QLabel *label7 = new QLabel();
    label7->setStyleSheet("background-image: url(:/qss/res/img/Generic Network.png);background-position:center;background-repeat:no-repeat;");

    m_pStackedWidget->insertWidget(TABTITLE_MESSAGE, m_pMsgPane);
    m_pStackedWidget->insertWidget(TABTITLE_CONTACTS, label2);
    m_pStackedWidget->insertWidget(TABTITLE_CALENDAR, label3);
    m_pStackedWidget->insertWidget(TABTITLE_WORKSPACE, label4);
    m_pStackedWidget->insertWidget(TABTITLE_WEDOC, label5);
    m_pStackedWidget->insertWidget(TABTITLE_WEDRIVE, label6);
    m_pStackedWidget->insertWidget(TABTITLE_MEETING, label7);

    m_btnMin->setFixedSize(36, 26);
    m_btnMax->setFixedSize(36, 26);
    m_btnClose->setFixedSize(36, 26);
    IconHelper::SetIcon(m_btnMin, QChar(0xe7d8), 15);
    IconHelper::SetIcon(m_btnMax, QChar(0xe693), 15);
    IconHelper::SetIcon(m_btnClose, QChar(0xe64f), 15);
    m_btnMin->setProperty("toolbar", "true");
    m_btnMax->setProperty("toolbar", "true");
    m_btnClose->setProperty("toolbar_close", "true");

    m_Logindlg->hide();
}

void WeComWnd::InitSolts()
{
    connect(m_pNavPane, SIGNAL(SignalTabChange(EMainTabTitle)), this, SLOT(OnTabChange(EMainTabTitle)));
    connect(this, SIGNAL(SignalTabChange(EMainTabTitle)), m_pNavPane, SLOT(OnMainTabChange(EMainTabTitle)));
    connect(m_Logindlg, SIGNAL(SignalLoginFinish()), this, SLOT(show()));

    connect(m_btnMin, SIGNAL(clicked()), this, SLOT(OnMinWindows()));
    connect(m_btnMax, SIGNAL(clicked()), this, SLOT(OnMaxWindows()));
    connect(m_btnClose, SIGNAL(clicked()), this, SLOT(OnClose()));
    connect(m_trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this,
                SLOT(OnSystemTrayIconActivated(QSystemTrayIcon::ActivationReason)));
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
    layoutMain->setMargin(1);

    setLayout(layoutMain);
}

void WeComWnd::ChangePage()
{
    m_pStackedWidget->setCurrentIndex(m_eMainTabTitle);

    update();

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

void WeComWnd::InitTrayIcon()
{
    QAction *pRest = new QAction(tr("休息一下"), m_systemTrayMenu);
    QAction *pGoOffwork = new QAction(tr("下班了"), m_systemTrayMenu);

    QMenu *pChildRest = new QMenu(m_systemTrayMenu);
    pChildRest->setTitle(tr("休息一下"));
    pChildRest->addAction(pRest);
    pChildRest->addAction(pGoOffwork);

    QAction *restoreAction = new QAction(tr("打开主窗口"), this);
    connect(restoreAction, SIGNAL(triggered()), this, SLOT(showNormal()));

    QAction *quitAction = new QAction(tr("退出"), this);
    connect(quitAction, SIGNAL(triggered()), qApp, SLOT(quit()));

    m_systemTrayMenu->addMenu(pChildRest);
    m_systemTrayMenu->addSeparator();
    m_systemTrayMenu->addAction(restoreAction);
    m_systemTrayMenu->addAction(quitAction);

    m_trayIcon->setContextMenu(m_systemTrayMenu);
    m_trayIcon->setIcon(QIcon(":/qss/res/WeComCopy_Tray.png"));  //设置托盘图标显示
    m_trayIcon->setToolTip(tr("企业微信:逍遥子")); //显示提示信息
    m_trayIcon->show();
}

void WeComWnd::mouseDoubleClickEvent( QMouseEvent *event )
{
    if(!m_widgetTitle->geometry().contains(this->mapFromGlobal(QCursor::pos())))
        return;

    OnMaxWindows();
}

void WeComWnd::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);         // 创建画家对象
    painter.setRenderHint(QPainter::Antialiasing, true); // 反走样

    QRect rcClient = rect();

    if (TABTITLE_MESSAGE == m_eMainTabTitle)
    {
        QRect rcClientLeft(rcClient);
        rcClientLeft.setRight(m_pNavPane->width() + 250);
        rcClientLeft.setTop(rcClientLeft.top() + 1);
        rcClientLeft.setBottom(rcClientLeft.bottom() - 1);
        rcClientLeft.setLeft(rcClientLeft.left() + m_pNavPane->width());

        painter.setPen(Qt::NoPen);
        painter.setBrush(QColor("#E6E8EB"));
        painter.drawRect(rcClientLeft);

        QPen pen(QColor("#D4D6D9"));
        painter.setPen(pen);
        painter.drawLine(rcClientLeft.topRight(), rcClientLeft.bottomRight());
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
    hide();
}

void WeComWnd::OnSystemTrayIconActivated(QSystemTrayIcon::ActivationReason reason)
{
    if(reason == QSystemTrayIcon::Trigger)
        showNormal();   //系统托盘中的图标被单击
    else if(reason == QSystemTrayIcon::DoubleClick)
        showNormal();   //系统托盘中的图标被双击
}
