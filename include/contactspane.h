#ifndef CCONTACTSPANE_H
#define CCONTACTSPANE_H

#include <QWidget>

class CFriendsList;
class CChatTopToolbar;
class CPushButtonEx;

class CContactsPane : public QWidget
{
    Q_OBJECT
public:
    explicit CContactsPane(QWidget *parent = 0);

private:
    void CreateAllChildWnd();
    void InitCtrl();
    void InitSolts();
    void Relayout();

private:
    CFriendsList *m_pFriendsList;
};

#endif // CCONTACTSPANE_H
