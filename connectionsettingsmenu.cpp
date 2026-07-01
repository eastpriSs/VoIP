#include "connectionsettingsmenu.h"
#include <QLineEdit>
#include <QComboBox>
#include <QLabel>

ConnectionSettingsMenu::ConnectionSettingsMenu(QWidget *parent)
    : QDialog{parent}
{
    setWindowTitle("Настройки подключения");

    mainLayout = new QVBoxLayout(this);

    // Протокол подключения
    protocolLayout = new QHBoxLayout(this);
    protocolLayout->addWidget(new QLabel("Протокол подключения:", this));
    QComboBox* protocolCmb = new QComboBox(this);
    protocolCmb->addItems({"TCP", "UDP"});
    protocolLayout->addWidget(protocolCmb);


    // Отображаемое имя пользователя
    usernameLayout = new QHBoxLayout(this);
    usernameLayout->addWidget(new QLabel("Отображаемое имя пользователя:", this));
    QLineEdit* usernameLine = new QLineEdit(this);
    usernameLayout->addWidget(usernameLine);


    mainLayout->addLayout(usernameLayout);
    mainLayout->addWidget(new QLabel("Настройки для профи:"));
    mainLayout->addLayout(protocolLayout);
}
