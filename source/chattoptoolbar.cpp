#include "chattoptoolbar.h"
#include "iconhelper.h"
#include "pushbuttonex.h"
#include "public.h"
#include "userdetaildlg.h"


CChatTopToolbar::CChatTopToolbar(QWidget *parent) : QWidget(parent)
{
    m_labUserName = NULL;
    m_labState = NULL;
    m_labEmail = NULL;
    m_labEmailValue = NULL;

    m_labSeparatorLine = NULL;

    m_labPart = NULL;
    m_labPartValue = NULL;
    m_btnAddUser = NULL;

    m_labSign = NULL;
    m_labSignValue = NULL;

    m_pUserDetail = NULL;

    setAttribute(Qt::WA_StyledBackground);  // 禁止父窗口样式影响子控件样式
    setProperty("form", "toptoolbar");

    CreateAllChildWnd();
    InitCtrl();
    Relayout();
}

void CChatTopToolbar::OnFriendChange(TUserInfo tUserInfo)
{
    m_tUserInfo = tUserInfo;
    m_labUserName->setText(tUserInfo.strName);
    m_labPartValue->setText(tUserInfo.strPart);
    m_labEmailValue->setText(tUserInfo.strEmail);

    QStringList strListSign;
    strListSign << "会议轰炸中" << "疯狂打码中" << "5F-16L-04" << "疯狂打BUG" << "╰╮45°仰朢天空，眼涙就不會畱下來╭╯" << "哪天版本？" <<
                   "说重点" << "有事烧香" << "我不复杂，但也不简单。" << "可能不舍的不是你而是昨天。" << "一样的眼睛，不一样的看法。"
                << "人穷志不穷，心要野，志要大!" << "嫉妒的别放弃，羡慕的请继续。" << "你玩你的自定义我玩我的格式化。" << "你我之间还有什么比沉默更难堪。"
                << "我的容忍也许会过界，请你理智。" << "有间旺铺要出租" << "招聘一个心上人。" << "我的世界黑与白，五彩世界请滚开。" << "有些事不要逞强，有些人不必勉强。";

    qsrand(QTime(0,0,0).msecsTo(QTime::currentTime()));
    int nIndex = qrand() % strListSign.length();
    m_labSignValue->setText(strListSign.at(nIndex));
}

bool CChatTopToolbar::eventFilter(QObject *obj, QEvent *event)
{
    if (obj == m_labUserName)   //  指定某个QLabel
    {
        if (event->type() == QEvent::MouseButtonPress)  // mouse button pressed
        {
            m_pUserDetail->SetUserInfo(m_labUserName->text(), m_tUserInfo.strAvatar);
            m_pUserDetail->show();

            QPoint ptBtn = m_labUserName->mapToGlobal(m_labUserName->pos());
            QPoint point(ptBtn);
            point.setX(ptBtn.x() - m_labUserName->pos().x());
            point.setY(ptBtn.y() - m_labUserName->pos().y() + m_labUserName->height() + 2);
            m_pUserDetail->move(point);
        }
    }

    return QWidget::eventFilter(obj, event);
}

void CChatTopToolbar::CreateAllChildWnd()
{
#define NEW_OBJECT(pObj, TYPE) \
    if (NULL == pObj) { pObj = new TYPE(this); }

    NEW_OBJECT(m_labUserName, QLabel);
    NEW_OBJECT(m_labState, QLabel);
    NEW_OBJECT(m_labEmail, QLabel);
    NEW_OBJECT(m_labEmailValue, QLabel);
    NEW_OBJECT(m_labSeparatorLine, QLabel);
    NEW_OBJECT(m_labPart, QLabel);
    NEW_OBJECT(m_labPartValue, QLabel);
    NEW_OBJECT(m_btnAddUser, CPushButtonEx);
    NEW_OBJECT(m_labSign, QLabel);
    NEW_OBJECT(m_labSignValue, QLabel);
    NEW_OBJECT(m_pUserDetail, CUserDetailDlg);
}

void CChatTopToolbar::InitCtrl()
{
    setFixedHeight(60);

    m_labUserName->setText(tr("逍遥子"));
    m_labUserName->setStyleSheet("font: 16px; font-weight: bold; color:#000000;");

    m_labEmailValue->setText(tr("hudejie2018@163.com"));
    m_labEmailValue->setStyleSheet("color:#ACACAC;");
    m_labPartValue->setText(tr("开发应用组"));
    m_labPartValue->setStyleSheet("color:#ACACAC;");

    m_labSignValue->setText(tr("╰╮45°仰朢天空，眼涙就不會畱下來╭╯ "));
    m_labSignValue->setStyleSheet("color:#ACACAC;");

    m_labSeparatorLine->setFixedSize(1, 14);
    m_labSeparatorLine->setStyleSheet("background-color:#E5E5E5");

    IconHelper::SetIcon(m_labState, QChar(0xe655), 20);
    m_labState->setStyleSheet("color:#5FB8F1;");

    IconHelper::SetIcon(m_labEmail, QChar(0xe652), 20);
    m_labEmail->setStyleSheet("color:#ACACAC;");

    IconHelper::SetIcon(m_labPart, QChar(0xe654), 20);
    m_labPart->setStyleSheet("color:#ACACAC;");

    IconHelper::SetIcon(m_btnAddUser, QChar(0xe656), 24);
    m_btnAddUser->setProperty("white_bk", "true");

    IconHelper::SetIcon(m_labSign, QChar(0xe645), 20);
    m_labSign->setStyleSheet("color:#ACACAC;");

    m_labUserName->installEventFilter(this);    // 安装事件过滤器
    m_pUserDetail->hide();
}

void CChatTopToolbar::Relayout()
{
    QHBoxLayout *layoutUser = new QHBoxLayout();
    layoutUser->addWidget(m_labUserName);
    layoutUser->addWidget(m_labState);
    layoutUser->setContentsMargins(0, 0, 10, 0);

    QHBoxLayout *layoutInfo = new QHBoxLayout();
    layoutInfo->addLayout(layoutUser);
    layoutInfo->addWidget(m_labEmail);
    layoutInfo->addWidget(m_labEmailValue);
    layoutInfo->addWidget(m_labSeparatorLine);
    layoutInfo->addWidget(m_labPart);
    layoutInfo->addWidget(m_labPartValue);
    layoutInfo->addStretch();
    layoutInfo->addWidget(m_btnAddUser);

    layoutInfo->setSpacing(6);
    layoutInfo->setContentsMargins(0, 0, 0, 0);

    QHBoxLayout *layoutSign = new QHBoxLayout();
    layoutSign->addWidget(m_labSign);
    layoutSign->addWidget(m_labSignValue);
    layoutSign->addStretch();
    layoutSign->setSpacing(6);
    layoutSign->setContentsMargins(0, 0, 0, 0);

    QVBoxLayout *layoutMain = new QVBoxLayout();
    layoutMain->addLayout(layoutInfo);
    layoutMain->addLayout(layoutSign);
    layoutMain->setSpacing(0);
    layoutMain->setContentsMargins(20, 6, 10, 6);

    setLayout(layoutMain);
}
