#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "authmenu.h"
#include "numbermenu.h"


QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

signals:
    void authActionTriggered();

public slots:
    void on_authAction_triggered();

private slots:
    void on_numberButton_clicked();

    void on_actionSettings_triggered();

private:
    AuthMenu        authMenu;
    NumberMenu      numberMenu;
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
