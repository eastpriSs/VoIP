#include "call_menu.h"
#include <QHBoxLayout>
#include <QDebug>
#include <QMessageBox>

CallMenu::CallMenu(QWidget *parent)
    : QDialog{parent}
{
    setWindowTitle("Меню вызова");
    setMinimumSize(400, 500);

    mainLayout = new QVBoxLayout(this);
    virtualKeyboardLayout = new QGridLayout();
    layoutSwitchLayout = new QHBoxLayout();

    statusBar = new QLabel(this);
    statusBar->setVisible(true);
    statusBar->setText("...");

    numberLine = new QLineEdit(this);
    numberLine->setMinimumHeight(40);

    confirmButton = new QPushButton("Вызов", this);
    confirmButton->setMinimumHeight(50);

    QHBoxLayout *controlLayout = new QHBoxLayout();
    backspaceButton = new QPushButton("⌫", this);
    clearButton = new QPushButton("Очистить", this);
    controlLayout->addWidget(backspaceButton);
    controlLayout->addWidget(clearButton);

    layoutButtonGroup = new QButtonGroup(this);
    switchNumbersButton = new QPushButton("123", this);
    switchLettersButton = new QPushButton("ABC", this);
    switchSymbolsButton = new QPushButton("#+@", this);

    layoutButtonGroup->addButton(switchNumbersButton, NUMBERS_LAYOUT_ID);
    layoutButtonGroup->addButton(switchLettersButton, LETTERS_LAYOUT_ID);
    layoutButtonGroup->addButton(switchSymbolsButton, SYMBOLS_LAYOUT_ID);

    layoutSwitchLayout->addWidget(switchNumbersButton);
    layoutSwitchLayout->addWidget(switchLettersButton);
    layoutSwitchLayout->addWidget(switchSymbolsButton);

    mainLayout->addWidget(numberLine);
    mainLayout->addLayout(controlLayout);
    mainLayout->addLayout(layoutSwitchLayout);
    mainLayout->addLayout(virtualKeyboardLayout);
    mainLayout->addWidget(confirmButton);
    mainLayout->addWidget(statusBar);

    connect(confirmButton, &QPushButton::clicked, this, &CallMenu::on_confirmButton_clicked);
    connect(backspaceButton, &QPushButton::clicked, this, &CallMenu::on_backspace_clicked);
    connect(clearButton, &QPushButton::clicked, this, &CallMenu::on_clear_clicked);
    connect(layoutButtonGroup, &QButtonGroup::idClicked, this, &CallMenu::on_layoutSwitch_clicked);

    setupNumbersLayout();
}

void CallMenu::setTextNumber(const QString &number) {
    numberLine->setText(number);
}

void CallMenu::clearTextNumber() {
    numberLine->clear();
}

void CallMenu::changeLayout(int layoutId) {
    if (layoutId == NUMBERS_LAYOUT_ID) setupNumbersLayout();
    else if (layoutId == LETTERS_LAYOUT_ID) setupLettersLayout();
    else if (layoutId == SYMBOLS_LAYOUT_ID) setupSymbolsLayout();
}

void CallMenu::showWarning(const QString &title, const QString &message) {
    QMessageBox::warning(this, title, message);
}

void CallMenu::showError(const QString &title, const QString &message)
{
    QMessageBox::critical(this, title, message);
}

void CallMenu::setStatusBarText(const QString &text)
{
    statusBar->setText(text);
}

void CallMenu::showIncomingCallMenu(const QString &text)
{
    incomingMenu = new IncomingCallMenu(this);
    incomingMenu->setCallerInfo(text);

    connect(incomingMenu, &IncomingCallMenu::acceptCall, this, &CallMenu::onAcceptCall);
    connect(incomingMenu, &IncomingCallMenu::rejectCall, this, &CallMenu::onRejectCall);

    incomingMenu->exec();
}

void CallMenu::onRequestCallingMenu()
{
    incomingMenu->onRequestCallingGui();
}

void CallMenu::onRequestRejectMenu()
{
    incomingMenu->onRequestRejectedGui();
}

void CallMenu::clearKeyboardLayout() {
    QLayoutItem *item;
    while ((item = virtualKeyboardLayout->takeAt(0)) != nullptr) {
        delete item->widget();
        delete item;
    }
}

