#ifndef CONTACT_LIST_MODEL_H
#define CONTACT_LIST_MODEL_H

#include <QObject>
#include <memory>
#include "contact_list_controller.h"

class ContactListModel : public QObject
{
    Q_OBJECT
public:
    explicit ContactListModel(std::shared_ptr<ContactListController> contactContrl, QObject *parent = nullptr);

public slots:
    void onContactClicked(const QString& contact);
    void onAuthConfigReceived(const QString &clientId, const QString &clientSecret, const QString &server);

private slots:
    void onPbxAuthError(const QString &message);
    void onExtensionsRecieved(QStringList contactList);
    void onRequestStateChanged(QString state);

signals:
    void authError(const QString &message);
    void showContacts(QStringList contacts);
    void setStatus(const QString &message);
    void callMenuRequested(const QString &number);
    void hideStatus();

private:
    QString serverDomain;
    std::shared_ptr<ContactListController> contactController;
};

#endif // CONTACT_LIST_MODEL_H
