#include "sip_uri.h"
#include "regex_patterns.h"
#include <stdexcept>

SipUri::SipUri(const QString& uri) : uri(uri) {
    validate();
}

QString SipUri::toString() const {
    return uri;
}


bool SipUri::operator==(const SipUri& other) const {
    return uri == other.uri;
}

void SipUri::validate() const
{
    if (!RegexPatterns::sipUri.match(uri).hasMatch()) {
        throw std::invalid_argument("Некорректный формат SIP URI");
    }
}

