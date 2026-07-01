#ifndef NUMBERMENU_H
#define NUMBERMENU_H

#include <QDialog>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QButtonGroup>

class NumberMenu : public QDialog
{
    Q_OBJECT

public:
    explicit NumberMenu(QWidget *parent = nullptr);
    void insertInTextNumber(QString&& s);
    void clearTextNumber();
    void setupNumbersLayout();
    void setupLettersLayout();
    void setupSymbolsLayout();

// setters & getters
    void setTextNumber(const QString& number);
    void setTextNumber(QString&& number);
    QString getTextNumber();

signals:
    void confirmButtonClicked(const QString &number);
    void virtualKeyboardPressed(const QObject* sender);
    void backspaceClicked();
    void clearClicked();
    void layoutSwitchToLettersClicked();
    void layoutSwitchToNumbersClicked();
    void layoutSwitchToSymbolsClicked();

private slots:
    void on_virtualKeyboard_pressed();
    void on_confirmButton_clicked();
    void on_layoutSwitch_clicked(int layoutId);
    void on_backspace_clicked();
    void on_clear_clicked();

private:
    void clearKeyboardLayout();

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

// Layouts ID
    static constexpr int LETTERS_LAYOUT_ID = 1;
    static constexpr int NUMBERS_LAYOUT_ID = 2;
    static constexpr int SYMBOLS_LAYOUT_ID = 3;

};

#endif // NUMBERMENU_H
