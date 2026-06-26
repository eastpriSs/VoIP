#include "authmenu.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

AuthMenu::AuthMenu(QWidget *parent)
    : QDialog(parent) {
    setWindowTitle("Авторизация / Регистрация");

    usernameEdit = new QLineEdit;
    passwordEdit = new QLineEdit;
    passwordEdit->setEchoMode(QLineEdit::Password);

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
                           passwordEdit->text().trimmed());
}
