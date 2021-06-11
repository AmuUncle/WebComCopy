#include "datamgrpane.h"
#include <QGridLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QVariant>
#include "dynamiccard.h"
#include "public.h"
#include <QDebug>
#include "userpane.h"


CDataMgrPane::CDataMgrPane(QWidget *parent) : QWidget(parent)
{
    m_widgetCards = NULL;

    CreateAllChildWnd();
    InitCtrl();
    Relayout();

}

void CDataMgrPane::CreateAllChildWnd()
{
#define NEW_OBJECT(pObj, TYPE) \
    if (NULL == pObj) { pObj = new TYPE(this); }

    NEW_OBJECT(m_widgetCards, QWidget);
}

void CDataMgrPane::InitCtrl()
{
    setAttribute(Qt::WA_StyledBackground);  // 禁止父窗口样式影响子控件样式
    setProperty("form", "msgpane");

    m_widgetCards->setFixedHeight(125);
}

void CDataMgrPane::Relayout()
{
    QHBoxLayout *layoutCards = new QHBoxLayout(m_widgetCards);

    CDynamicCard *pCard1 = new CDynamicCard(m_widgetCards);
    pCard1->SetValue(100001);
    pCard1->SetTitle(tr("点击次数"));
    pCard1->SetIcon(QChar(0xe662));
    pCard1->SetBgColor(QColor("#2D8CF0"));

    CDynamicCard *pCard2 = new CDynamicCard(m_widgetCards);
    pCard2->SetValue(999);
    pCard2->SetTitle(tr("收藏次数"));
    pCard2->SetIcon(QChar(0xe64c));
    pCard2->SetBgColor(QColor("#19BE6B"));

    CDynamicCard *pCard3 = new CDynamicCard(m_widgetCards);
    pCard3->SetValue(2233);
    pCard3->SetTitle(tr("转发次数"));
    pCard3->SetIcon(QChar(0xe665));
    pCard3->SetBgColor(QColor("#FF9900"));

    layoutCards->addWidget(pCard1);
    layoutCards->addStretch();
    layoutCards->addWidget(pCard2);
    layoutCards->addStretch();
    layoutCards->addWidget(pCard3);
    layoutCards->setSpacing(4);
    layoutCards->setMargin(0);

    CUserPane *pUserPane = new CUserPane(this);
    pUserPane->setFixedSize(400, 470);

    QHBoxLayout *layoutUserPane = new QHBoxLayout();
    layoutUserPane->addWidget(pUserPane);
    layoutUserPane->addStretch();
    layoutUserPane->setSpacing(4);
    layoutUserPane->setContentsMargins(0, 0, 0, 0);

    QVBoxLayout *layoutMain = new QVBoxLayout();
    layoutMain->addWidget(m_widgetCards);
    layoutMain->addLayout(layoutUserPane);
    layoutMain->addStretch();
    layoutMain->setSpacing(8);
    layoutMain->setMargin(4);
    setLayout(layoutMain);
}

void CDataMgrPane::resizeEvent(QResizeEvent *event)
{
    int nCardsW = width() - 4 * 2 - 4 * 2;
    double fCardW = (double)nCardsW / 3;
    double fCardH =  fCardW / ((double)257 / 112);
    m_widgetCards->setFixedHeight(fCardH + 8);
}
