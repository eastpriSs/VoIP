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
    stackedWidget = new QStackedWidget(this);

    statusBar = new QLabel(this);
    statusBar->setVisible(true);
    statusBar->setText("...");

    callTimer = new QTimer(this);

    setupUiPages();

    mainLayout->addWidget(stackedWidget);
    mainLayout->addWidget(statusBar);

    connect(confirmButton, &QPushButton::clicked, this, &CallMenu::on_confirmButton_clicked);
    connect(backspaceButton, &QPushButton::clicked, this, &CallMenu::on_backspace_clicked);
    connect(clearButton, &QPushButton::clicked, this, &CallMenu::on_clear_clicked);
    connect(layoutButtonGroup, &QButtonGroup::idClicked, this, &CallMenu::on_layoutSwitch_clicked);

    connect(acceptButton, &QPushButton::clicked, this, &CallMenu::callAccepted);
    connect(rejectIncomingButton, &QPushButton::clicked, this, &CallMenu::callRejected);
    connect(hangUpButton, &QPushButton::clicked, this, &CallMenu::callHangUp);
    connect(muteButton, &QPushButton::clicked, this, &CallMenu::on_muteButton_clicked);
    connect(holdButton, &QPushButton::clicked, this, &CallMenu::on_holdButton_clicked);

    connect(callTimer, &QTimer::timeout, this, &CallMenu::updateCallTimer);

    setupNumbersLayout();
}

