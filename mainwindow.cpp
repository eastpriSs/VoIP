#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QDebug>
#include "authmenupresenter.h"
#include "numbermenupresenter.h"
#include "connectionsettingsmenu.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , authMenu(this)
    , numberMenu(this)
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


void MainWindow::on_numberButton_clicked()
{
    NumberMenuPresenter nmp = NumberMenuPresenter(&numberMenu, this);
    numberMenu.exec();
}


void MainWindow::on_actionSettings_triggered()
{
    ConnectionSettingsMenu cm = ConnectionSettingsMenu(this);
    cm.exec();
}

