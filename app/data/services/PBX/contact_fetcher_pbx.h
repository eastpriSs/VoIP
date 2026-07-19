#ifndef CONTACT_FETCHER_PBX_H
#define CONTACT_FETCHER_PBX_H

#include <QObject>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>

class ContactFetcherPBX : public QObject
{
    Q_OBJECT

    static constexpr int DEFAULT_EXPIRE_TIME = 3600;

public:
    ContactFetcherPBX(QObject *parent = nullptr);
    void fetchToken(const QString &clientId, const QString &clientSecret, const QString &server);
    void fetchExtensions(const QString& token, const QString& server);

signals:
    void tokenRecieved(QString tokenHash, int expireTime);
    void extensionsRecieved(QList<QString> extensions);
private slots:
    void onTokenReceived(QNetworkReply *reply);
    void onExtensionsReceived(QNetworkReply *reply);

private:
    QNetworkAccessManager *networkManager;

};

#endif // CONTACT_FETCHER_PBX_H
