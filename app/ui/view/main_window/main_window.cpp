#include "main_window.h"
#include "./ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(AuthMenu* authMenu, CallMenu* callMenu, ContactList* conMenu, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , authMenu(authMenu)
    , contactList(conMenu)
    , callMenu(callMenu)
{
    ui->setupUi(this);
    ui->verticalLayout->insertWidget(2, contactList);
    connect(contactList, &ContactList::callMenuShowRequested, this, &MainWindow::onCallMenuRequested);
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
    contactList->updateList();
}

void MainWindow::onCallMenuRequested(const QString &number)
{
    callMenu->setTextNumber(number);
    callMenu->exec();
}

void MainWindow::on_numberButton_clicked()
{
    callMenu->exec();
}

