#ifndef CONNECTIONSETTINGSMENU_H
#define CONNECTIONSETTINGSMENU_H

#include <QWidget>
#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>

class ConnectionSettingsMenu : public QDialog
{
    Q_OBJECT
public:
    explicit ConnectionSettingsMenu(QWidget *parent = nullptr);

signals:

private:
    QVBoxLayout* mainLayout;
    QHBoxLayout* protocolLayout;
    QHBoxLayout* usernameLayout;
};

#endif // CONNECTIONSETTINGSMENU_H
