#include "pbx_auth_credits.h"
#include "regex_patterns.h"
#include <stdexcept>

PBXAuthCredits::PBXAuthCredits(const QString &clientId, const QString &clientSecret, const QString &server)
{
    using namespace RegexPatterns;

    if (clientId.isEmpty() && clientSecret.isEmpty() && server.isEmpty()) {
        clID = clientId;
        clSecret = clientSecret;
        srvDomain = server;
        return;
    }


    if (!clientIdRegex.match(clientId).hasMatch()) {
        throw std::invalid_argument("Некорректный Client ID. Допускаются только латинские буквы, цифры, дефисы и подчеркивания (от 3 до 150 символов).");
    }
    if (clientSecret.trimmed().isEmpty() || clientSecret.length() < 8) {
        throw std::invalid_argument("Некорректный Client Secret. Он должен содержать не менее 8 символов.");
    }
    if (!serverRegex.match(server).hasMatch()) {
        throw std::invalid_argument("Некорректный адрес сервера. URL должен начинаться с https:// и иметь валидный домен/IP.");
    }

    clID = clientId;
    clSecret = clientSecret;
    srvDomain = server;
}

QString PBXAuthCredits::clientId() const {
    return clID;
}

QString PBXAuthCredits::clientSecret() const {
    return clSecret;
}

QString PBXAuthCredits::server() const {
    return srvDomain;
}

bool PBXAuthCredits::isEmpty() const {
    return clID.isEmpty() && clSecret.isEmpty() && srvDomain.isEmpty();
}
