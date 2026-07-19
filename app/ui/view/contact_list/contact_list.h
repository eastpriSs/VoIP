#ifndef CONTACT_LIST_H
#define CONTACT_LIST_H

#include <QListWidget>
#include <QDialog>
#include <QLabel>
#include <memory>
#include "setting_menu.h"

class ContactList : public QListWidget
{
    Q_OBJECT
public:
    explicit ContactList(QWidget *parent = nullptr);

    void addContact(const QString &name);
    void removeSelectedContact();
    void setContacts(const QStringList &contacts);
    void clearList();
    void updateList();

    // Метод для передачи SettingMenu
    void setSettingMenu(std::shared_ptr<SettingMenu> menu);

signals:
    void itemClicked(QListWidgetItem *item);
    void contactChoose(const QString& contact);
    void updateListRequested();
    void authConfigEntered(const QString &clientId, const QString &clientSecret, const QString &server);
    void callMenuShowRequested(const QString &contact);

public slots:
    void uploadList(const QStringList& contacts);
    void showError(const QString &message);
    void showContacts(QStringList contacts);
    void setStatusBarText(const QString &text);
    void callMenu(const QString &contact);
    void authMenuRequested();
    void onHideStatus();

private slots:
    void onContactClicked(QListWidgetItem* contact);
    void onSettingsSubmitted(const QString &clientId, const QString &clientSecret, const QString &httpServer);

private:
    QDialog *statusDialog = nullptr;
    QLabel *statusLabel = nullptr;

    std::shared_ptr<SettingMenu> settingMenu;

    static constexpr int WEIGHT_STATUS_LABEL = 300;
    static constexpr int HEIGHT_STATUS_LABEL = 100;
};

#endif // CONTACT_LIST_H
