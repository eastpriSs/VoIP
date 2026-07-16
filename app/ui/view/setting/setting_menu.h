#ifndef SETTING_MENU_H
#define SETTING_MENU_H

#include <QDialog>
#include <QLineEdit>
#include <QPushButton>

class SettingMenu : public QDialog
{
    Q_OBJECT
public:
    explicit SettingMenu(QWidget *parent = nullptr);

public slots:
    void setInitialSettings(const QString &clientId, const QString &clientSecret, const QString &httpServer);

signals:
    void settingsSubmitted(const QString &clientId, const QString &clientSecret, const QString &httpServer);

private slots:
    void onSubmitClicked();

private:
    QLineEdit *clientIdEdit;
    QLineEdit *clientSecretEdit;
    QLineEdit *httpServerEdit;
    QPushButton *submitButton;
};

#endif // SETTING_MENU_H
