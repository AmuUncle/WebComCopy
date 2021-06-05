#ifndef CNAVIGATIONBAR_H
#define CNAVIGATIONBAR_H

#include <QWidget>
#include <QList>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include "pushbuttonex.h"



class CNavigationBar : public QWidget
{
    Q_OBJECT
public:
    explicit CNavigationBar(QWidget *parent = 0);

public:
    void Clear();
    int AddItem(QString strTitle, QVariant varData = 0);
    void SetItemVisible(int nItem, bool bVisible);              // nItem 从1开始

private:
    void Relayout();

private:
    struct TItem
    {
        CPushButtonEx *btnTitle;
        QVariant varData;
        int nIndex;
    };

    QList<TItem*> m_listItems;
    QHBoxLayout *m_mainLayout;
};

#endif // CNAVIGATIONBAR_H
