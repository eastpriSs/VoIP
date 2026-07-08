#ifndef CALL_MENU_H
#define CALL_MENU_H

#include <QDialog>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QButtonGroup>

class CallMenu : public QDialog
{
    Q_OBJECT
public:
    explicit CallMenu(QWidget *parent = nullptr);

    // Слоты для получения команд от Model (через Presenter)
    void setTextNumber(const QString& number);
    void clearTextNumber();

public slots:
    void changeLayout(int layoutId);
    void showWarning(const QString& title, const QString& message);

signals:
    // Сигналы о намерениях пользователя (отправляются в Model)
    void keyPressed(const QString& text);
    void backspacePressed();
    void clearPressed();
    void layoutSwitchRequested(int layoutId);
    void confirmPressed(const QString& number);

private slots:
    void on_virtualKeyboard_pressed();
    void on_confirmButton_clicked();
    void on_layoutSwitch_clicked(int layoutId);
    void on_backspace_clicked();
    void on_clear_clicked();

private:
    void clearKeyboardLayout();
    void setupNumbersLayout();
    void setupLettersLayout();
    void setupSymbolsLayout();

    QVBoxLayout *mainLayout;
    QGridLayout *virtualKeyboardLayout;
    QHBoxLayout *layoutSwitchLayout;
    QLineEdit *numberLine;
    QPushButton *confirmButton;
    QPushButton *backspaceButton;
    QPushButton *clearButton;
    QPushButton *switchNumbersButton;
    QPushButton *switchLettersButton;
    QPushButton *switchSymbolsButton;
    QButtonGroup *layoutButtonGroup;

    static constexpr int LETTERS_LAYOUT_ID = 1;
    static constexpr int NUMBERS_LAYOUT_ID = 2;
    static constexpr int SYMBOLS_LAYOUT_ID = 3;
};

#endif // CALL_MENU_H
