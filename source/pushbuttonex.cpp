#include "pushbuttonex.h"
#include <QMouseEvent>
#include <QPainter>

CPushButtonEx::CPushButtonEx(QWidget *parent) : QPushButton(parent)
{
    m_varData = 0;
    m_bExArea = false;

    setCursor(Qt::PointingHandCursor); //设置鼠标样式
}

CPushButtonEx::~CPushButtonEx()
{

}

void CPushButtonEx::mouseReleaseEvent( QMouseEvent *e )
{
    if (!m_bExArea)
        return QPushButton::mouseReleaseEvent(e);

    QRect rcEx = rect();
    rcEx.setTopLeft(QPoint(rcEx.bottom() / 4 * 3, rcEx.right() / 4 * 3));

    if (!rcEx.contains(e->pos()))
        emit SignalClicked();
    else
        emit SignalClickedExArea();

    return QPushButton::mouseReleaseEvent(e);
}
