#include "contact_list_model.h"
#include <QDebug>

#include "contact_list_model.h"
#include <QDebug>

ContactListModel::ContactListModel(std::shared_ptr<ContactListController> c, QObject *parent)
    : QObject{parent}, contactController(c)
{
    connect(contactController.get(), &ContactListController::pbxAuthError, this, &ContactListModel::onPbxAuthError);
    connect(contactController.get(), &ContactListController::extensionsRecieved,
            this, &ContactListModel::onExtensionsRecieved);
    connect(contactController.get(), &ContactListController::requestStateChanged,
            this, &ContactListModel::onRequestStateChanged);
    connect(contactController.get(), &ContactListController::settingsRequired,
            this, &ContactListModel::showSettingsMenuRequested);
}

void ContactListModel::onUpdateListRequested()
{
    contactController->tryUpdateFromSettings();
}

void ContactListModel::onContactClicked(const QString &contact)
{

    QString number = QString("sip:%1@%2").arg(contact, serverDomain);
    contactController->proccessSelectedNumber(number);
    emit callMenuRequested(number);
}

void ContactListModel::onAuthConfigReceived(const QString &clientId, const QString &clientSecret, const QString &server)
{
    serverDomain = server;
    serverDomain.replace("http://", "");
    serverDomain.replace("https://", "");
    contactController->updateContactList(clientId, clientSecret, server);
}

void ContactListModel::onPbxAuthError(const QString &message)
{
    emit authError(message);
}

void ContactListModel::onExtensionsRecieved(QStringList contactList)
{
    emit hideStatus();
    emit showContacts(std::move(contactList));
}

void ContactListModel::onRequestStateChanged(QString state)
{
    emit setStatus(state);
}
