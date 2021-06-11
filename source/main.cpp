#include "wecomwnd.h"
#include <QApplication>
#include <QFile>
#include "iconhelper.h"
#include "appinit.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QFont f = QFont("Microsoft Yahei", 9);
//    int nFontId = QFontDatabase::addApplicationFont("consolas.ttf");
//    QStringList strlistFontName = QFontDatabase::applicationFontFamilies(nFontId);

//    if (strlistFontName.count() > 0)
//    {
//        f = QFont(strlistFontName.at(0), 9);
//        f.setStyleStrategy(QFont::PreferAntialias);
//    }

    f.setStyleStrategy(QFont::PreferAntialias);
    a.setFont(f);

    QApplication::setQuitOnLastWindowClosed(false);

    //更改程序启动后任务栏图标
    a.setWindowIcon(QIcon(":/qss/res/WeComCopy.png"));

    //加载样式表
    QFile file(":/qss/res/WeComCopy.css");
    if (file.open(QFile::ReadOnly))
    {
        QString qss = QLatin1String(file.readAll());
        QString paletteColor = qss.mid(20, 7);
        qApp->setPalette(QPalette(QColor(paletteColor)));
        qApp->setStyleSheet(qss);
        file.close();
    }

    AppInit::Instance()->start();
    IconHelper::Load();

    WeComWnd w;
    w.hide();
    w.Login();

    return a.exec();
}
