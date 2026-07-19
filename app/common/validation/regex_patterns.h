#ifndef REGEX_PATTERNS_H
#define REGEX_PATTERNS_H

#include <QRegularExpression>

namespace RegexPatterns {

inline const QRegularExpression internalNumber("^[A-Za-z0-9_]+$");
inline const QRegularExpression virtualNumber("^\\+?[1-9]\\d{9,14}$");
inline const QRegularExpression username("^[a-zA-Z0-9_\\.\\*\\-@]{3,64}$");
inline const QRegularExpression sipUri("^(sips?):([^@]+)(?:@(.+))?$");
inline const QRegularExpression clientIdRegex("^[a-zA-Z0-9_-]{3,150}$");
inline const QRegularExpression serverRegex(
    R"(^https?://(?:[a-zA-Z0-9.\-]+|\[[a-fA-F0-9:]+\])(?::(?:[1-9][0-9]{0,3}|[1-5][0-9]{4}|6[0-4][0-9]{3}|65[0-4][0-9]{2}|655[0-2][0-9]|6553[0-5]))?(/.*)?$)"
    );
inline const QRegularExpression httpsHttpsRegex(R"(^https?://)");
}

#endif // REGEX_PATTERNS_H
