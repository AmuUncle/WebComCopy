/**
 * @file      iconhelper.h
 * @brief     字体图标
 * @author    胡德杰
 * @date      2020-10-27
 * @version   1.0
 * @copyright Copyright(C) 2020 NVR All rights reserved.
 */

#ifndef ICONHELPER_H
#define ICONHELPER_H

#include <QPushButton>
#include <QToolButton>
#include <QAction>
#include <QLabel>
#include <QStandardItem>

class IconHelper : public QObject
{
    Q_OBJECT

public:
    static bool Load();
    static void SetIcon(QLabel *label, QChar iconCode, uint dwSize = 26);
    static void SetIcon(QPushButton *btn, QChar iconCode, uint dwSize = 20);
    static void SetIcon(QPushButton *btn, QChar iconCode, const QString &strColor, uint dwSize = 20);
    static void SetIcon(QToolButton *btn, QChar iconCode, const QString &strColor = "#FFFFFF", uint dwIconSize = 26);
    static void SetIcon(QAction *action, QChar iconCode, const QString &strColor = "#000000", uint dwIconSize = 40);
    static void SetIcon(QLabel *label, const QString &strMainIcon = "", const QString &strSecIcon = "", const QString &strThirdIcon = "", uint dwIconSize = 24);
    static void SetIcon(QStandardItem *item, QChar iconCode, uint dwSize = 26);

    static QPixmap GetPixmap(const QString &strColor, QChar iconCode, uint dwSize, uint dwPixWidth, uint dwPixHeight);

    // 生成三张叠加在一起的图片，主图为背景，辅图在右下角
    static QPixmap GetPixmap(const QString &strMainIcon, const QString &strSecIcon, const QString &strThirdIcon, uint dwPixWidth, uint dwPixHeight);

    static QPixmap GetDragChnPixmap( QString strText );

    static QFont GetFont() { return m_iconFont; }

private:
    static QFont m_iconFont;                    // 图形字体
};

#endif // ICONHELPER_H
