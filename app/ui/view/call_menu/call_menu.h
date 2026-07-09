#ifndef CALL_MENU_H
#define CALL_MENU_H

#include <QDialog>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QButtonGroup>
#include <QLabel>

class IncomingCallMenu;

class CallMenu : public QDialog
{
    Q_OBJECT
public:
    explicit CallMenu(QWidget *parent = nullptr);

    void setTextNumber(const QString& number);
    void clearTextNumber();

public slots:
    void changeLayout(int layoutId);
    void showWarning(const QString& title, const QString& message);
    void showError(const QString& title, const QString& message);
    void setStatusBarText(const QString& text);
    void showIncomingCallMenu(const QString& text);
    void onRequestCallingMenu();
    void onRequestRejectMenu();

signals:
    void keyPressed(const QString& text);
    void backspacePressed();
    void clearPressed();
    void layoutSwitchRequested(int layoutId);
    void confirmPressed(const QString& number);
    void callAccepted();
    void callRejected();

private slots:
    void on_virtualKeyboard_pressed();
    void on_confirmButton_clicked();
    void on_layoutSwitch_clicked(int layoutId);
    void on_backspace_clicked();
    void on_clear_clicked();
    void onAcceptCall();
    void onRejectCall();

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
    QLabel  *statusBar;
    IncomingCallMenu *incomingMenu;

    static constexpr int LETTERS_LAYOUT_ID = 1;
    static constexpr int NUMBERS_LAYOUT_ID = 2;
    static constexpr int SYMBOLS_LAYOUT_ID = 3;
};

class IncomingCallMenu : public QDialog
{
    Q_OBJECT
public:
    explicit IncomingCallMenu(QWidget *parent = nullptr);
    void setCallerInfo(const QString& info);

public slots:
    void onRequestCallingGui();
    void onRequestRejectedGui();

signals:
    void acceptCall();
    void rejectCall();

private:
    QLineEdit *callerLine;
    QPushButton *acceptButton;
    QPushButton *rejectButton;
};

#endif // CALL_MENU_H
