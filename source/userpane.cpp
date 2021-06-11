#include "userpane.h"
#include <QVariant>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QVariant>
#include <QPainter>
#include "public.h"
#include "iconhelper.h"
#include <QtMath>
#include <QDebug>
#include <QGraphicsDropShadowEffect>


CUserDetailPane::CUserDetailPane(QWidget *parent)
{
    setAttribute(Qt::WA_StyledBackground);  // 禁止父窗口样式影响子控件样式
    setProperty("form", "userpane");
}

void CUserDetailPane::paintEvent(QPaintEvent *)
{
    QPainter painter(this);         // 创建画家对象
    painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform | QPainter::TextAntialiasing, true); // 抗锯齿和使用平滑转换算法

    QFont ft = painter.font();

    QRect rcClient = rect();
    rcClient.marginsRemoved(QMargins(0, 0, 0, 0));

    painter.translate(0, 0);  // 移动绘制原点
    painter.scale(rcClient.width() / 400.0, rcClient.height() / 470.0);

    QRect rectMain(0, 0, 400, 470);

    QRect rcImg(rectMain);
    rcImg.setBottom(rcImg.top() + 230);

    QPixmap p = QPixmap(":/qss/res/user_bg.png").scaled(rcImg.size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    painter.drawPixmap(rcImg, p);

    painter.save();
    painter.setPen(Qt::NoPen);
    painter.setBrush(QColor(255, 255, 255));
    QRect rcAvatarBg(20, 190, 77, 77);
    painter.drawEllipse(rcAvatarBg);

    QRect rcAvatar = rcAvatarBg.marginsRemoved(QMargins(5, 5, 5, 5));
    QPixmap p1 = QPixmap(":/qss/res/Avatar.png").scaled(rcAvatar.size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    painter.drawPixmap(rcAvatar, p1);
    painter.restore();

    QFont ftTemp = ft;
    ftTemp.setPointSize(15);
    ftTemp.setBold(true);
    painter.setFont(ftTemp);
    painter.setPen(QColor("#4DD9D5"));
    painter.drawText(QRect(160, 240, 220, 42), Qt::AlignRight | Qt::AlignVCenter, tr("阿木大叔"));
    painter.setFont(ft);

    int nItem = 0;
    const int nSpaceH = 42;

    {
        int nOffset = nItem * nSpaceH;

        painter.save();
        painter.setPen(QColor("#5D5D5F"));
        painter.drawText(QRect(20, 277 + nOffset, 307, 20), Qt::AlignLeft | Qt::AlignTop, tr("Qt"));

        QRect rcSlider1(20, 300 + nOffset, 307, 8);
        painter.setPen(Qt::NoPen);
        painter.setBrush(QColor("#E6EBF5"));
        painter.drawRoundedRect(rcSlider1, 5, 5);

        QRect rcSel(20, 300 + nOffset, 307 * 0.9, 8);
        painter.setPen(Qt::NoPen);
        painter.setBrush(QColor("#1890FF"));
        painter.drawRoundedRect(rcSel, 5, 5);
        painter.drawRect(rcSel.marginsRemoved(QMargins(5, 0, 0, 0)));

        painter.setPen(QColor("#5D5D5F"));
        painter.drawText(QRect(340, 295 + nOffset, 40, 40), Qt::AlignLeft | Qt::AlignTop, tr("90%"));

        painter.restore();

        nItem++;
    }

    {
        int nOffset = nItem * nSpaceH;

        painter.save();
        painter.setPen(QColor("#5D5D5F"));
        painter.drawText(QRect(20, 277 + nOffset, 307, 20), Qt::AlignLeft | Qt::AlignTop, tr("Qss"));

        QRect rcSlider1(20, 300 + nOffset, 307, 8);
        painter.setPen(Qt::NoPen);
        painter.setBrush(QColor("#E6EBF5"));
        painter.drawRoundedRect(rcSlider1, 5, 5);

        QRect rcSel(20, 300 + nOffset, 307 * 0.2, 8);
        painter.setPen(Qt::NoPen);
        painter.setBrush(QColor("#13CE66"));
        painter.drawRoundedRect(rcSel, 5, 5);
        painter.drawRect(rcSel.marginsRemoved(QMargins(5, 0, 0, 0)));

        painter.setPen(QColor("#5D5D5F"));
        painter.drawText(QRect(340, 295 + nOffset, 40, 40), Qt::AlignLeft | Qt::AlignTop, tr("20%"));

        painter.restore();

        nItem++;
    }

    {
        int nOffset = nItem * nSpaceH;

        painter.save();
        painter.setPen(QColor("#5D5D5F"));
        painter.drawText(QRect(20, 277 + nOffset, 307, 20), Qt::AlignLeft | Qt::AlignTop, tr("C++"));

        QRect rcSlider1(20, 300 + nOffset, 307, 8);
        painter.setPen(Qt::NoPen);
        painter.setBrush(QColor("#E6EBF5"));
        painter.drawRoundedRect(rcSlider1, 5, 5);

        QRect rcSel(20, 300 + nOffset, 307 * 0.95, 8);
        painter.setPen(Qt::NoPen);
        painter.setBrush(QColor("#FF9900"));
        painter.drawRoundedRect(rcSel, 5, 5);
        painter.drawRect(rcSel.marginsRemoved(QMargins(5, 0, 0, 0)));

        painter.setPen(QColor("#5D5D5F"));
        painter.drawText(QRect(340, 295 + nOffset, 40, 40), Qt::AlignLeft | Qt::AlignTop, tr("95%"));

        painter.restore();

        nItem++;
    }

    {
        int nOffset = nItem * nSpaceH;

        painter.save();
        painter.setPen(QColor("#5D5D5F"));
        painter.drawText(QRect(20, 277 + nOffset, 307, 20), Qt::AlignLeft | Qt::AlignTop, tr("Linux"));

        QRect rcSlider1(20, 300 + nOffset, 307, 8);
        painter.setPen(Qt::NoPen);
        painter.setBrush(QColor("#E6EBF5"));
        painter.drawRoundedRect(rcSlider1, 5, 5);

        QRect rcSel(20, 300 + nOffset, 307 * 0.8, 8);
        painter.setPen(Qt::NoPen);
        painter.setBrush(QColor("#E46CBB"));
        painter.drawRoundedRect(rcSel, 5, 5);
        painter.drawRect(rcSel.marginsRemoved(QMargins(5, 0, 0, 0)));

        painter.setPen(QColor("#5D5D5F"));
        painter.drawText(QRect(340, 295 + nOffset, 40, 40), Qt::AlignLeft | Qt::AlignTop, tr("80%"));

        painter.restore();

        nItem++;
    }

}

CUserPane::CUserPane(QWidget *parent) : QWidget(parent)
{
    m_pUserPane = NULL;

    setAttribute(Qt::WA_StyledBackground);              // 禁止父窗口样式影响子控件样式
    setProperty("form", "basedlg");
    setAttribute(Qt::WA_TranslucentBackground, true);

    CreateAllChildWnd();
    InitCtrl();
    Relayout();
}

void CUserPane::CreateAllChildWnd()
{
#define NEW_OBJECT(pObj, TYPE) \
    if (NULL == pObj) { pObj = new TYPE(this); }

    NEW_OBJECT(m_pUserPane, CUserDetailPane);
}

void CUserPane::InitCtrl()
{
    // 设置边框阴影
    this->setAttribute(Qt::WA_TranslucentBackground, true);
    // 设置具体阴影
    QGraphicsDropShadowEffect *shadowBorder = new QGraphicsDropShadowEffect(this);
    shadowBorder->setOffset(0, 0);
    // 阴影颜色
    shadowBorder->setColor(QColor(0x44, 0x44, 0x44, 127));
    // 阴影半径
    shadowBorder->setBlurRadius(8);
    setGraphicsEffect(shadowBorder);
}

void CUserPane::InitSolts()
{

}

void CUserPane::Relayout()
{
    QVBoxLayout *layoutMain = new QVBoxLayout();
    layoutMain->addWidget(m_pUserPane);
    layoutMain->setSpacing(8);
    layoutMain->setMargin(10);
    setLayout(layoutMain);
}
