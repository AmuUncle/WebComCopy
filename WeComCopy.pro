#-------------------------------------------------
#
# Project created by QtCreator 2021-05-20T14:15:42
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = WeComCopy
TEMPLATE = app
DESTDIR = bin

INCLUDEPATH += include

SOURCES += source/main.cpp\
        source/wecomwnd.cpp \
    source/navpane.cpp \
    source/pushbuttonex.cpp \
    source/iconhelper.cpp \
    source/appinit.cpp \
    source/userdetaildlg.cpp \
    source/basedlg.cpp \
    logindlg.cpp

HEADERS  += include/wecomwnd.h \
    include/navpane.h \
    include/pushbuttonex.h \
    include/iconhelper.h \
    include/appinit.h \
    include/userdetaildlg.h \
    public.h \
    include/basedlg.h \
    logindlg.h

FORMS    += ui/wecomwnd.ui

RESOURCES += \
    res/wecomcopy.qrc

RC_FILE +=  \
    res/WeComCopy.rc
