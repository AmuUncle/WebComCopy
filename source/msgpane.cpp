#include "msgpane.h"
#include "friendslist.h"
#include <QVariant>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QKeyEvent>
#include <QWebEngineSettings>
#include "msgqueue.h"
#include "chattoptoolbar.h"
#include "pushbuttonex.h"


CMsgPane::CMsgPane(QWidget *parent) : QWidget(parent)
{
    m_pFriendsList = NULL;
    m_pTopToolbar = NULL;
    m_pViewChat = NULL;
    m_textEdit = NULL;
    m_btnSend = NULL;
    m_labSeparatorLine = NULL;

    CreateAllChildWnd();
    InitCtrl();
    InitSolts();
    Relayout();
}

void CMsgPane::CreateAllChildWnd()
{
#define NEW_OBJECT(pObj, TYPE) \
    if (NULL == pObj) { pObj = new TYPE(this); }

    NEW_OBJECT(m_pFriendsList, CFriendsList);
    NEW_OBJECT(m_pTopToolbar, CChatTopToolbar);
    NEW_OBJECT(m_pViewChat, QWebEngineView);
    NEW_OBJECT(m_textEdit, QTextEdit);
    NEW_OBJECT(m_btnSend, CPushButtonEx);
    NEW_OBJECT(m_labSeparatorLine, QLabel);
}

void CMsgPane::InitCtrl()
{
    setAttribute(Qt::WA_StyledBackground);  // 禁止父窗口样式影响子控件样式
    setProperty("form", "msgpane");

    m_pFriendsList->setFixedWidth(250);
    m_textEdit->setFixedHeight(110);
    m_textEdit->setStyleSheet("font: 14px; color:#000000;");

    m_btnSend->setFixedSize(80, 40);
    m_btnSend->setText(tr("发送(S)"));
    m_btnSend->setProperty("sendbtn", "true");

    m_labSeparatorLine->setFixedHeight(1);
    m_labSeparatorLine->setStyleSheet("background-color:#4A7ABA");
    m_labSeparatorLine->hide();

    m_pViewChat->load(QUrl("qrc:/html/html/index1.html"));
    m_pViewChat->show();

    m_textEdit->installEventFilter(this);
}

void CMsgPane::InitSolts()
{
    connect(m_pFriendsList, SIGNAL(SignalFriendChange(TUserInfo)), m_pTopToolbar, SLOT(OnFriendChange(TUserInfo)));
    connect(m_btnSend, SIGNAL(clicked()), this, SLOT(OnBtnSendClicked()));

    connect(MSGQUEUE, SIGNAL(SignalRecvMsg(QByteArray,QObject *)), this, SLOT(OnRecvMsg(QByteArray, QObject *)));
}

void CMsgPane::Relayout()
{
    QHBoxLayout *layoutSend = new QHBoxLayout();
    layoutSend->addStretch();
    layoutSend->addWidget(m_btnSend);

    QVBoxLayout *layoutRMain = new QVBoxLayout();
    layoutRMain->addWidget(m_pTopToolbar);
    layoutRMain->addWidget(m_pViewChat);
    layoutRMain->addWidget(m_labSeparatorLine);
    layoutRMain->addWidget(m_textEdit);
    layoutRMain->addLayout(layoutSend);
    layoutRMain->addStretch();

    QHBoxLayout *layoutMain = new QHBoxLayout();
    layoutMain->addWidget(m_pFriendsList);
    layoutMain->addLayout(layoutRMain);
    layoutMain->setSpacing(0);
    layoutMain->setMargin(0);

    setLayout(layoutMain);
}

bool CMsgPane::eventFilter(QObject *obj, QEvent *e)
{
    if (obj == m_textEdit)   //  指定某个QLabel
    {
        if (e->type() == QEvent::KeyPress)
        {
            QKeyEvent *event = static_cast<QKeyEvent*>(e);

            if (event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter)
            {
                OnBtnSendClicked(); //发送消息的槽
                return true;
            }
        }
    }

    return QWidget::eventFilter(obj, e);
}

void CMsgPane::OnBtnSendClicked()
{
    TMsgItem item;
    item.strUrl = QString("http://api.qingyunke.com/api.php?key=free&appid=0&msg=%1").arg(m_textEdit->toPlainText());
    item.pObj = this;
    MSGQUEUE->Push(item);

    QString jsStr = QString(QString("addMsg(\"%1\")").arg(m_textEdit->toPlainText()));
    m_pViewChat->page()->runJavaScript(jsStr);
    m_textEdit->clear();
}

void CMsgPane::OnRecvMsg(QByteArray strMsg, QObject *obj)
{
    if (obj != this)
        return;

    QJsonParseError jsonError;
    QJsonDocument doucment = QJsonDocument::fromJson(strMsg, &jsonError);
    if (!doucment.isNull() && (jsonError.error == QJsonParseError::NoError))
    {
        if (doucment.isObject())
        {
            QJsonObject object = doucment.object();
            if (object.contains("content"))
            {
                QJsonValue value = object.value("content");
                if (value.isString())
                {
                    QString strName = value.toString();

                    QString jsStr = QString(QString("addRecvMsg(\"%1\")").arg(strName));
                    m_pViewChat->page()->runJavaScript(jsStr);
                }
            }
        }
    }
}
