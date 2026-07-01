#ifndef NUMBERMENU_H
#define NUMBERMENU_H

#include <QWidget>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QPushButton>
#include <QDialog>

class NumberMenu : public QDialog
{
    Q_OBJECT
public:
    explicit NumberMenu(QWidget *parent = nullptr);


private slots:
    void on_confirmButton_clicked();
    void on_virtualKeyboard_pressed();

private:
    QLineEdit* numberLine;
    QPushButton* confirmButton;
    QVBoxLayout* mainLayout;
    QGridLayout* virtualKeyboardLayout;

signals:
    void confirmButtonClicked(const QString&);

};

#endif // NUMBERMENU_H
