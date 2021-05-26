#include "userdetaildlg.h"
#include "pushbuttonex.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QDesktopServices>
#include <QUrl>
#include "iconhelper.h"

#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif

CUserDetailDlg::CUserDetailDlg(QWidget *parent) : QWidget(parent)
{
    m_widgetTop = NULL;
    m_btnUserIcon = NULL;
    m_labUserName = NULL;
    m_labSex = NULL;

    m_labSeparatorLine = NULL;

    m_labTel = NULL;
    m_labTelValue = NULL;
    m_labMail = NULL;
    m_labMailValue = NULL;
    m_labDepartment = NULL;
    m_labDepartmentValue = NULL;

    m_btnSendMsg = NULL;

    m_pAvatar = NULL;
    m_labelAvatar = NULL;

    setAttribute(Qt::WA_StyledBackground);  // 禁止父窗口样式影响子控件样式
    setProperty("form", "userdetail");

    CreateAllChildWnd();
    InitCtrl();
    Relayout();

    connect(m_btnUserIcon, SIGNAL(clicked()), this, SLOT(OnBtnUserIconClicked()));
}

void CUserDetailDlg::SetUserInfo(QString strName, QString ico)
{
    m_labUserName->setText(strName);
    m_btnUserIcon->setIcon(QIcon(ico));
    m_btnUserIcon->setIconSize(m_btnUserIcon->size());

    m_labelAvatar->setStyleSheet(QString("border-image: url(%1);").arg(ico));
}

void CUserDetailDlg::CreateAllChildWnd()
{
#define NEW_OBJECT(pObj, TYPE) \
    if (NULL == pObj) { pObj = new TYPE(this); }

    NEW_OBJECT(m_widgetTop, QWidget);
    NEW_OBJECT(m_btnUserIcon, CPushButtonEx);
    NEW_OBJECT(m_labUserName, QLabel);
    NEW_OBJECT(m_labSex, QLabel);
    NEW_OBJECT(m_labSeparatorLine, QLabel);
    NEW_OBJECT(m_labTel, QLabel);
    NEW_OBJECT(m_labTelValue, QLabel);
    NEW_OBJECT(m_labMail, QLabel);
    NEW_OBJECT(m_labMailValue, QLabel);
    NEW_OBJECT(m_labDepartment, QLabel);
    NEW_OBJECT(m_labDepartmentValue, QLabel);
    NEW_OBJECT(m_btnSendMsg, CPushButtonEx);

    NEW_OBJECT(m_pAvatar, QWidget);

    if (NULL == m_labelAvatar)
        m_labelAvatar = new QLabel(m_pAvatar);
}

void CUserDetailDlg::InitCtrl()
{
    setFixedSize(280, 270);
    setWindowFlags(Qt::Popup);

    m_pAvatar->hide();
    m_labelAvatar->setStyleSheet("border-image: url(:/qss/res/usricon.jpeg);");
    m_pAvatar->setFixedSize(230, 230);
    m_pAvatar->setWindowFlags(Qt::Popup);
    m_pAvatar->setProperty("form", "userdetail");

    m_btnUserIcon->setFixedSize(70, 70);
    m_btnUserIcon->setIcon(QIcon(":/qss/res/usricon.jpeg"));
    m_btnUserIcon->setIconSize(m_btnUserIcon->size());

    m_labSeparatorLine->setFixedHeight(1);
    m_labSeparatorLine->setStyleSheet("background-color:#E5E5E5");

    m_labTel->setProperty("title", "true");
    m_labMail->setProperty("title", "true");
    m_labDepartment->setProperty("title", "true");
    m_labUserName->setProperty("username", "true");
    m_labSex->setProperty("sex", "true");
    m_btnSendMsg->setProperty("sendmsg", "true");
    m_labTelValue->setProperty("link", "true");
    m_labMailValue->setProperty("link", "true");
    m_labDepartmentValue->setProperty("link", "true");

    m_labUserName->setTextInteractionFlags(Qt::TextSelectableByMouse);
    m_labUserName->setCursor(Qt::IBeamCursor);
    m_labTelValue->setCursor(Qt::PointingHandCursor);
    m_labMailValue->setCursor(Qt::PointingHandCursor);
    m_labDepartmentValue->setCursor(Qt::PointingHandCursor);

    m_labTelValue->installEventFilter(this);    // 安装事件过滤器
    m_labMailValue->installEventFilter(this);    // 安装事件过滤器
    m_labDepartmentValue->installEventFilter(this);    // 安装事件过滤器

    m_labUserName->setText(tr("逍遥子"));
    m_labTel->setText(tr("手机"));
    m_labTelValue->setText(tr("15088888888"));
    m_labMail->setText(tr("邮箱"));
    m_labMailValue->setText(tr("hudejie2018@163.com"));
    m_labDepartment->setText(tr("部门"));
    m_labDepartmentValue->setText(tr("行业服务部/开发应用组"));

    m_btnSendMsg->setText(tr("发消息"));

    IconHelper::SetIcon(m_labSex, QChar(0xe646), 14);
}

