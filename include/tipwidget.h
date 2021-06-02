#ifndef _TTipWidget_H_
#define _TTipWidget_H_

#include <QWidget>
#include <QLabel>
#include <QTimer>

class TTipWidget :public QLabel
{
    Q_OBJECT

public:
    static TTipWidget *Instance();
    static void ExitInstance();
    void SetMesseage(const QString &strMessage, const QPoint *pPoint=nullptr);

private:
    TTipWidget();
    ~TTipWidget();

    void OnTimer();
    void enterEvent(QEvent *);
    void leaveEvent(QEvent *);

private:
    static TTipWidget *m_pTipWidget;
    QWidget *mpParent;
    QTimer  *mpTimer;
    bool     mbEnter;
    int      mnTransparent;
};

#define AUTOTIP TTipWidget::Instance()

#endif // _TTipWidget_H_
