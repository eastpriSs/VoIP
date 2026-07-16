#include "setting_saver.h"
#include <QSettings>

namespace {

const QString project = "VoIP";
const QString company = "IntegraSources";
const QString headerPBXGroup = "PBXCred";
const QString clientIdField  = "clientId";
const QString clientSecretField  = "clientSecret";
const QString serverField = "httpServer";

}


SettingSaver::SettingSaver(QObject *parent)
    : QObject{parent}
{}

void SettingSaver::savePBXCred(const QString &clientId, const QString &clientSecret, const QString &httpServer)
{
    QSettings settings(company, project);

    settings.beginGroup(headerPBXGroup);
    settings.setValue(clientIdField, clientId);
    settings.setValue(clientSecretField, clientSecret);
    settings.setValue(serverField, httpServer);
    settings.endGroup();
}

void SettingSaver::getPBXCred(QString &clientId, QString &clientSecret, QString &httpServer)
{
    QSettings settings(company, project);

    settings.beginGroup(headerPBXGroup);
    clientId = settings.value(clientIdField, "").toString();
    clientSecret = settings.value(clientSecretField, "").toString();
    httpServer = settings.value(serverField, "").toString();
    settings.endGroup();
}
