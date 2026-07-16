#include "setting_saver.h"
#include <QSettings>

namespace {
const QString project = "VoIP";
const QString company = "IntegraSources";
const QString headerPBXGroup = "PBXCred";
const QString clientIdField  = "clientId";
const QString clientSecretField  = "clientSecret";
const QString serverField = "httpServer";
const QString recentCallsGroup = "RecentCalls";
const QString recentCallsArray = "calls";
const QString recentCallRecord = "record";
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

// --- НОВЫЕ МЕТОДЫ ---

void SettingSaver::saveRecentCalls(const QStringList& calls)
{
    QSettings settings(company, project);
    settings.beginGroup(recentCallsGroup);
    settings.beginWriteArray(recentCallsArray);
    for (int i = 0; i < calls.size(); ++i) {
        settings.setArrayIndex(i);
        settings.setValue(recentCallRecord, calls[i]);
    }
    settings.endArray();
    settings.endGroup();
}

QStringList SettingSaver::getRecentCalls()
{
    QStringList calls;
    QSettings settings(company, project);
    settings.beginGroup(recentCallsGroup);
    int size = settings.beginReadArray(recentCallsArray);
    for (int i = 0; i < size; ++i) {
        settings.setArrayIndex(i);
        calls.append(settings.value(recentCallRecord).toString());
    }
    settings.endArray();
    settings.endGroup();
    return calls;
}
