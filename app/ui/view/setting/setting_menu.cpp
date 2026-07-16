#include "setting_menu.h"
#include <QFormLayout>
#include <QVBoxLayout>

SettingMenu::SettingMenu(QWidget *parent) : QDialog(parent)
{
    clientIdEdit = new QLineEdit(this);

    clientSecretEdit = new QLineEdit(this);
    clientSecretEdit->setEchoMode(QLineEdit::Password);

    httpServerEdit = new QLineEdit(this);
    httpServerEdit->setPlaceholderText("http://");

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
    emit settingsSubmitted(clientIdEdit->text(),
                           clientSecretEdit->text(),
                           httpServerEdit->text());

    accept();
}

void SettingMenu::setInitialSettings(const QString &clientId, const QString &clientSecret, const QString &httpServer)
{
    clientIdEdit->setText(clientId);
    clientSecretEdit->setText(clientSecret);
    httpServerEdit->setText(httpServer);
}
