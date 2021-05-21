#include "wecomwnd.h"
#include "ui_wecomwnd.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include "navpane.h"

WeComWnd::WeComWnd(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WeComWnd)
{
    ui->setupUi(this);

    m_pStackedWidget = NULL;
    m_pNavPane = NULL;

    setWindowFlags(windowFlags() | Qt::FramelessWindowHint | Qt::WindowMinMaxButtonsHint);
    setProperty("form", "mainwnd");
    setProperty("canMove", "true");

    CreateAllChildWnd();
    InitCtrl();
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

}

void WeComWnd::UpdateCtrlText()
{

}
