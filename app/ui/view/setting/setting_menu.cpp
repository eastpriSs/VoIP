// setting_menu.cpp
#include "setting_menu.h"
#include <QFormLayout>
#include <QVBoxLayout>
#include <QMessageBox>

SettingMenu::SettingMenu(QWidget *parent) : QDialog(parent)
{
    clientIdEdit = new QLineEdit(this);
    clientSecretEdit = new QLineEdit(this);
    clientSecretEdit->setEchoMode(QLineEdit::Password);
    httpServerEdit = new QLineEdit(this);
    httpServerEdit->setPlaceholderText("https://");

    submitButton = new QPushButton(tr("Сохранить"), this);

    QFormLayout *formLayout = new QFormLayout();
    formLayout->addRow(tr("ID клиента:"), clientIdEdit);
    formLayout->addRow(tr("SECRET клиента:"), clientSecretEdit);
    formLayout->addRow(tr("HTTP сервер:"), httpServerEdit);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addLayout(formLayout);
    mainLayout->addWidget(submitButton);

    connect(submitButton, &QPushButton::clicked, this, &SettingMenu::onSubmitClicked);
}

void SettingMenu::onSubmitClicked()
{
    emit submitRequested(clientIdEdit->text(),
                         clientSecretEdit->text(),
                         httpServerEdit->text());
}

void SettingMenu::setInitialSettings(const QString &clientId, const QString &clientSecret, const QString &httpServer)
{
    clientIdEdit->setText(clientId);
    clientSecretEdit->setText(clientSecret);
    httpServerEdit->setText(httpServer);
}

void SettingMenu::showValidationError(const QString &message)
{
    QMessageBox::critical(this, tr("Ошибка ввода"), message);
}

void SettingMenu::closeOnSuccess()
{
    this->accept();
}