void CallMenu::setupUiPages()
{
    // ==========================================
    // 1. Основная страница
    // ==========================================
    dialerPage = new QWidget(this);
    QVBoxLayout *dialerLayout = new QVBoxLayout(dialerPage);

    virtualKeyboardLayout = new QGridLayout();
    layoutSwitchLayout = new QHBoxLayout();

    numberLine = new QLineEdit(dialerPage);
    numberLine->setMinimumHeight(40);

    confirmButton = new QPushButton("Вызов", dialerPage);
    confirmButton->setMinimumHeight(50);

    QHBoxLayout *controlLayout = new QHBoxLayout();
    backspaceButton = new QPushButton("⌫", dialerPage);
    clearButton = new QPushButton("Очистить", dialerPage);
    controlLayout->addWidget(backspaceButton);
    controlLayout->addWidget(clearButton);

    layoutButtonGroup = new QButtonGroup(dialerPage);
    switchNumbersButton = new QPushButton("123", dialerPage);
    switchLettersButton = new QPushButton("ABC", dialerPage);
    switchSymbolsButton = new QPushButton("#+@", dialerPage);

    layoutButtonGroup->addButton(switchNumbersButton, NUMBERS_LAYOUT_ID);
    layoutButtonGroup->addButton(switchLettersButton, LETTERS_LAYOUT_ID);
    layoutButtonGroup->addButton(switchSymbolsButton, SYMBOLS_LAYOUT_ID);

    layoutSwitchLayout->addWidget(switchNumbersButton);
    layoutSwitchLayout->addWidget(switchLettersButton);
    layoutSwitchLayout->addWidget(switchSymbolsButton);

    dialerLayout->addWidget(numberLine);
    dialerLayout->addLayout(controlLayout);
    dialerLayout->addLayout(layoutSwitchLayout);
    dialerLayout->addLayout(virtualKeyboardLayout);
    dialerLayout->addWidget(confirmButton);

    // ==========================================
    // 2. СТРАНИЦА ВХОДЯЩЕГО ВЫЗОВА
    // ==========================================
    incomingCallPage = new QWidget(this);
    QVBoxLayout *incomingLayout = new QVBoxLayout(incomingCallPage);

    callerLabel = new QLabel("Входящий вызов...", incomingCallPage);
    callerLabel->setAlignment(Qt::AlignCenter);
    QFont callerFont = callerLabel->font();
    callerFont.setPointSize(14);
    callerFont.setBold(true);
    callerLabel->setFont(callerFont);

    acceptButton = new QPushButton("Принять", incomingCallPage);
    acceptButton->setMinimumHeight(50);
    acceptButton->setStyleSheet("background-color: #4CAF50; color: white; font-weight: bold;");

    rejectIncomingButton = new QPushButton("Отклонить", incomingCallPage);
    rejectIncomingButton->setMinimumHeight(50);
    rejectIncomingButton->setStyleSheet("background-color: #f44336; color: white; font-weight: bold;");

    incomingLayout->addStretch();
    incomingLayout->addWidget(callerLabel);
    incomingLayout->addStretch();
    incomingLayout->addWidget(acceptButton);
    incomingLayout->addWidget(rejectIncomingButton);

    // ==========================================
    // 3. СТРАНИЦА АКТИВНОГО РАЗГОВОРА
    // ==========================================
    activeCallPage = new QWidget(this);
    QVBoxLayout *activeLayout = new QVBoxLayout(activeCallPage);

    // Стильное оформление статуса в виде бейджа со скругленными углами
    activeCallStatusLabel = new QLabel("Разговор активен", activeCallPage);
    activeCallStatusLabel->setAlignment(Qt::AlignCenter);
    activeCallStatusLabel->setMinimumHeight(30);
    activeCallStatusLabel->setStyleSheet(
        "background-color: #2E7D32; color: white; "
        "border-radius: 12px; font-weight: bold; font-size: 13px; "
        "padding: 4px 14px;"
        );

    timerLabel = new QLabel("00:00", activeCallPage);
    timerLabel->setAlignment(Qt::AlignCenter);
    QFont timerFont = timerLabel->font();
    timerFont.setPointSize(24);
    timerFont.setBold(true);
    timerLabel->setFont(timerFont);

    QHBoxLayout *callActionsLayout = new QHBoxLayout();

    muteButton = new QPushButton("Без звука", activeCallPage);
    muteButton->setMinimumHeight(45);
    muteButton->setCheckable(true);
    muteButton->setStyleSheet(
        "QPushButton { background-color: #f5f5f5; border: 1px solid #dcdcdc; border-radius: 6px; font-weight: bold; color: #333; }"
        "QPushButton:checked { background-color: #e0e0e0; border-color: #b0b0b0; color: #d32f2f; }"
        );

    holdButton = new QPushButton("Удержание", activeCallPage);
    holdButton->setMinimumHeight(45);
    holdButton->setCheckable(true);
    holdButton->setStyleSheet(
        "QPushButton { background-color: #f5f5f5; border: 1px solid #dcdcdc; border-radius: 6px; font-weight: bold; color: #333; }"
        "QPushButton:checked { background-color: #e0e0e0; border-color: #b0b0b0; color: #ef6c00; }"
        );

    callActionsLayout->addWidget(muteButton);
    callActionsLayout->addWidget(holdButton);

    hangUpButton = new QPushButton("Завершить вызов", activeCallPage);
    hangUpButton->setMinimumHeight(50);
    hangUpButton->setStyleSheet("background-color: #f44336; color: white; font-weight: bold; border-radius: 6px;");

    activeLayout->addStretch();
    activeLayout->addWidget(activeCallStatusLabel, 0, Qt::AlignCenter); // Выравниваем бейдж по центру
    activeLayout->addSpacing(10);
    activeLayout->addWidget(timerLabel);
    activeLayout->addStretch();
    activeLayout->addLayout(callActionsLayout);
    activeLayout->addWidget(hangUpButton);

    stackedWidget->addWidget(dialerPage);
    stackedWidget->addWidget(incomingCallPage);
    stackedWidget->addWidget(activeCallPage);

    stackedWidget->setCurrentIndex(DIALER_PAGE);
}

void CallMenu::setTextNumber(const QString &number) { numberLine->setText(number); }
void CallMenu::clearTextNumber() { numberLine->clear(); }

void CallMenu::changeLayout(int layoutId) {
    if (layoutId == NUMBERS_LAYOUT_ID) setupNumbersLayout();
    else if (layoutId == LETTERS_LAYOUT_ID) setupLettersLayout();
    else if (layoutId == SYMBOLS_LAYOUT_ID) setupSymbolsLayout();
}

void CallMenu::showWarning(const QString &title, const QString &message) { QMessageBox::warning(this, title, message); }
void CallMenu::showError(const QString &title, const QString &message) { QMessageBox::critical(this, title, message); }
void CallMenu::setStatusBarText(const QString &text) { statusBar->setText(text); }

void CallMenu::showIncomingCallMenu(const QString &text)
{
    callerLabel->setText(QString("Входящий вызов:\n\n%1").arg(text));
    stackedWidget->setCurrentIndex(INCOMING_CALL_PAGE);
    setStatusBarText("Ожидание ответа...");
    this->show();
}

