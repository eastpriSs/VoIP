#include "main_window.h"
#include "./ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(AuthMenu* authMenu, CallMenu* callMenu, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , authMenu(authMenu)
    , callMenu(callMenu)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_authAction_triggered()
{
    authMenu->exec();
}


void MainWindow::on_numberButton_clicked()
{
    callMenu->exec();
}

