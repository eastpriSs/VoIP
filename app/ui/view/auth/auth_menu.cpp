#include "auth_menu.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QIntValidator>

AuthMenu::AuthMenu(QWidget *parent)
    : QDialog(parent) {
    setWindowTitle("Авторизация / Регистрация");

    usernameEdit = new QLineEdit;
    passwordEdit = new QLineEdit;
    passwordEdit->setEchoMode(QLineEdit::Password);

    sipServerEdit = new QLineEdit;
    sipServerEdit->setPlaceholderText("например: sip.example.com");

    sipPortEdit = new QLineEdit;
    sipPortEdit->setPlaceholderText("5060");
    sipPortEdit->setValidator(new QIntValidator(1, 65535, this));
    sipPortEdit->setText("5060");

    loginButton = new QPushButton("Войти");
    registerButton = new QPushButton("Зарегистрироваться");
    cancelButton = new QPushButton("Отмена");
    statusLabel = new QLabel;
    statusLabel->setStyleSheet("color: red;");

    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    mainLayout->addWidget(new QLabel("Логин:"));
    mainLayout->addWidget(usernameEdit);
    mainLayout->addWidget(new QLabel("Пароль:"));
    mainLayout->addWidget(passwordEdit);

    QLabel* sipLabel = new QLabel("SIP сервер (для регистрации):");
    mainLayout->addWidget(sipLabel);
    mainLayout->addWidget(sipServerEdit);

    QLabel* portLabel = new QLabel("SIP порт (для регистрации):");
    mainLayout->addWidget(portLabel);
    mainLayout->addWidget(sipPortEdit);

    mainLayout->addWidget(statusLabel);

    QHBoxLayout *btnLayout = new QHBoxLayout;
    btnLayout->addStretch();
    btnLayout->addWidget(loginButton);
    btnLayout->addWidget(registerButton);
    btnLayout->addWidget(cancelButton);
    mainLayout->addLayout(btnLayout);

    connect(loginButton, &QPushButton::clicked,
            this, &AuthMenu::onLoginButtonClicked);
    connect(registerButton, &QPushButton::clicked,
            this, &AuthMenu::onRegisterButtonClicked);
    connect(cancelButton, &QPushButton::clicked,
            this, &AuthMenu::reject);
}

AuthMenu::~AuthMenu() {}

void AuthMenu::onLoginButtonClicked() {
    emit loginRequested(usernameEdit->text().trimmed(),
                        passwordEdit->text().trimmed());
}

void AuthMenu::onRegisterButtonClicked() {
    emit registerRequested(usernameEdit->text().trimmed(),
                           passwordEdit->text().trimmed(),
                           sipServerEdit->text().trimmed(),
                           sipPortEdit->text().toInt());
}
