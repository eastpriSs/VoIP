#include "auth_menu.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QIntValidator>
#include <QMessageBox>
#include <QProgressBar>

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
\
    progressBar = new QProgressBar;
    progressBar->setVisible(false);

    /*
     *  Проценты:
        25 - Валидация данных
        50 - Отправка запроса
        75 - Получение ответа
        100 - успешная регистрация
    */
    progressBar->setRange(0, 100);
    progressBar->setValue(0);

    bottomStatusLabel = new QLabel("...");
    bottomStatusLabel->setStyleSheet("color: gray; font-size: 11px; padding-top: 5px;");

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

    mainLayout->addWidget(progressBar);

    QHBoxLayout *btnLayout = new QHBoxLayout;
    btnLayout->addStretch();
    btnLayout->addWidget(loginButton);
    btnLayout->addWidget(registerButton);
    btnLayout->addWidget(cancelButton);
    mainLayout->addLayout(btnLayout);

    mainLayout->addWidget(bottomStatusLabel);

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
    setProgress(0);
}

void AuthMenu::onRegisterFailed(QString err_text) {
    QMessageBox::critical(this, tr("Ошибка регистрации"),
                          tr(err_text.toStdString().c_str()),
                          QMessageBox::Close);
}

void AuthMenu::onRegisterSucces(QString text) {
    QMessageBox::information(this, tr("Успешная регистрация"),
                             tr(text.toStdString().c_str()),
                             QMessageBox::Close);
}

void AuthMenu::onProgressChanged(QString status, int value)
{
    setProgressVisible(true);
    setProgress(progressBar->value() + value);
    setBottomStatus(status);
}


void AuthMenu::setProgress(int value) {
    progressBar->setValue(value);
    if (value >= 100) {
        progressBar->setVisible(false);
    }
}

void AuthMenu::setProgressVisible(bool visible) {
    progressBar->setVisible(visible);
    if (visible) {
        progressBar->reset();
    }
}

void AuthMenu::setBottomStatus(const QString& text) {
    bottomStatusLabel->setText(text);
}