void CUserDetailDlg::Relayout()
{
    QHBoxLayout *layoutMain = new QHBoxLayout();
    layoutMain->addWidget(m_btnUserIcon);
    layoutMain->addWidget(m_labUserName);
    layoutMain->addWidget(m_labSex);
    layoutMain->addStretch();
    layoutMain->setSpacing(6);
    layoutMain->setMargin(0);

    int nIndex = 0;
    QGridLayout *layoutTop = new QGridLayout();
    layoutTop->addLayout(layoutMain, 0, 0, 1, 5);

    nIndex++;
    layoutTop->addWidget(m_labSeparatorLine, nIndex, 0, 1, 5);

    nIndex++;
    layoutTop->addWidget(m_labTel, nIndex, 0, 1, 1);
    layoutTop->addWidget(m_labTelValue, nIndex, 1, 1, 4);

    nIndex++;
    layoutTop->addWidget(m_labMail, nIndex, 0, 1, 1);
    layoutTop->addWidget(m_labMailValue, nIndex, 1, 1, 4);

    nIndex++;
    layoutTop->addWidget(m_labDepartment, nIndex, 0, 1, 1);
    layoutTop->addWidget(m_labDepartmentValue, nIndex, 1, 1, 4);

    nIndex++;
    layoutTop->addWidget(m_btnSendMsg, nIndex, 0, 1, 5);

    layoutTop->setSpacing(6);
    layoutTop->setContentsMargins(20, 20, 20, 20);
    setLayout(layoutTop);

    QHBoxLayout *layoutUserIcon = new QHBoxLayout(m_pAvatar);
    layoutUserIcon->addWidget(m_labelAvatar);
    layoutUserIcon->setSpacing(6);
    layoutUserIcon->setMargin(8);
}

bool CUserDetailDlg::eventFilter(QObject *obj, QEvent *event)
{
    if (obj == m_labTelValue)   //  指定某个QLabel
    {
        if (event->type() == QEvent::MouseButtonPress)  // mouse button pressed
        {
            QDesktopServices::openUrl(QUrl(QString("tel:%1").arg(m_labTelValue->text())));
        }
    }
    else if (obj == m_labMailValue) //  指定某个QLabel
    {
        if (event->type() == QEvent::MouseButtonPress)  // mouse button pressed
        {
            QDesktopServices::openUrl(QUrl(QString("mailto:%1").arg(m_labMailValue->text())));
        }
    }

    return QWidget::eventFilter(obj, event);
}

void CUserDetailDlg::OnBtnUserIconClicked()
{
    m_pAvatar->show();

    QPoint ptBtn = m_btnUserIcon->mapToGlobal(m_btnUserIcon->pos());
    QPoint point(ptBtn);
    point.setX(ptBtn.x() - m_btnUserIcon->pos().x() - (m_pAvatar->width() - m_btnUserIcon->width()) / 2);
    point.setY(ptBtn.y() - m_btnUserIcon->pos().y() + m_btnUserIcon->height() + 2);
    m_pAvatar->move(point);

    qDebug() << point;
}
