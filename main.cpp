#include "mainwindow.h"
#include <opus/opus.h>
#include <pjsua2.hpp>
#include <QApplication>
#include <QLocale>

int main(int argc, char *argv[])
{
    QLocale::setDefault(QLocale("en_US"));
    qputenv("QT_IM_MODULE", QByteArray("qtvirtualkeyboard"));

    // Принудительно используем X11/Xwayland вместо Wayland для Fedora 40
    qputenv("QT_QPA_PLATFORM", QByteArray("xcb"));

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
