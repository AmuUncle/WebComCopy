#include "component.h"
#include <QGridLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "public.h"
#include "notificationpane.h"
#include "popconfirm.h"

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
    m_btnTop  = NULL;
    m_btnLeft  = NULL;
    m_btnRight  = NULL;
    m_btnBottom  = NULL;
    m_btnTL = NULL;
    m_btnTR = NULL;
    m_btnLT = NULL;
    m_btnRT = NULL;
    m_btnLB = NULL;
    m_btnRB = NULL;
    m_btnBL = NULL;
    m_btnBR = NULL;

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

    NEW_OBJECT(m_btnTop, QPushButton);
    NEW_OBJECT(m_btnLeft, QPushButton);
    NEW_OBJECT(m_btnRight, QPushButton);
    NEW_OBJECT(m_btnBottom, QPushButton);
    NEW_OBJECT(m_btnTL, QPushButton);
    NEW_OBJECT(m_btnTR, QPushButton);
    NEW_OBJECT(m_btnLT, QPushButton);
    NEW_OBJECT(m_btnRT, QPushButton);
    NEW_OBJECT(m_btnLB, QPushButton);
    NEW_OBJECT(m_btnRB, QPushButton);
    NEW_OBJECT(m_btnBL, QPushButton);
    NEW_OBJECT(m_btnBR, QPushButton);
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
    m_btnOpenRT->setText("右上");
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
    m_groupPopconfirm->setFixedHeight(220);
    m_groupPopconfirm->setTitle(tr("气泡确认框"));
    m_btnTop->setText("Top");
    m_btnLeft->setText("Left");
    m_btnRight->setText("Right");
    m_btnBottom->setText("Bottom");

    m_btnTL->setText("TL");
    m_btnTR->setText("TR");
    m_btnLT->setText("LT");
    m_btnRT->setText("RT");
    m_btnLB->setText("LB");
    m_btnRB->setText("RB");
    m_btnBL->setText("BL");
    m_btnBR->setText("BR");

    QGridLayout *layoutComponent = new QGridLayout();
    layoutComponent->addWidget(m_btnTL, 0, 1, 1, 1);
    layoutComponent->addWidget(m_btnTop, 0, 2, 1, 1);
    layoutComponent->addWidget(m_btnTR, 0, 3, 1, 1);
    layoutComponent->addWidget(m_btnLT, 1, 0, 1, 1);
    layoutComponent->addWidget(m_btnRT, 1, 4, 1, 1);
    layoutComponent->addWidget(m_btnLeft, 2, 0, 1, 1);
    layoutComponent->addWidget(m_btnRight, 2, 4, 1, 1);
    layoutComponent->addWidget(m_btnLB, 3, 0, 1, 1);
    layoutComponent->addWidget(m_btnRB, 3, 4, 1, 1);
    layoutComponent->addWidget(m_btnBL, 4, 1, 1, 1);
    layoutComponent->addWidget(m_btnBottom, 4, 2, 1, 1);
    layoutComponent->addWidget(m_btnBR, 4, 3, 1, 1);

    layoutComponent->setSpacing(8);
    layoutComponent->setMargin(10);

    m_groupPopconfirm->setLayout(layoutComponent);
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

    /////////////////////////////

    connect(m_btnTop, &QPushButton::clicked, [this]
                                                    {
                                                        CPopconfirm *pPopconfirm = new CPopconfirm(m_btnTop);
                                                        pPopconfirm->Show(CPopconfirm::AlignTop);
                                                    });

    connect(m_btnLeft, &QPushButton::clicked, [this]
                                                    {
                                                        CPopconfirm *pPopconfirm = new CPopconfirm(m_btnLeft);
                                                        pPopconfirm->Show(CPopconfirm::AlignLeft);
                                                    });

    connect(m_btnRight, &QPushButton::clicked, [this]
                                                    {
                                                        CPopconfirm *pPopconfirm = new CPopconfirm(m_btnRight);
                                                        pPopconfirm->Show(CPopconfirm::AlignRight);
                                                    });

    connect(m_btnBottom, &QPushButton::clicked, [this]
                                                    {
                                                        CPopconfirm *pPopconfirm = new CPopconfirm(m_btnBottom);
                                                        pPopconfirm->Show(CPopconfirm::AlignBottom);
                                                    });

    connect(m_btnTL, &QPushButton::clicked, [this]
                                                    {
                                                        CPopconfirm *pPopconfirm = new CPopconfirm(m_btnTL);
                                                        pPopconfirm->Show(CPopconfirm::AlignTopLeft);
                                                    });

    connect(m_btnTR, &QPushButton::clicked, [this]
                                                    {
                                                        CPopconfirm *pPopconfirm = new CPopconfirm(m_btnTR);
                                                        pPopconfirm->Show(CPopconfirm::AlignTopRight);
                                                    });

    connect(m_btnLT, &QPushButton::clicked, [this]
                                                    {
                                                        CPopconfirm *pPopconfirm = new CPopconfirm(m_btnLT);
                                                        pPopconfirm->Show(CPopconfirm::AlignLeftTop);
                                                    });

    connect(m_btnRT, &QPushButton::clicked, [this]
                                                    {
                                                        CPopconfirm *pPopconfirm = new CPopconfirm(m_btnRT);
                                                        pPopconfirm->Show(CPopconfirm::AlignRightTop);
                                                    });

    connect(m_btnLB, &QPushButton::clicked, [this]
                                                    {
                                                        CPopconfirm *pPopconfirm = new CPopconfirm(m_btnLB);
                                                        pPopconfirm->Show(CPopconfirm::AlignLeftBottom);
                                                    });

    connect(m_btnRB, &QPushButton::clicked, [this]
                                                    {
                                                        CPopconfirm *pPopconfirm = new CPopconfirm(m_btnRB);
                                                        pPopconfirm->Show(CPopconfirm::AlignRightBottom);
                                                    });

    connect(m_btnBL, &QPushButton::clicked, [this]
                                                    {
                                                        CPopconfirm *pPopconfirm = new CPopconfirm(m_btnBL);
                                                        pPopconfirm->Show(CPopconfirm::AlignBottomLeft);
                                                    });

    connect(m_btnBR, &QPushButton::clicked, [this]
                                                    {
                                                        CPopconfirm *pPopconfirm = new CPopconfirm(m_btnBR);
                                                        pPopconfirm->Show(CPopconfirm::AlignBottomRight);
                                                    });
}

void CComponent::Relayout()
{
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
