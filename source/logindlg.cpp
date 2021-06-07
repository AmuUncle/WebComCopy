#include "logindlg.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include "iconhelper.h"
#include <QTimer>
#include <QDesktopWidget>
#include "wecomwnd.h"


CLoginDlg::CLoginDlg(QWidget *parent) : CBaseDlg(parent)
{
    m_labCompany = NULL;
    m_labUserIcon = NULL;
    m_labUserName = NULL;
    m_labTip = NULL;
    m_btnCfg = NULL;
    m_labQRcode = NULL;

    CreateAllChildWnd();
    InitCtrl();
    InitSolts();
    Relayout();

    QTimer::singleShot(2000, this, SLOT(OnLoging()));
}

void CLoginDlg::CreateAllChildWnd()
{
#define NEW_OBJECT(pObj, TYPE) \
    if (NULL == pObj) { pObj = new TYPE(this); }

    NEW_OBJECT(m_labCompany, QLabel);
    NEW_OBJECT(m_labUserIcon, QLabel);
    NEW_OBJECT(m_labUserName, QLabel);
    NEW_OBJECT(m_labTip, QLabel);
    NEW_OBJECT(m_btnCfg, CPushButtonEx);
    NEW_OBJECT(m_labQRcode, QLabel);
}

void CLoginDlg::InitCtrl()
{
    setFixedSize(300, 425);
    EnableMoveWindow(true);

    QDesktopWidget *desktopWidget = QApplication::desktop();
    QRect screenRect = desktopWidget->screenGeometry();

    move((screenRect.width() - this->width())/2, (screenRect.height() - this->height()) / 2);

    m_labUserIcon->setStyleSheet("border-image: url(:/qss/res/usricon.jpeg);");
    m_labUserIcon->setFixedSize(110, 110);

    m_labQRcode->setStyleSheet("border-image: url(:/qss/res/QRcode.png);");
    m_labQRcode->setFixedSize(200, 200);

    m_btnCfg->setFixedSize(40, 40);
    m_labCompany->setText(tr("喜杰良圆科技股份有限公司"));
    m_labUserName->setText(tr("逍遥子"));
    m_labTip->setText(tr("扫码登录"));
    m_labCompany->setAlignment(Qt::AlignCenter);
    m_labUserName->setAlignment(Qt::AlignCenter);
    m_labTip->setAlignment(Qt::AlignCenter);

    IconHelper::SetIcon(m_btnCfg, QChar(0xe642));
    m_btnCfg->setProperty("white_bk", "true");

    m_labCompany->setStyleSheet("QLabel{font: bold 13px; color:#36608F;}");
    m_labUserName->setStyleSheet("QLabel{font: bold 16px; color:#000000;}");
    m_labTip->setStyleSheet("QLabel{font: 14px; color:#000000;}");

    m_labQRcode->show();
    m_labCompany->hide();
    m_labUserIcon->hide();
    m_labUserName->hide();
}

void CLoginDlg::InitSolts()
{

}

void CLoginDlg::Relayout()
{
    QHBoxLayout *layoutIcon = new QHBoxLayout();
    layoutIcon->addStretch();
    layoutIcon->addWidget(m_labQRcode);
    layoutIcon->addWidget(m_labUserIcon);
    layoutIcon->addStretch();

    QHBoxLayout *layoutCfg = new QHBoxLayout();
    layoutCfg->addStretch();
    layoutCfg->addWidget(m_btnCfg);
    layoutCfg->setContentsMargins(0, 0, 10, 0);

    QVBoxLayout *layoutUser = new QVBoxLayout();
    layoutUser->addLayout(layoutIcon);
    layoutUser->addWidget(m_labUserName);
    layoutUser->setSpacing(0);
    layoutUser->setMargin(0);

    QVBoxLayout *layoutVMain = new QVBoxLayout();
    layoutVMain->addWidget(m_labCompany);
    layoutVMain->addLayout(layoutUser);
    layoutVMain->addWidget(m_labTip);
    layoutVMain->addStretch();
    layoutVMain->addLayout(layoutCfg);
    layoutVMain->setSpacing(40);
    layoutVMain->setContentsMargins(0, 40, 0, 10);

    centralWidget()->setLayout(layoutVMain);
}

void CLoginDlg::OnLoginFinish()
{
    hide();

    emit SignalLoginFinish();
}

void CLoginDlg::OnLoging()
{
    m_labTip->setText(tr("正在登录..."));
    m_labQRcode->hide();
    m_labCompany->show();
    m_labUserIcon->show();
    m_labUserName->show();

    QTimer::singleShot(3000, this, SLOT(OnLoginFinish()));
}

void CLoginDlg::OnBtnCloseClicked()
{
    qApp->quit();
    reject();
}
