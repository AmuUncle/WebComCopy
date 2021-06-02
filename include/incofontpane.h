#ifndef CINCOFONTPANE_H
#define CINCOFONTPANE_H

#include <QWidget>
#include <QScrollArea>


class CIncoFontPane : public QWidget
{
    Q_OBJECT
public:
    explicit CIncoFontPane(QWidget *parent = 0);

private slots:
    void OnBtnClicked();

private:
    void CreateAllChildWnd();
    void InitCtrl();
    void InitSolts();
    void Relayout();
    void ParseJsonFile();

private:
    QScrollArea *m_pScrollArea;
    QWidget *m_widgetContent;
};

#endif // CINCOFONTPANE_H
