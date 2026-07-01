#include "numbermenu.h"
#include <QHBoxLayout>
#include <QDebug>

NumberMenu::NumberMenu(QWidget *parent)
    : QDialog{parent}
{
    setWindowTitle("Набор номера");
    setMinimumSize(400, 500);

    mainLayout = new QVBoxLayout(this);
    virtualKeyboardLayout = new QGridLayout();
    layoutSwitchLayout = new QHBoxLayout();

    numberLine = new QLineEdit(this);
    numberLine->setMinimumHeight(40);

    confirmButton = new QPushButton("Вызов", this);
    confirmButton->setMinimumHeight(50);

    // Кнопки управления вводом
    QHBoxLayout *controlLayout = new QHBoxLayout();
    backspaceButton = new QPushButton("⌫", this);
    clearButton = new QPushButton("Очистить", this);
    controlLayout->addWidget(backspaceButton);
    controlLayout->addWidget(clearButton);

    // Кнопки переключения раскладок
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

    // Сборка основного layout
    mainLayout->addWidget(numberLine);
    mainLayout->addLayout(controlLayout);
    mainLayout->addLayout(layoutSwitchLayout);
    mainLayout->addLayout(virtualKeyboardLayout);
    mainLayout->addWidget(confirmButton);

    connect(confirmButton, &QPushButton::clicked, this, &NumberMenu::on_confirmButton_clicked);
    connect(backspaceButton, &QPushButton::clicked, this, &NumberMenu::on_backspace_clicked);
    connect(clearButton, &QPushButton::clicked, this, &NumberMenu::on_clear_clicked);
    connect(layoutButtonGroup, &QButtonGroup::idClicked, this, &NumberMenu::on_layoutSwitch_clicked);

    setupNumbersLayout();
}

void NumberMenu::insertInTextNumber(QString&& s)
{
    numberLine->insert(s);
}

void NumberMenu::clearTextNumber()
{
    numberLine->clear();
}

void NumberMenu::setTextNumber(const QString &number)
{
    numberLine->setText(number);
}

void NumberMenu::setTextNumber(QString &&number)
{
    numberLine->setText(std::move(number));
}

QString NumberMenu::getTextNumber()
{
    return numberLine->text();
}

void NumberMenu::clearKeyboardLayout()
{
    QLayoutItem *item;
    while ((item = virtualKeyboardLayout->takeAt(0)) != nullptr) {
        delete item->widget();
        delete item;
    }
}

void NumberMenu::setupNumbersLayout()
{
    clearKeyboardLayout();

    int number = 1;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            QPushButton* key = new QPushButton(QString::number(number++), this);
            key->setMinimumSize(80, 60);
            connect(key, &QPushButton::clicked, this, &NumberMenu::on_virtualKeyboard_pressed);
            virtualKeyboardLayout->addWidget(key, i, j);
        }
    }

    QPushButton* zeroKey = new QPushButton("0", this);
    QPushButton* starKey = new QPushButton("*", this);
    QPushButton* hashKey = new QPushButton("#", this);

    zeroKey->setMinimumSize(80, 60);
    starKey->setMinimumSize(80, 60);
    hashKey->setMinimumSize(80, 60);

    connect(zeroKey, &QPushButton::clicked, this, &NumberMenu::on_virtualKeyboard_pressed);
    connect(starKey, &QPushButton::clicked, this, &NumberMenu::on_virtualKeyboard_pressed);
    connect(hashKey, &QPushButton::clicked, this, &NumberMenu::on_virtualKeyboard_pressed);

    virtualKeyboardLayout->addWidget(starKey, 3, 0);
    virtualKeyboardLayout->addWidget(zeroKey, 3, 1);
    virtualKeyboardLayout->addWidget(hashKey, 3, 2);
}

void NumberMenu::setupLettersLayout()
{
    clearKeyboardLayout();

    QString letters = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    int cols = 6;
    int row = 0, col = 0;

    for (QChar letter : letters) {
        QPushButton* key = new QPushButton(QString(letter), this);
        key->setMinimumSize(50, 50);
        connect(key, &QPushButton::clicked, this, &NumberMenu::on_virtualKeyboard_pressed);
        virtualKeyboardLayout->addWidget(key, row, col);

        col++;
        if (col >= cols) {
            col = 0;
            row++;
        }
    }
}

void NumberMenu::setupSymbolsLayout()
{
    clearKeyboardLayout();

    QStringList symbols = {"@", ".", "-", "+", "_", ":", "/", ";", "=", "?", "&", "!", "#", "*", "(", ")"};
    int cols = 5;
    int row = 0, col = 0;

    for (const QString &symbol : symbols) {
        QPushButton* key = new QPushButton(symbol, this);
        key->setMinimumSize(60, 50);
        connect(key, &QPushButton::clicked, this, &NumberMenu::on_virtualKeyboard_pressed);
        virtualKeyboardLayout->addWidget(key, row, col);

        col++;
        if (col >= cols) {
            col = 0;
            row++;
        }
    }
}

void NumberMenu::on_virtualKeyboard_pressed()
{
    emit virtualKeyboardPressed(sender());
}

void NumberMenu::on_confirmButton_clicked()
{
    emit confirmButtonClicked(numberLine->text());
}

void NumberMenu::on_layoutSwitch_clicked(int layoutId)
{
    switch(layoutId)
    {
    case NUMBERS_LAYOUT_ID:
        emit layoutSwitchToNumbersClicked();
        break;
    case LETTERS_LAYOUT_ID:
        emit layoutSwitchToLettersClicked();
        break;
    case SYMBOLS_LAYOUT_ID:
        emit layoutSwitchToSymbolsClicked();
        break;
    };
}

void NumberMenu::on_backspace_clicked()
{
    emit backspaceClicked();
}

void NumberMenu::on_clear_clicked()
{
    emit clearClicked();
}
