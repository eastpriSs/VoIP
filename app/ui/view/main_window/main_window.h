#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "auth_menu.h"
#include "contact_list.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(AuthMenu* authMenu, QWidget *parent = nullptr);
    ~MainWindow();

signals:
    void authActionTriggered();

public slots:
    void on_authAction_triggered();

private slots:
    void on_contactsButton_clicked();

private:
    AuthMenu* authMenu;
    ContactList* contactList;
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