void CallMenu::onRequestCallingMenu()
{
    setStatusBarText("Соединение установлено.");
    stackedWidget->setCurrentIndex(ACTIVE_CALL_PAGE);

    callDurationSeconds = 0;
    timerLabel->setText("00:00");
    callTimer->start(1000);

    // Сброс кнопки Mute
    isMuted = false;
    muteButton->setChecked(false);
    muteButton->setText("Без звука");

    // Сброс кнопки Hold и возвращение дефолтного зеленого стиля статуса
    isHeld = false;
    holdButton->setChecked(false);
    holdButton->setText("Удержание");
    activeCallStatusLabel->setText("Разговор активен");
    activeCallStatusLabel->setStyleSheet(
        "background-color: #2E7D32; color: white; "
        "border-radius: 12px; font-weight: bold; font-size: 13px; "
        "padding: 4px 14px;"
        );
}

void CallMenu::onRequestRejectMenu()
{
    setStatusBarText("Вызов завершен.");
    callTimer->stop();
    stackedWidget->setCurrentIndex(DIALER_PAGE);
}

void CallMenu::updateCallTimer() {
    callDurationSeconds++;
    int minutes = callDurationSeconds / 60;
    int seconds = callDurationSeconds % 60;
    timerLabel->setText(QString("%1:%2")
                            .arg(minutes, 2, 10, QChar('0'))
                            .arg(seconds, 2, 10, QChar('0')));
}

void CallMenu::on_muteButton_clicked() {
    isMuted = muteButton->isChecked();
    if (isMuted) {
        muteButton->setText("Включить микрофон");
        setStatusBarText("Звук микрофона отключен");
    } else {
        muteButton->setText("Без звука");
        setStatusBarText("Микрофон включен");
    }
    emit muteToggled(isMuted);
}

void CallMenu::on_holdButton_clicked() {
    isHeld = holdButton->isChecked();
    if (isHeld) {
        holdButton->setText("Возобновить");
        activeCallStatusLabel->setText("На удержании");

        activeCallStatusLabel->setStyleSheet(
            "background-color: #EF6C00; color: white; "
            "border-radius: 12px; font-weight: bold; font-size: 13px; "
            "padding: 4px 14px;"
            );
        setStatusBarText("Звонок поставлен на удержание");

    } else {
        holdButton->setText("Удержание");
        activeCallStatusLabel->setText("Разговор активен");
        activeCallStatusLabel->setStyleSheet(
            "background-color: #2E7D32; color: white; "
            "border-radius: 12px; font-weight: bold; font-size: 13px; "
            "padding: 4px 14px;"
            );
        setStatusBarText("Разговор возобновлен");
    }
    emit holdToggled(isHeld);
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

    zeroKey->setMinimumSize(80, 60); starKey->setMinimumSize(80, 60); hashKey->setMinimumSize(80, 60);

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
    int cols = 6, row = 0, col = 0;
    for (QChar letter : letters) {
        QPushButton* key = new QPushButton(QString(letter), this);
        key->setMinimumSize(50, 50);
        connect(key, &QPushButton::clicked, this, &CallMenu::on_virtualKeyboard_pressed);
        virtualKeyboardLayout->addWidget(key, row, col);
        if (++col >= cols) { col = 0; row++; }
    }
}

void CallMenu::setupSymbolsLayout() {
    clearKeyboardLayout();
    QStringList symbols = {"@", ".", "-", "+", "_", ":", "/", ";", "=", "?", "&", "!", "#", "*", "(", ")"};
    int cols = 5, row = 0, col = 0;
    for (const QString &symbol : symbols) {
        QPushButton* key = new QPushButton(symbol, this);
        key->setMinimumSize(60, 50);
        connect(key, &QPushButton::clicked, this, &CallMenu::on_virtualKeyboard_pressed);
        virtualKeyboardLayout->addWidget(key, row, col);
        if (++col >= cols) { col = 0; row++; }
    }
}

void CallMenu::on_virtualKeyboard_pressed() {
    if (QPushButton* btn = qobject_cast<QPushButton*>(sender())) emit keyPressed(btn->text());
}
void CallMenu::on_confirmButton_clicked() { emit confirmPressed(numberLine->text()); }
void CallMenu::on_layoutSwitch_clicked(int layoutId) { emit layoutSwitchRequested(layoutId); }
void CallMenu::on_backspace_clicked() { emit backspacePressed(); }
void CallMenu::on_clear_clicked() { emit clearPressed(); }
