#include "setting_saver.h"
#include <QSettings>

SettingSaver::SettingSaver(QObject *parent)
    : QObject{parent}
{}

void SettingSaver::savePBXCred(const QString &clientId, const QString &clientSecret, const QString &httpServer)
{
    QSettings settings("IntegraSources", "VoIP");

    settings.beginGroup("PBXCred");
    settings.setValue("clientId", clientId);
    settings.setValue("clientSecret", clientSecret);
    settings.setValue("httpServer", httpServer);
    settings.endGroup();
}

void SettingSaver::getPBXCred(QString &clientId, QString &clientSecret, QString &httpServer)
{
    QSettings settings("IntegraSources", "VoIP");

    settings.beginGroup("PBXCred");
    clientId = settings.value("clientId", "").toString();
    clientSecret = settings.value("clientSecret", "").toString();
    httpServer = settings.value("httpServer", "").toString();
    settings.endGroup();
}
