#include "sip_uri.h"
#include "regex_patterns.h"
#include <stdexcept>

SipUri::SipUri(const QString& uri) : uri(uri) {
    validate();
}

SipUri::SipUri(const QString& contact, const QString& serverDomain) {
    if (RegexPatterns::sipUri.match(contact).hasMatch()) {
        uri = contact;
    }
    else {
        uri = QString("sip:%1@%2").arg(contact, serverDomain);

        if (!RegexPatterns::sipUri.match(uri).hasMatch()) {
            throw std::invalid_argument("Некорректный формат SIP URI");
        }
    }
}

QString SipUri::toString() const {
    return uri;
}

bool SipUri::operator==(const SipUri& other) const {
    return uri == other.uri;
}

void SipUri::validate() const {
    if (!RegexPatterns::sipUri.match(uri).hasMatch()) {
        throw std::invalid_argument("Некорректный формат SIP URI");
    }
}
