#ifndef CMSGPANE_H
#define CMSGPANE_H

#include <QWidget>


class CFriendsList;


class CMsgPane : public QWidget
{
    Q_OBJECT
public:
    explicit CMsgPane(QWidget *parent = 0);

private:
    void CreateAllChildWnd();
    void InitCtrl();
    void InitSolts();
    void Relayout();

private:
    CFriendsList *m_pFriendsList;
};

#endif // CMSGPANE_H
