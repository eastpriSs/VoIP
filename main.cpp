#include "mainwindow.h"
#include <opus/opus.h>
#include <pjsua2.hpp>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
