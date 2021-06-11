#ifndef CUSERPANE_H
#define CUSERPANE_H

#include <QWidget>

class CUserDetailPane : public QWidget
{
    Q_OBJECT
public:
    explicit CUserDetailPane(QWidget *parent = 0);

protected:
    void paintEvent(QPaintEvent *);
};

class CUserPane : public QWidget
{
    Q_OBJECT
public:
    explicit CUserPane(QWidget *parent = 0);

private:
    void CreateAllChildWnd();
    void InitCtrl();
    void InitSolts();
    void Relayout();

private:
    CUserDetailPane *m_pUserPane;
};

#endif // CUSERPANE_H
