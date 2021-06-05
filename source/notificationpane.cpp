#include "notificationpane.h"
#include <QGuiApplication>
#include <QScreen>



NotificationPane::NotificationPane(QWidget *parent) : QWidget(parent)
{
    m_pTimerHide = NULL;
    m_nIndex = 0;

    setAttribute(Qt::WA_StyledBackground);  // 禁止父窗口样式影响子控件样式
    setWindowFlags(windowFlags() | Qt::Dialog | Qt::FramelessWindowHint | Qt::WindowMinMaxButtonsHint);
    setProperty("form", "mainwnd");


    m_pTimerHide = new QTimer(this);
    connect(m_pTimerHide, SIGNAL(timeout()), this, SLOT(OnTimerHideTimeOut()));








    setFixedSize(390, 135);
}

void NotificationPane::Start(int msec)
{
    m_pTimerHide->setInterval(msec);
    m_pTimerHide->start();
}

void NotificationPane::enterEvent(QEvent *event)
{
    m_pTimerHide->stop();
}

void NotificationPane::leaveEvent(QEvent *event)
{
    m_pTimerHide->start();
}

void NotificationPane::OnTimerHideTimeOut()
{
    hide();
    emit SignalHide(m_nIndex);
}


////////////////////////////////////////////////////////////////////


NotificationMgr* NotificationMgr::m_pNotificationMgr = NULL;
NotificationMgr::NotificationMgr(QWidget *parent)
{
    m_listNotification.clear();

    // 默认创建10个
    for (int i = 0; i < MAX_NOTICE; i++)
    {
        NotificationPane *pNotice = new NotificationPane(parent);
        pNotice->hide();
        pNotice->SetId(i);

        connect(pNotice, SIGNAL(SignalHide(int)), this, SLOT(OnItemHide(int)));

        TNoteItem tItem;
        tItem.pNotificationPane = pNotice;
        m_listNotification << tItem;
    }
}

void NotificationMgr::Init(QWidget *parent)
{
    if (NULL == m_pNotificationMgr)
    {
        m_pNotificationMgr = new NotificationMgr(parent);
    }
}

NotificationMgr *NotificationMgr::GetInstance()
{
    return m_pNotificationMgr;
}

void NotificationMgr::ExitInstance()
{
    if (m_pNotificationMgr != NULL)
    {
        delete m_pNotificationMgr;
        m_pNotificationMgr = NULL;
    }
}

void NotificationMgr::Notice(QString strContent)
{
    for (int i = 0; i < m_listNotification.size(); i++)
    {
        TNoteItem tItem = m_listNotification.at(i);
        NotificationPane *pNotice = tItem.pNotificationPane;
        if (!tItem.bShow)
        {
            m_listNotification[i].bShow = true;
            break;
        }
    }

    QScreen *screen = QGuiApplication::primaryScreen ();
    QRect screenRect =  screen->availableVirtualGeometry();
    int dWidth = screenRect.width();

    int nPos = 10;
    int nStartHeight = 10;
    for (int i = 0; i < m_listNotification.size(); i++)
    {
        TNoteItem tItem = m_listNotification.at(i);
        NotificationPane *pNotice = tItem.pNotificationPane;
        if (tItem.bShow)
        {
           pNotice->show();

           QSize size = pNotice->size();
           pNotice->move(dWidth - size.width() - 10, nStartHeight);
            pNotice->Start(tItem.nInterval);

           nStartHeight += size.height();
           nStartHeight += nPos;
        }
    }
}

void NotificationMgr::ShowAll()
{
    QScreen *screen = QGuiApplication::primaryScreen ();
    QRect screenRect =  screen->availableVirtualGeometry();
    int dWidth = screenRect.width();

    int nPos = 10;
    int nStartHeight = 10;
    for (int i = 0; i < m_listNotification.size(); i++)
    {
        TNoteItem tItem = m_listNotification.at(i);
        NotificationPane *pNotice = tItem.pNotificationPane;
        if (tItem.bShow)
        {
           pNotice->show();

           QSize size = pNotice->size();
           pNotice->move(dWidth - size.width() - 10, nStartHeight);

           nStartHeight += size.height();
           nStartHeight += nPos;
        }
    }
}

void NotificationMgr::OnItemHide(int nIndex)
{
    m_listNotification[nIndex].bShow = false;
    ShowAll();
}
