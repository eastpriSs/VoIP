#ifndef CALL_MENU_H
#define CALL_MENU_H

#include <QDialog>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QButtonGroup>
#include <QLabel>
#include <QStackedWidget>
#include <QTimer>


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
    void callHangUp();
    void muteToggled(bool isMuted);

private slots:
    void on_virtualKeyboard_pressed();
    void on_confirmButton_clicked();
    void on_layoutSwitch_clicked(int layoutId);
    void on_backspace_clicked();
    void on_clear_clicked();
    void on_muteButton_clicked();
    void updateCallTimer();

private:
    void clearKeyboardLayout();
    void setupNumbersLayout();
    void setupLettersLayout();
    void setupSymbolsLayout();
    void setupUiPages();

    enum PageIndex {
        DIALER_PAGE = 0,
        INCOMING_CALL_PAGE = 1,
        ACTIVE_CALL_PAGE = 2
    };

    QVBoxLayout *mainLayout;
    QStackedWidget *stackedWidget;

    QWidget *dialerPage;
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

    QWidget *incomingCallPage;
    QLabel *callerLabel;
    QPushButton *acceptButton;
    QPushButton *rejectIncomingButton;

    QWidget *activeCallPage;
    QLabel *activeCallStatusLabel;
    QLabel *timerLabel;
    QPushButton *muteButton;
    QPushButton *hangUpButton;

    QLabel  *statusBar;
    QTimer  *callTimer;
    int     callDurationSeconds = 0;
    bool    isMuted = false;

    static constexpr int LETTERS_LAYOUT_ID = 1;
    static constexpr int NUMBERS_LAYOUT_ID = 2;
    static constexpr int SYMBOLS_LAYOUT_ID = 3;
};

#endif // CALL_MENU_H
