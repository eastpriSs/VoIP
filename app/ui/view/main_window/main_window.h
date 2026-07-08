#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "auth_menu.h"
#include "call_menu.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(AuthMenu* authMenu, CallMenu* callMenu, QWidget *parent = nullptr);
    ~MainWindow();

signals:
    void authActionTriggered();

public slots:
    void on_authAction_triggered();

private slots:
    void on_numberButton_clicked();

private:
    AuthMenu*      authMenu;
    CallMenu*      callMenu;
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
