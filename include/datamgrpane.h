#ifndef CDATAMGRPANE_H
#define CDATAMGRPANE_H

#include <QWidget>


class CDataMgrPane : public QWidget
{
    Q_OBJECT
public:
    explicit CDataMgrPane(QWidget *parent = 0);

private:
    void CreateAllChildWnd();
    void InitCtrl();
    void Relayout();

    void resizeEvent(QResizeEvent *event);

private:
    QWidget *m_widgetCards;
};

#endif // CDATAMGRPANE_H
