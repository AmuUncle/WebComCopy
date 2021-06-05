#include "navigationbar.h"


CNavigationBar::CNavigationBar(QWidget *parent) : QWidget(parent)
{
    m_mainLayout = NULL;

    QHBoxLayout *mainLayout = new QHBoxLayout(this);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(0);
    setLayout(mainLayout);
}

void CNavigationBar::Clear()
{

}

int CNavigationBar::AddItem(QString strTitle, QVariant varData)
{
//    if (NULL == widgetContent)
//        return -1;

//    CPushButtonEx *btnTitle = new CPushButtonEx(strTitle, this);
//    btnTitle->setProperty("form", "collapsepanebtn");
//    btnTitle->setLayoutDirection(Qt::RightToLeft);

//    SetItemIcon(btnTitle, false);

//    btnTitle->setFixedHeight(30);
//    btnTitle->setObjectName("collapseItemTitle");
//    btnTitle->setCheckable(true);
//    connect(btnTitle, SIGNAL(clicked()), this, SLOT(OnButtonClick()));

//    TItem *item = new TItem();
//    item->btnTitle = btnTitle;
//    item->widgetContent = widgetContent;
//    item->varData = varData;
//    item->widgetContent->setVisible(false);
//    item->nItem = m_listItems.count();

//    m_listItems.append(item);

    Relayout();

    return m_listItems.count();
}

void CNavigationBar::SetItemVisible(int nItem, bool bVisible)
{

}

void CNavigationBar::Relayout()
{

}
