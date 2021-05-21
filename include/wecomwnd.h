#ifndef WECOMWND_H
#define WECOMWND_H

#include <QWidget>
#include <QtWidgets>

namespace Ui {
class WeComWnd;
}

class NavPane;

class WeComWnd : public QWidget
{
    Q_OBJECT

public:
    explicit WeComWnd(QWidget *parent = 0);
    ~WeComWnd();

private:
    void CreateAllChildWnd();
    void InitCtrl();
    void Relayout();
    void ChangePage();
    void UpdateCtrlText();

private:
    Ui::WeComWnd *ui;
    QStackedWidget *m_pStackedWidget;
    NavPane *m_pNavPane;
};

#endif // WECOMWND_H
