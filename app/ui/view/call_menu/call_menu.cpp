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
