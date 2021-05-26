#ifndef PUBLIC_H
#define PUBLIC_H

#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif

#include "iconhelper.h"

enum EMainTabTitle
{
    TABTITLE_MESSAGE = 0,       // 消息会话
    TABTITLE_CONTACTS = 1,      // 通讯录
    TABTITLE_CALENDAR = 2,      // 日程
    TABTITLE_WORKSPACE = 3,       // 工作台
    TABTITLE_WEDOC = 4,      // 微文档
    TABTITLE_WEDRIVE = 5,      // 微盘
    TABTITLE_MEETING = 6,      // 会议
};


struct TUserInfo
{
    QString strName;
    QString strPart;
    QString strEmail;
    QString strAvatar;
    // ...
};

#endif // PUBLIC_H
