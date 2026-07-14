#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkRequest>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>
#include <QSslConfiguration>
#include "contact_fetcher_pbx.h"

ContactFetcherPBX::ContactFetcherPBX(QObject *parent)
    : QObject(parent)
{
    networkManager = new QNetworkAccessManager(this);
}

void ContactFetcherPBX::fetchToken(const QString &clientId, const QString &clientSecret,
                                   const QString &server)
{
    QUrl url(server + "/admin/api/api/token");
    QNetworkRequest request(url);

    // обход ssl сертификации
    QSslConfiguration sslConfig = QSslConfiguration::defaultConfiguration();
    sslConfig.setPeerVerifyMode(QSslSocket::VerifyNone);
    request.setSslConfiguration(sslConfig);

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    QString concatenated = clientId + ":" + clientSecret;
    QByteArray data = concatenated.toLocal8Bit().toBase64();
    QString headerData = "Basic " + data;
    request.setRawHeader("Authorization", headerData.toLocal8Bit());

    QByteArray postData;
    postData.append("grant_type=client_credentials&scope=gql:core:read");

    qInfo() << "Отправка запроса на получение токена...";

    QNetworkReply *reply = networkManager->post(request, postData);

    connect(reply, &QNetworkReply::finished, this, [this, reply]() {
        onTokenReceived(reply);
    });
}

void ContactFetcherPBX::onTokenReceived(QNetworkReply *reply)
{
    reply->deleteLater();

    if (reply->error() != QNetworkReply::NoError) {
        qWarning() << "Ошибка при получении токена:" << reply->errorString();
        return;
    }

    QByteArray responseData = reply->readAll();
    QJsonDocument jsonDoc = QJsonDocument::fromJson(responseData);

    if (jsonDoc.isNull() || !jsonDoc.isObject()) {
        qWarning() << "Неверный формат JSON-ответа";
        return;
    }

    bool expireTimeRecieved = true;
    QJsonObject jsonObj = jsonDoc.object();
    QString token = jsonObj.value("access_token").toString();
    int expiresIn = jsonObj.value("expires_in").toString().toInt(&expireTimeRecieved);

    if (token.isEmpty()) {
        qWarning() << "Токен не найден в ответе сервера. Ответ:" << responseData;
        return;
    }
    if (expireTimeRecieved) {
        qWarning() << "Время жизни не найдено. Выставлено значение по умолчанию. Ответ:" << responseData;
        expiresIn = DEFAULT_EXPIRE_TIME;
    }

    qInfo() << "Токен успешно получен!";
    emit tokenRecieved(std::move(token), expiresIn);
}

void ContactFetcherPBX::fetchExtensions(const QString& token, const QString& server)
{
    QUrl url(server + "/admin/api/api/gql");
    QNetworkRequest request(url);

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setRawHeader("Authorization", ("Bearer " + token).toUtf8());

    QJsonObject jsonBody;
    jsonBody["query"] = "query { fetchAllExtensions { status totalCount extension { extensionId } } }";

    QJsonDocument jsonDoc(jsonBody);
    QByteArray postData = jsonDoc.toJson(QJsonDocument::Compact);

    qInfo() << "Отправка GraphQL запроса...";

    QNetworkReply *reply = networkManager->post(request, postData);

    connect(reply, &QNetworkReply::finished, this, [this, reply]() {
        onExtensionsReceived(reply);
    });
}

void ContactFetcherPBX::onExtensionsReceived(QNetworkReply *reply)
{
    reply->deleteLater();

    if (reply->error() != QNetworkReply::NoError) {
        qWarning() << "Ошибка при выполнении GraphQL запроса:" << reply->errorString();
        return;
    }

    QByteArray responseData = reply->readAll();

// debug
//     QByteArray responseData(R"({"data":{"fetchAllExtensions":{"status":true,"totalCount":2,"extension":[{"extensionId":"1001"},{"extensionId":"1002"}]}}}
// )");

    QJsonDocument jsonDoc = QJsonDocument::fromJson(responseData);

    if (jsonDoc.isNull() || !jsonDoc.isObject()) {
        qWarning() << "Неверный формат JSON-ответа с extensions";
        return;
    }

    QJsonObject jsonObj = jsonDoc.object();
    QJsonArray extensions = jsonObj["data"].toObject()
                                   ["fetchAllExtensions"].toObject()
                                   ["extension"].toArray();

    QList<QString> extensionsList;
    for (const QJsonValue &value : extensions) {
        if (value.isObject()) {
            QJsonObject currentExtension = value.toObject();
            extensionsList.append(currentExtension["extensionId"].toString());
        }
    }

    qInfo() << "Успешный ответ от GraphQL:";
    qInfo().noquote() << responseData;

    emit extensionsRecieved(std::move(extensionsList));
}
