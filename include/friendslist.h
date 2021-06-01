#ifndef CFRIENDSLIST_H
#define CFRIENDSLIST_H

#include <QWidget>
#include <QtWidgets>
#include "public.h"
#include "pushbuttonex.h"


class CFriendsList : public QWidget
{
    Q_OBJECT
public:
    explicit CFriendsList(QWidget *parent = 0);

public:
    void SetContactMode(bool bContacts);

private slots:
    void OnItemClicked(QListWidgetItem *item, QListWidgetItem *previous);

signals:
    void SignalFriendChange(TUserInfo tUserInfo);

private:
    void CreateAllChildWnd();
    void InitCtrl();
    void InitList();
    void InitTree();
    void InitSolts();
    void Relayout();

private:
    QLineEdit *m_lineEditSearch;
    QLabel  *m_labSearch;
    CPushButtonEx *m_btnAdd;
    QListWidget *m_listwidgetFriends;
    QTreeWidget *m_listwidgetContacts;
};

#endif // CFRIENDSLIST_H
