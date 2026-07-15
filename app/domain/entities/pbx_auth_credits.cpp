#include "pbx_auth_credits.h"
#include <QRegularExpression>
#include <stdexcept>

PBXAuthCredits::PBXAuthCredits(const QString &clientId, const QString &clientSecret, const QString &server) {

    QRegularExpression clientIdRegex("^[a-zA-Z0-9_-]{3,150}$");
    if (!clientIdRegex.match(clientId).hasMatch()) {
        throw std::invalid_argument("Некорректный Client ID. Допускаются только латинские буквы, цифры, дефисы и подчеркивания (от 3 до 150 символов).");
    }

    if (clientSecret.trimmed().isEmpty() || clientSecret.length() < 8) {
        throw std::invalid_argument("Некорректный Client Secret. Он должен содержать не менее 8 символов.");
    }

    QRegularExpression serverRegex(R"(^http:\/\/[a-zA-Z0-9.-]+(?::[0-9]+)?(\/.*)?$)");
    if (!serverRegex.match(server).hasMatch()) {
        throw std::invalid_argument("Некорректный адрес сервера. URL должен начинаться с https:// и иметь валидный домен/IP.");
    }

    m_clientId = clientId;
    m_clientSecret = clientSecret;
    m_server = server;
}

QString PBXAuthCredits::clientId() const {
    return m_clientId;
}

QString PBXAuthCredits::clientSecret() const {
    return m_clientSecret;
}

QString PBXAuthCredits::server() const {
    return m_server;
}
