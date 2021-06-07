#ifndef CCOMPONENT_H
#define CCOMPONENT_H

#include <QWidget>
#include <QtWidgets>


class CComponent : public QWidget
{
    Q_OBJECT

public:
    explicit CComponent(QWidget *parent = 0);

private:
    void CreateAllChildWnd();
    void InitCtrl();
    void InitNoticeCtrl();
    void InitPopconfirm();
    void InitSolts();
    void Relayout();

private:
    QGroupBox *m_groupNotice;
    QPushButton *m_btnOpenNotice1;
    QPushButton *m_btnOpenNotice2;
    QPushButton *m_btnOpenLT;
    QPushButton *m_btnOpenRT;
    QPushButton *m_btnOpenLB;
    QPushButton *m_btnOpenRB;

    QGroupBox *m_groupPopconfirm;
};

#endif // CCOMPONENT_H
