#ifndef SETTING_SAVER_H
#define SETTING_SAVER_H

#include <QObject>
#include <QString>

class SettingSaver : public QObject
{
    Q_OBJECT
public:
    explicit SettingSaver(QObject *parent = nullptr);

    void savePBXCred(const QString &clientId, const QString &clientSecret, const QString &httpServer);
    void getPBXCred(QString &clientId, QString &clientSecret, QString &httpServer);
};

#endif // SETTING_SAVER_H
