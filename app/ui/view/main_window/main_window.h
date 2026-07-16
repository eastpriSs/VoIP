#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "auth_menu.h"
#include "call_menu.h"
#include "setting_menu.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(AuthMenu* authMenu, CallMenu* callMenu, SettingMenu* settMenu, QWidget *parent = nullptr);
    ~MainWindow();

    void appendRecentCall(QString record);
    void setRecentCalls(const QStringList& calls);
    QStringList getRecentCalls() const;
signals:
    void authActionTriggered();

public slots:
    void on_authAction_triggered();

private slots:
    void on_numberButton_clicked();

    void on_clientAction_triggered();

private:
    AuthMenu*      authMenu;
    CallMenu*      callMenu;
    SettingMenu*   settMenu;
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
