#include "tipwidget.h"

TTipWidget *TTipWidget::m_pTipWidget = NULL;

TTipWidget::TTipWidget()
    : mpParent(nullptr)
    , mbEnter(false)
    , mnTransparent(200)
{
    setWindowFlags(Qt::Tool | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    setAlignment(Qt::AlignCenter);

    mpTimer = new QTimer(this);
    connect(mpTimer, &QTimer::timeout, this, &TTipWidget::OnTimer);

    setVisible(false);
}

TTipWidget::~TTipWidget()
{
    deleteLater();
}

void TTipWidget::enterEvent(QEvent *)
{
    mbEnter       = true;
    mnTransparent = 200;
    setStyleSheet(QString("color:white;font:12px \"Microsoft YaHei\";border-radius:5px;background-color:rgba(80, 80, 80, %1);").arg(mnTransparent));
}

void TTipWidget::leaveEvent(QEvent *)
{
    mbEnter = false;
}

void TTipWidget::OnTimer()
{
    if (mbEnter)
    {
        return;
    }

    mnTransparent -= 3;
    if (mnTransparent > 0)
    {
        if (mpParent && parentWidget())
        {
            QPoint pt((parentWidget()->width() - width()) >> 1, 40);
            if (pos() != pt)
            {
                move(pt);
            }
        }
        setStyleSheet(QString("color:white;font:12px \"Microsoft YaHei\";border-radius:5px;background-color:rgba(80, 80, 80, %1);").arg(mnTransparent));
    }
    else
    {
        mpTimer->stop();
        setVisible(false);
    }
}

void TTipWidget::SetMesseage(const QString &strMessage, const QPoint *pPoint)
{
    if (strMessage.isEmpty())
    {
        return;
    }

    QFontMetrics fm1(font());
    setFixedSize(fm1.width(strMessage) + 30, 30);

    mpParent = parentWidget();

    if (width() > mpParent->width())
    {
        setFixedSize(mpParent->width() - 60, 60);
        setWordWrap(true);
    }
    else
    {
        setWordWrap(false);
    }

    setText(strMessage);

    if (nullptr != mpParent)
    {
        if (nullptr != pPoint)
        {
            move(mpParent->mapFromGlobal(*pPoint));
            mpParent = nullptr;
        }
        else
        {
            move((mpParent->width() - width()) >> 1, 40);
        }
    }

    setVisible(true);
    mnTransparent = 200;

    mpTimer->start(30);
}

TTipWidget *TTipWidget::Instance()
{
    if (NULL == m_pTipWidget)
        m_pTipWidget = new TTipWidget();

    return m_pTipWidget;
}

void TTipWidget::ExitInstance()
{
    if (NULL != m_pTipWidget)
    {
        delete m_pTipWidget;
        m_pTipWidget = NULL;
    }
}
