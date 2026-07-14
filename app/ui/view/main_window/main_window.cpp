#include "main_window.h"
#include "./ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(AuthMenu* authMenu, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , authMenu(authMenu)
{
    ui->setupUi(this);
    contactList = new ContactList(this);
    ui->verticalLayout->insertWidget(2, contactList);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_authAction_triggered()
{
    authMenu->exec();
}

void MainWindow::on_contactsButton_clicked()
{
    contactList->uploadList();
}

