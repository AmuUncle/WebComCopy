#ifndef CPOPCONFIRM_H
#define CPOPCONFIRM_H

#include <QWidget>
#include <QtWidgets>
class CPushButtonEx;

class CPopconfirm : public QWidget
{
    Q_OBJECT
public:
    explicit CPopconfirm(QWidget *parent = 0);

    enum EAlignment
    {
        AlignLeft,
        AlignRight,
        AlignTop,
        AlignBottom,
        AlignTopLeft,
        AlignTopRight,
        AlignLeftTop,
        AlignRightTop,
        AlignLeftBottom,
        AlignRightBottom,
        AlignBottomLeft,
        AlignBottomRight,
    };

public:
    void Show(EAlignment eAlignment = AlignTop);

private:
    void paintEvent(QPaintEvent *event);
    bool event(QEvent *event);

private:
    void CreateAllChildWnd();
    void InitCtrl();
    void Relayout();

private:
    EAlignment m_eAlignment;

    QLabel *m_labelIcon;
    QLabel *m_labelTitle;
    QPushButton *m_btnYes;
    QPushButton *m_btnNo;
};

#endif // CPOPCONFIRM_H
