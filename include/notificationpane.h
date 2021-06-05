#ifndef NOTIFICATIONPANE_H
#define NOTIFICATIONPANE_H

#include <QWidget>
#include <QTimer>


const uint MAX_NOTICE = 10;

class NotificationPane : public QWidget
{
    Q_OBJECT
public:
    explicit NotificationPane(QWidget *parent = 0);

public:
    void SetId(int nIndex) { m_nIndex = nIndex; }
    int GetId() { return m_nIndex; }
    void Start(int msec);

private:
    void enterEvent(QEvent *event);
    void leaveEvent(QEvent *event);

signals:
    void SignalHide(int nIndex);

public slots:
    void OnTimerHideTimeOut();

private:
    QTimer *m_pTimerHide;
    int m_nIndex;
};


class NotificationMgr : public QObject
{
    Q_OBJECT
public:
    explicit NotificationMgr(QWidget *parent = 0);

public:
    static void Init(QWidget *parent = 0);
    static NotificationMgr *GetInstance();
    static void ExitInstance();

    void Notice(QString strContent);

private:
    void ShowAll();

public slots:
    void OnItemHide(int nIndex);

private:
    struct TNoteItem
    {
        NotificationPane *pNotificationPane;
        bool bShow;
        int nInterval;

        TNoteItem()
        {
            pNotificationPane = NULL;
            bShow = false;
            nInterval = 4500;
        }
    };

    static NotificationMgr *m_pNotificationMgr;
    QList<TNoteItem> m_listNotification;
    QMutex m_mutex;
};

#endif // NOTIFICATIONPANE_H