void CallMenu::setupNumbersLayout() {
    clearKeyboardLayout();
    int number = 1;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            QPushButton* key = new QPushButton(QString::number(number++), this);
            key->setMinimumSize(80, 60);
            connect(key, &QPushButton::clicked, this, &CallMenu::on_virtualKeyboard_pressed);
            virtualKeyboardLayout->addWidget(key, i, j);
        }
    }
    QPushButton* zeroKey = new QPushButton("0", this);
    QPushButton* starKey = new QPushButton("*", this);
    QPushButton* hashKey = new QPushButton("#", this);

    zeroKey->setMinimumSize(80, 60);
    starKey->setMinimumSize(80, 60);
    hashKey->setMinimumSize(80, 60);

    connect(zeroKey, &QPushButton::clicked, this, &CallMenu::on_virtualKeyboard_pressed);
    connect(starKey, &QPushButton::clicked, this, &CallMenu::on_virtualKeyboard_pressed);
    connect(hashKey, &QPushButton::clicked, this, &CallMenu::on_virtualKeyboard_pressed);

    virtualKeyboardLayout->addWidget(starKey, 3, 0);
    virtualKeyboardLayout->addWidget(zeroKey, 3, 1);
    virtualKeyboardLayout->addWidget(hashKey, 3, 2);
}

IncomingCallMenu::IncomingCallMenu(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle("Входящий вызов");
    setMinimumSize(300, 200);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    callerLine = new QLineEdit(this);
    callerLine->setReadOnly(true);
    callerLine->setAlignment(Qt::AlignCenter);
    callerLine->setStyleSheet("font-size: 18px; font-weight: bold; border: none;");
    mainLayout->addWidget(callerLine);

    QHBoxLayout *btnLayout = new QHBoxLayout();

    acceptButton = new QPushButton("Ответить", this);
    acceptButton->setMinimumHeight(50);
    acceptButton->setStyleSheet("background-color: #28a745; color: white; font-weight: bold;");

    rejectButton = new QPushButton("Отклонить", this);
    rejectButton->setMinimumHeight(50);
    rejectButton->setStyleSheet("background-color: #dc3545; color: white; font-weight: bold;");

    btnLayout->addWidget(acceptButton);
    btnLayout->addWidget(rejectButton);
    mainLayout->addLayout(btnLayout);

    connect(acceptButton, &QPushButton::clicked, this, &IncomingCallMenu::acceptCall);
    connect(rejectButton, &QPushButton::clicked, this, &IncomingCallMenu::rejectCall);
}

void IncomingCallMenu::setCallerInfo(const QString &info) {
    callerLine->setText(info);
}

void IncomingCallMenu::onRequestCallingGui()
{

}

void IncomingCallMenu::onRequestRejectedGui()
{

}

void CallMenu::setupLettersLayout() {
    clearKeyboardLayout();
    QString letters = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    int cols = 6;
    int row = 0, col = 0;
    for (QChar letter : letters) {
        QPushButton* key = new QPushButton(QString(letter), this);
        key->setMinimumSize(50, 50);
        connect(key, &QPushButton::clicked, this, &CallMenu::on_virtualKeyboard_pressed);
        virtualKeyboardLayout->addWidget(key, row, col);
        col++;
        if (col >= cols) { col = 0; row++; }
    }
}

void CallMenu::setupSymbolsLayout() {
    clearKeyboardLayout();
    QStringList symbols = {"@", ".", "-", "+", "_", ":", "/", ";", "=", "?", "&", "!", "#", "*", "(", ")"};
    int cols = 5;
    int row = 0, col = 0;
    for (const QString &symbol : symbols) {
        QPushButton* key = new QPushButton(symbol, this);
        key->setMinimumSize(60, 50);
        connect(key, &QPushButton::clicked, this, &CallMenu::on_virtualKeyboard_pressed);
        virtualKeyboardLayout->addWidget(key, row, col);
        col++;
        if (col >= cols) { col = 0; row++; }
    }
}

void CallMenu::on_virtualKeyboard_pressed() {
    QPushButton* btn = qobject_cast<QPushButton*>(sender());
    if (btn) emit keyPressed(btn->text());
}

void CallMenu::on_confirmButton_clicked() {
    emit confirmPressed(numberLine->text());
}

void CallMenu::on_layoutSwitch_clicked(int layoutId) {
    emit layoutSwitchRequested(layoutId);
}

void CallMenu::on_backspace_clicked() {
    emit backspacePressed();
}

void CallMenu::on_clear_clicked() {
    emit clearPressed();
}

void CallMenu::onAcceptCall()
{
    emit callAccepted();
}

void CallMenu::onRejectCall()
{
    emit callRejected();
}
