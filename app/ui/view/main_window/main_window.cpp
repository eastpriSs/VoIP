#include "main_window.h"
#include "./ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(AuthMenu* authMenu, ContactList* conMenu, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , authMenu(authMenu)
    , contactList(conMenu)
{
    ui->setupUi(this);
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
    contactList->updateList();
    // todo: здесь будет обновление списка(запрос данных)
}

