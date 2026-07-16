#include "main_window.h"
#include "./ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(AuthMenu* authMenu, CallMenu* callMenu, SettingMenu* settMenu, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , authMenu(authMenu)
    , callMenu(callMenu)
    , settMenu(settMenu)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::appendRecentCall(QString record)
{
    ui->recentList->addItem(record);
}

void MainWindow::on_authAction_triggered()
{
    authMenu->exec();
}

void MainWindow::on_numberButton_clicked()
{
    callMenu->exec();
}

void MainWindow::on_clientAction_triggered()
{
    settMenu->exec();
}

