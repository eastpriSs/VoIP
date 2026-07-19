#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkRequest>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>
#include <QSslConfiguration>
#include "contact_fetcher_pbx.h"
#include "pbx_api_constants.h"

using namespace PbxApi;

ContactFetcherPBX::ContactFetcherPBX(QObject *parent)
    : QObject(parent)
{
    networkManager = new QNetworkAccessManager(this);
}

void ContactFetcherPBX::fetchToken(const QString &clientId, const QString &clientSecret,
                                   const QString &server)
{
    QUrl url(QString("%1%2").arg(server, TOKEN_ENDPOINT));
    QNetworkRequest request(url);

    // обход ssl сертификации
    QSslConfiguration sslConfig = QSslConfiguration::defaultConfiguration();
    sslConfig.setPeerVerifyMode(QSslSocket::VerifyNone);
    request.setSslConfiguration(sslConfig);

    request.setHeader(QNetworkRequest::ContentTypeHeader, CONTENT_TYPE_FORM);

    QString concatenated = QStringLiteral("%1:%2").arg(clientId, clientSecret);
    QByteArray data = concatenated.toLocal8Bit().toBase64();
    QString headerData = AUTH_BASIC_PREFIX + QString::fromLatin1(data);
    request.setRawHeader(AUTHORIZATION_HEADER.toUtf8(), headerData.toUtf8());

    QByteArray postData;
    postData.append(TOKEN_GRANT_TYPE.toUtf8());

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

    QString token = jsonObj.value(JsonKeys::ACCESS_TOKEN).toString();
    int expiresIn = jsonObj.value(JsonKeys::EXPIRES_IN).toString().toInt(&expireTimeRecieved);

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
    QUrl url(QString("%1%2").arg(server, GQL_ENDPOINT));
    QNetworkRequest request(url);

    request.setHeader(QNetworkRequest::ContentTypeHeader, CONTENT_TYPE_JSON);

    request.setRawHeader(AUTHORIZATION_HEADER.toUtf8(),
                         QStringLiteral("%1%2").arg(AUTH_BEARER_PREFIX, token).toUtf8());

    QJsonObject jsonBody;
    jsonBody[JsonKeys::QUERY] = GQL_FETCH_EXTENSIONS_QUERY;

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
    QJsonDocument jsonDoc = QJsonDocument::fromJson(responseData);
    if (jsonDoc.isNull() || !jsonDoc.isObject()) {
        qWarning() << "Неверный формат JSON-ответа с extensions";
        return;
    }

    QJsonObject jsonObj = jsonDoc.object();

    QJsonArray extensions = jsonObj[JsonKeys::DATA].toObject()
                                [JsonKeys::FETCH_ALL_EXTENSIONS].toObject()
                                [JsonKeys::EXTENSION].toArray();

    QList<QString> extensionsList;
    for (const QJsonValue &value : extensions) {
        if (value.isObject()) {
            QJsonObject currentExtension = value.toObject();
            extensionsList.append(currentExtension[JsonKeys::EXTENSION_ID].toString());
        }
    }

    qInfo() << "Успешный ответ от GraphQL:";
    qInfo().noquote() << responseData;
    emit extensionsRecieved(std::move(extensionsList));
}
