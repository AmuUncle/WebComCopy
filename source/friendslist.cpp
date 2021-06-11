﻿#include "friendslist.h"
#include <QVariant>
#include "public.h"

CFriendsList::CFriendsList(QWidget *parent) : QWidget(parent)
{
    m_lineEditSearch = NULL;
    m_labSearch = NULL;
    m_btnAdd = NULL;
    m_listwidgetFriends = NULL;
    m_listwidgetContacts = NULL;

    CreateAllChildWnd();
    InitCtrl();
    InitSolts();
    Relayout();
}

void CFriendsList::SetContactMode(bool bContacts)
{
    m_listwidgetContacts->setVisible(bContacts);
    m_listwidgetFriends->setVisible(!bContacts);
}

void CFriendsList::OnItemClicked( QListWidgetItem *item, QListWidgetItem *previous )
{
    TUserInfo tUserInfo = {0};

    tUserInfo.strName = item->data(Qt::UserRole).toString();
    tUserInfo.strEmail = "hudejie2018@163.com";
    tUserInfo.strPart = tr("设计部");
    tUserInfo.strAvatar = item->data(Qt::UserRole + 1).toString();
    emit SignalFriendChange(tUserInfo);
}

void CFriendsList::CreateAllChildWnd()
{
#define NEW_OBJECT(pObj, TYPE) \
    if (NULL == pObj) { pObj = new TYPE(this); }

    NEW_OBJECT(m_lineEditSearch, QLineEdit);
    NEW_OBJECT(m_labSearch, QLabel);
    NEW_OBJECT(m_btnAdd, CPushButtonEx);
    NEW_OBJECT(m_listwidgetFriends, QListWidget);
    NEW_OBJECT(m_listwidgetContacts, QTreeWidget);
}

void CFriendsList::InitCtrl()
{
    setAttribute(Qt::WA_StyledBackground);  // 禁止父窗口样式影响子控件样式
    setProperty("form", "friendlist");

    m_labSearch->setFixedSize(22, 22);
    IconHelper::SetIcon(m_labSearch, QChar(0xe63c), 16);
    m_labSearch->setStyleSheet("color:#5D646C");

    m_btnAdd->setFixedSize(26, 26);
    IconHelper::SetIcon(m_btnAdd, QChar(0xe649), "#575E66", 22);

    QMargins margins = m_lineEditSearch->textMargins();
    m_lineEditSearch->setTextMargins(m_labSearch->width(), margins.top(), margins.right(), margins.bottom());
    m_lineEditSearch->setPlaceholderText(tr("搜索"));

    QHBoxLayout *pSearchLayout = new QHBoxLayout();
    pSearchLayout->addWidget(m_labSearch);
    pSearchLayout->addStretch();
    pSearchLayout->setSpacing(0);
    pSearchLayout->setContentsMargins(0, 0, 0, 0);
    m_lineEditSearch->setLayout(pSearchLayout);

    InitList();
    InitTree();
}

