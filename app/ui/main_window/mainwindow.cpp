#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QDebug>
#include "authmenupresenter.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , authMenu(this)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_authAction_triggered()
{
    AuthMenuPresenter authPres = AuthMenuPresenter(&authMenu, this);
    authMenu.exec();
}

