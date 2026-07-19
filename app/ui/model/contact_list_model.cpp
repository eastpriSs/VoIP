#include "contact_list_model.h"
#include "regex_patterns.h"
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
    contactController->proccessSelectedNumber(contact, serverDomain);
    emit callMenuRequested(contact);
}

void ContactListModel::onAuthConfigReceived(const QString &clientId, const QString &clientSecret, const QString &server)
{
    serverDomain = server;
    serverDomain.remove(RegexPatterns::httpsHttpsRegex);
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