void CFriendsList::InitList()
{
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));

    QStringList strListName;
    strListName << "小沙弥" << "木华黎" << "丘处机" << "沈青刚" << "书记" << "一灯大师" <<
                   "书生" << "王处一" << "王罕" << "尹志平" << "包惜弱" << "冯衡" << "术赤" << "天竺僧人" <<
                   "孙不二" << "札木合" << "华筝" << "李萍" << "刘玄处" << "刘瑛姑" << "吕文德" << "完颜洪烈" <<
                   "乔寨主" << "曲三" << "曲傻姑" << "全金发" << "汤祖德" << "朱聪" << "陈玄风" << "完颜洪熙" <<
                   "陆乘风" << "陆冠英" << "沙通天" << "农夫" << "吴青烈" << "赤老温" << "杨康" << "灵智上人";

    QStringList strListMsg;
    strListMsg << "今晚出来聚餐..." << "周末加班..." << "不说了，说多了都是泪..." << "哦哦，好的，3Q" << "第一个不加不行啊" << "好的" <<
                   "这个估计当时没看具体逻辑..." << "https://gitee.com/hudejie/wecom-copy..." << "好" << "8.1.3  8.1.4" << "[图片]"
               << "非法参数1005" << "回来的吧" << "ok" << "四楼来拿" << "我一直没弄" << "web正常显示的";

    QStringList strListTime;
    strListTime << "16:34" << "08:21" << "10:45" << "18:57" << "01:21" << "17:44" <<
                   "昨天" << "32分钟前" << "星期一" << "星期二" << "星期三"
               << "星期四" << "星期五" << "星期六" << "星期天" << "5/21" << "3/12" << "2012/4/21" << "刚刚";

    for (int i = 1; i <= 108; i++)
    {
        QListWidgetItem *item = new QListWidgetItem;
        item->setSizeHint(QSize(10, 65));
        m_listwidgetFriends->addItem(item);

        QWidget *pItemWidget = new QWidget(m_listwidgetFriends);
        CPushButtonEx *pLabelIcon = new CPushButtonEx(pItemWidget);
        QLabel *pLabelName = new QLabel(pItemWidget);
        QLabel *pLabelMsg = new QLabel(pItemWidget);
        QLabel *pLabelTime = new QLabel(pItemWidget);

        int nIconIndex = qrand() % 10;
        nIconIndex = qMax(nIconIndex, 1);

        pLabelIcon->setFixedSize(40, 40);
        pLabelIcon->setIcon(QIcon(QString(":/icon/icon/user (%1).jpg").arg(nIconIndex)));
        pLabelIcon->setIconSize(pLabelIcon->size());
        pLabelIcon->setCursor(Qt::ArrowCursor); //设置鼠标样式

        int nNameIndex = qrand() % strListName.length();

        pLabelName->setText(strListName.at(nNameIndex));
        pLabelName->setStyleSheet("font: 14px; color:#000000;");

        int nTimeIndex = qrand() % strListTime.length();
        pLabelTime->setText(strListTime.at(nTimeIndex));

        pLabelTime->setStyleSheet("font: 11px; color:#A4A5A7;");
        pLabelTime->setAlignment(Qt::AlignRight);

        int nMsgIndex = qrand() % strListMsg.length();
        pLabelMsg->setText(strListMsg.at(nMsgIndex));
        pLabelMsg->setStyleSheet("font: 12px; color:#A4A5A7;");

        item->setData(Qt::UserRole, pLabelName->text());
        item->setData(Qt::UserRole + 1, QString(":/icon/icon/user (%1).jpg").arg(nIconIndex));

        QHBoxLayout *layoutMsg = new QHBoxLayout();
        layoutMsg->addWidget(pLabelMsg);
        layoutMsg->addStretch();
        layoutMsg->addWidget(pLabelTime);
        layoutMsg->setSpacing(8);
        layoutMsg->setContentsMargins(0, 0, 6, 0);

        QVBoxLayout *layoutRight = new QVBoxLayout();
        layoutRight->addWidget(pLabelName);
        layoutRight->addLayout(layoutMsg);
        layoutRight->setSpacing(0);
        layoutRight->setContentsMargins(0, 10, 0, 10);

        QHBoxLayout *layoutMain = new QHBoxLayout(pItemWidget);
        layoutMain->addWidget(pLabelIcon);
        layoutMain->addLayout(layoutRight);
        layoutMain->setContentsMargins(15, 0, 0, 0);

        m_listwidgetFriends->setItemWidget(item, pItemWidget);
    }

    m_listwidgetFriends->setCurrentRow(0);

    QTimer::singleShot(200, this, [&]()
    {
        OnItemClicked(m_listwidgetFriends->currentItem(), m_listwidgetFriends->currentItem());
    });
}

void CFriendsList::InitTree()
{
    m_listwidgetContacts->hide();
    m_listwidgetContacts->setHeaderHidden(true);

    // 清空原有数据
    m_listwidgetContacts->clear();
    m_listwidgetContacts->setIndentation(0);

    QTreeWidgetItem* pItem = new QTreeWidgetItem();
    pItem->setText(0, tr("124"));

    QStringList strings;
    strings<< tr("124") << tr("1245") << tr("1246");
    QTreeWidgetItem* pItemChild = new QTreeWidgetItem(strings);
    pItem->addChild(pItemChild);

    m_listwidgetContacts->addTopLevelItem(pItem);

}

void CFriendsList::InitSolts()
{
    connect(m_listwidgetFriends, SIGNAL(currentItemChanged(QListWidgetItem*, QListWidgetItem*)), this, SLOT(OnItemClicked(QListWidgetItem*, QListWidgetItem *)));
}

void CFriendsList::Relayout()
{
    QHBoxLayout *layoutSearch = new QHBoxLayout();
    layoutSearch->addWidget(m_lineEditSearch);
    layoutSearch->addWidget(m_btnAdd);
    layoutSearch->setSpacing(10);
    layoutSearch->setContentsMargins(15, 6, 10, 6);

    QVBoxLayout *layoutMain = new QVBoxLayout();
    layoutMain->addLayout(layoutSearch);
    layoutMain->addWidget(m_listwidgetFriends);
    layoutMain->addWidget(m_listwidgetContacts);
    layoutMain->setSpacing(0);
    layoutMain->setMargin(0);

    setLayout(layoutMain);
}
