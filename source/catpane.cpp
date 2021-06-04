#include "catpane.h"
#include <QPainter>
#include <QMouseEvent>
#include <QDebug>
#include <QCursor>


CCatPane::CCatPane(QWidget *parent) : QWidget(parent)
{
    m_fXRadio = 0.5;
    m_fYRadio = 0.5;
    m_nScaleCloud1 = 0;
    m_nScaleCloud2 = 0;
    m_nScaleCloud3 = 0;

    m_pixCat.load(":/qss/res/img/cat/cat.png");
    m_pixCatEyeWrite.load(":/qss/res/img/cat/eye_write.png");
    m_pixCatEyeBlack.load(":/qss/res/img/cat/eye_black.png");
    m_pixCatEyeBg.load(":/qss/res/img/cat/eye_bg.png");

    m_pixCloud001.load(":/qss/res/img/cat/cuteCloud001.png");
    m_pixCloud002.load(":/qss/res/img/cat/cuteCloud002.png");
    m_pixCloud003.load(":/qss/res/img/cat/cuteCloud003.png");
    m_pixCloud004.load(":/qss/res/img/cat/cuteCloud004.png");
    m_pixSun.load(":/qss/res/img/cat/cuteCloud005.png");

    setMouseTracking(true);

    QPixmap myCursor = QPixmap(":/qss/res/img/cat/feather.png").scaled(QSize(40, 40), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    setCursor(myCursor);

    m_pCloudTimer = new QTimer(this);
    connect(m_pCloudTimer, SIGNAL(timeout()), this, SLOT(OnTimerCloudTimeOut()));
    m_pCloudTimer->start(100);
}

void CCatPane::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);

    DrawCloud(&painter, rect());

    double fRadio = (double)1080.0 / 1920.0;
    QRect rectCat = rect();
    rectCat.setTop(rectCat.height() >> 1);
    int nWidth = rectCat.height() / fRadio;
    rectCat.setLeft(rectCat.left() + ((rectCat.width() - nWidth) >> 1));
    rectCat.setRight(rectCat.left() + nWidth);
    DrawCat(&painter, rectCat);
}

void CCatPane::mouseMoveEvent(QMouseEvent *event)
{
    m_fXRadio = (double)event->pos().x() / width();
    m_fYRadio = (double)event->pos().y() / height();

    update();
}

void CCatPane::DrawCloud(QPainter *painter, QRect rectMain)
{
    painter->drawPixmap(rectMain.left() + 30, rectMain.top() + 10, m_pixSun);
    painter->drawPixmap(rectMain.right() - 200, rectMain.top() + 10, m_pixCloud003);

    if (m_nScaleCloud1 > rectMain.width())
        m_nScaleCloud1 = -m_pixCloud001.width();

    if (m_nScaleCloud2 > rectMain.width())
        m_nScaleCloud2 = -m_pixCloud002.width();

    if (m_nScaleCloud3 > rectMain.width())
        m_nScaleCloud3 = -m_pixCloud004.width();

    painter->drawPixmap(m_nScaleCloud1, rectMain.top() + 60, m_pixCloud001);
    painter->drawPixmap(m_nScaleCloud2, rectMain.top() + 60, m_pixCloud002);
    painter->drawPixmap(m_nScaleCloud3, rectMain.top() + 70, m_pixCloud004);
}

void CCatPane::DrawCat(QPainter *painter, QRect rectMain)
{
    if (m_fXRadio > 1.0)
        m_fXRadio = 0.5;

    if (m_fYRadio > 1.0)
        m_fYRadio = 0.5;

    painter->save();
    painter->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform | QPainter::TextAntialiasing, true);
    painter->translate(rectMain.left(), rectMain.top());
    painter->scale(rectMain.width() / 1920.0, rectMain.height() / 1080.0);

    QRect rcImgEyeBg(730, 335, 283, 162);
    QPixmap pImgEyeBg = m_pixCatEyeBg.scaled(rcImgEyeBg.size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    painter->drawPixmap(rcImgEyeBg, pImgEyeBg);

    QRect rcImgEyeBlackLeft(730 + 120 * m_fXRadio - 80 / 2, 335 + 120 * m_fYRadio - 82 /2, 80, 82);
    QPixmap pImgEyeBlack = m_pixCatEyeBlack.scaled(rcImgEyeBlackLeft.size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    painter->drawPixmap(rcImgEyeBlackLeft, pImgEyeBlack);

    QRect rcImgEyeWriteLeft(rcImgEyeBlackLeft.left() + 16, rcImgEyeBlackLeft.top() + 16, 20, 20);
    QPixmap pImgEyeWriteLeft = m_pixCatEyeWrite.scaled(rcImgEyeWriteLeft.size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    painter->drawPixmap(rcImgEyeWriteLeft, pImgEyeWriteLeft);

    QRect rcImgEyeBlackRight(895 + 120 * m_fXRadio - 80 / 2, 387 + 120 * m_fYRadio - 82 /2, 80, 82);
    pImgEyeBlack = m_pixCatEyeBlack.scaled(rcImgEyeBlackRight.size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    painter->drawPixmap(rcImgEyeBlackRight, pImgEyeBlack);

    QRect rcImgEyeWriteRight(rcImgEyeBlackRight.left() + 16 , rcImgEyeBlackRight.top() + 16, 20, 20);
    QPixmap pImgEyeWriteRight = m_pixCatEyeWrite.scaled(rcImgEyeWriteRight.size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    painter->drawPixmap(rcImgEyeWriteRight, pImgEyeWriteRight);

    QRect rcImgCat(0, 0, 1920, 1080);
    QPixmap p = m_pixCat.scaled(rcImgCat.size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    painter->drawPixmap(rcImgCat, p);

    painter->restore();
}

void CCatPane::OnTimerCloudTimeOut()
{
    m_nScaleCloud2 += 0.1;
    m_nScaleCloud3 = m_nScaleCloud2 + 80;
    m_nScaleCloud1 = m_nScaleCloud3 + 300;

    update();
}
