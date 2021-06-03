#include "catpane.h"
#include <QPainter>
#include <QMouseEvent>
#include <QDebug>
#include <QCursor>


CCatPane::CCatPane(QWidget *parent) : QWidget(parent)
{
    m_fXRadio = 0.5;
    m_fYRadio = 0.5;

    m_pixCat.load(":/qss/res/img/cat/cat.png");
    m_pixCatEyeWrite.load(":/qss/res/img/cat/eye_write.png");
    m_pixCatEyeBlack.load(":/qss/res/img/cat/eye_black.png");
    m_pixCatEyeBg.load(":/qss/res/img/cat/eye_bg.png");
    setMouseTracking(true);

    QPixmap myCursor = QPixmap(":/qss/res/img/cat/feather.png").scaled(QSize(40, 40), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    setCursor(myCursor);
}

void CCatPane::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);

    double fRadio = (double)1080.0 / 1920.0;
    QRect rectCat = rect();
    rectCat.setTop(rectCat.height() >> 1);
    int nWidth = rectCat.height() / fRadio;
    rectCat.setLeft(rectCat.left() + (rectCat.width() - nWidth) >> 1);
    rectCat.setRight(rectCat.left() + nWidth);
    DrawCat(&painter, rectCat);
}

void CCatPane::mouseMoveEvent(QMouseEvent *event)
{
    m_fXRadio = (double)event->pos().x() / width();
    m_fYRadio = (double)event->pos().y() / height();

    update();
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
