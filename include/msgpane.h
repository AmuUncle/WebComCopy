#ifndef CMSGPANE_H
#define CMSGPANE_H

#include <QWidget>
#include <QWebEngineView>
#include <QTextEdit>
#include <QLabel>

class CFriendsList;
class CChatTopToolbar;
class CPushButtonEx;

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
    void SendGetRequest(QString strMsg);

    bool eventFilter(QObject *obj, QEvent *e);

public slots:
    void OnBtnSendClicked();
    void OnRecvMsg(QByteArray strMsg);

private:
    CFriendsList *m_pFriendsList;
    CChatTopToolbar *m_pTopToolbar;
    QWebEngineView *m_pViewChat;
    QTextEdit *m_textEdit;
    CPushButtonEx *m_btnSend;
    QLabel *m_labSeparatorLine;
};

#endif // CMSGPANE_H
