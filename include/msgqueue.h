/**
 * @file      msgqueue.h
 * @brief     消息队列
 * @author    岳甲寅
 * @date      2020-10-21
 * @version   1.0
 * @copyright Copyright(C) 2020 NVR All rights reserved.
 */

#ifndef MSGQUEUE_H
#define MSGQUEUE_H

#include <QThread>
#include <QMutex>

struct TMsgItem
{
//    u32 dwHandle;
//    u16 wMsgId;
//    void *pBuf;
//    u32 dwBufLen;
};

class CMsgQueue : public QThread
{
    Q_OBJECT

public:
    explicit CMsgQueue(QObject *parent = 0);
    virtual ~CMsgQueue();

public:
    static CMsgQueue *GetInstance();
    static void ExitInstance();

    bool Push(QString item);

protected:
    void run();
    void Clear();

signals:
    void SignalRecvMsg(QByteArray msg);

private:
    static CMsgQueue *m_pMsgQueue;
    QList<QString> m_listMsg;
    QMutex m_mutex;
};

#define MSGQUEUE CMsgQueue::GetInstance()

#endif // CMSGQUEUE_H
