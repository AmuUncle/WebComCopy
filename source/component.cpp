#include "component.h"
#include <QGridLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "public.h"
#include "notificationpane.h"


CComponent::CComponent(QWidget *parent) : QWidget(parent)
{
    m_groupNotice = NULL;
    m_btnOpenNotice1 = NULL;
    m_btnOpenNotice2 = NULL;
    m_btnOpenLT  = NULL;
    m_btnOpenRT  = NULL;
    m_btnOpenLB  = NULL;
    m_btnOpenRB  = NULL;

    m_groupPopconfirm = NULL;

    setAttribute(Qt::WA_StyledBackground);  // 禁止父窗口样式影响子控件样式
    setProperty("form", "basedlg");

    CreateAllChildWnd();
    InitCtrl();
    InitSolts();
    Relayout();
}

void CComponent::CreateAllChildWnd()
{
#define NEW_OBJECT(pObj, TYPE) \
    if (NULL == pObj) { pObj = new TYPE(this); }

    NEW_OBJECT(m_groupNotice, QGroupBox);
    NEW_OBJECT(m_groupPopconfirm, QGroupBox);

    NEW_OBJECT(m_btnOpenNotice1, QPushButton);
    NEW_OBJECT(m_btnOpenNotice2, QPushButton);
    NEW_OBJECT(m_btnOpenLT, QPushButton);
    NEW_OBJECT(m_btnOpenRT, QPushButton);
    NEW_OBJECT(m_btnOpenLB, QPushButton);
    NEW_OBJECT(m_btnOpenRB, QPushButton);
}

void CComponent::InitCtrl()
{
    InitNoticeCtrl();
    InitPopconfirm();
}

void CComponent::InitNoticeCtrl()
{
    m_groupNotice->setFixedHeight(120);
    m_groupNotice->setTitle(tr("通知提醒框"));
    m_btnOpenNotice1->setText("自动关闭");
    m_btnOpenNotice2->setText("不关闭");
    m_btnOpenNotice1->setToolTip("最简单的用法，4.5 秒后自动关闭。");
    m_btnOpenNotice2->setToolTip("不自动关闭");
    m_btnOpenNotice1->setFixedWidth(188);
    m_btnOpenNotice2->setFixedWidth(188);

    m_btnOpenLT->setText("左上");
    m_btnOpenRT->setText("右下");
    m_btnOpenLB->setText("左下");
    m_btnOpenRB->setText("右下");

    QGridLayout *layoutComponent = new QGridLayout();
    layoutComponent->addWidget(m_btnOpenNotice1, 0, 0, 1, 2);
    layoutComponent->addWidget(m_btnOpenLT, 0, 2, 1, 1);
    layoutComponent->addWidget(m_btnOpenRT, 0, 3, 1, 1);

    layoutComponent->addWidget(m_btnOpenNotice2, 1, 0, 1, 2);
    layoutComponent->addWidget(m_btnOpenLB, 1, 2, 1, 1);
    layoutComponent->addWidget(m_btnOpenRB, 1, 3, 1, 1);

    layoutComponent->setSpacing(8);
    layoutComponent->setMargin(25);

    m_groupNotice->setLayout(layoutComponent);
}

void CComponent::InitPopconfirm()
{
    m_groupPopconfirm->setFixedHeight(120);
    m_groupPopconfirm->setTitle(tr("气泡确认框"));
}

void CComponent::InitSolts()
{
    connect(m_btnOpenNotice1, &QPushButton::clicked, [this]
                                                    {
                                                        NotificationMgr::GetInstance()->Notice("This is the content of the notification. This is the content of the notification. This is the content of the notification.",
                                                                                               "Notification Title");
                                                    });

    connect(m_btnOpenNotice2, &QPushButton::clicked, [this]
                                                    {
                                                        NotificationMgr::GetInstance()->Notice("I will never close automatically. This is a purposely very very long description that has many many characters and words.",
                                                                                               "Notification Title", false);
                                                    });

    connect(m_btnOpenLT, &QPushButton::clicked, [this]
                                                    {
                                                        NotificationMgr::GetInstance()->Notice("This is the content of the notification. This is the content of the notification. This is the content of the notification.",
                                                                                               "Notification Title", true, NotificationMgr::AlignLeft | NotificationMgr::AlignTop);
                                                    });

    connect(m_btnOpenRT, &QPushButton::clicked, [this]
                                                    {
                                                        NotificationMgr::GetInstance()->Notice("I will never close automatically. This is a purposely very very long description that has many many characters and words.",
                                                                                               "Notification Title", true, NotificationMgr::AlignRight | NotificationMgr::AlignTop);
                                                    });

    connect(m_btnOpenLB, &QPushButton::clicked, [this]
                                                    {
                                                        NotificationMgr::GetInstance()->Notice("I will never close automatically. This is a purposely very very long description that has many many characters and words.",
                                                                                               "Notification Title", true, NotificationMgr::AlignLeft | NotificationMgr::AlignBottom);
                                                    });

    connect(m_btnOpenRB, &QPushButton::clicked, [this]
                                                    {
                                                        NotificationMgr::GetInstance()->Notice("I will never close automatically. This is a purposely very very long description that has many many characters and words.",
                                                                                               "Notification Title", true, NotificationMgr::AlignRight | NotificationMgr::AlignBottom);
                                                    });
}

void CComponent::Relayout()
{
    // 12 * 12
    QGridLayout *layoutComponent = new QGridLayout();
    layoutComponent->addWidget(m_groupNotice, 0, 0, 3, 6);
    layoutComponent->addWidget(m_groupPopconfirm, 3, 0, 3, 6);
    layoutComponent->setSpacing(8);
    layoutComponent->setMargin(25);

    QVBoxLayout *layoutMain = new QVBoxLayout();
    layoutMain->addLayout(layoutComponent);
    layoutMain->addStretch();
    layoutMain->setSpacing(0);
    layoutMain->setMargin(0);

    setLayout(layoutMain);
}
