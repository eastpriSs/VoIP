#include "numbermenu.h" 

NumberMenu::NumberMenu(QWidget *parent)
    : QDialog{parent}
{
    setWindowTitle("Набор номера");

    mainLayout = new QVBoxLayout(this);
    virtualKeyboardLayout = new QGridLayout(this);
    numberLine = new QLineEdit(this);
    confirmButton = new QPushButton(this);

    confirmButton->setText("Вызов");

    ushort number = 0;
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            QPushButton* key = new QPushButton(this);
            key->setText(QString::number(number++));
            connect(key, &QPushButton::clicked, this, &NumberMenu::on_virtualKeyboard_pressed);
            virtualKeyboardLayout->addWidget(key, i, j);
        }
    }


    mainLayout->addWidget(numberLine);
    mainLayout->addLayout(virtualKeyboardLayout);
    mainLayout->addWidget(confirmButton);

    connect(confirmButton, &QPushButton::clicked, this, &NumberMenu::on_confirmButton_clicked);
}


void NumberMenu::on_virtualKeyboard_pressed()
{
    QObject *senderObj = sender();
    if (!senderObj) return;

    QPushButton *button = qobject_cast<QPushButton*>(senderObj);

    if (button)
        numberLine->insert(button->text());
}

void NumberMenu::on_confirmButton_clicked()
{
    emit confirmButtonClicked(numberLine->text());
}
