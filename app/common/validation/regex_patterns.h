#ifndef REGEX_PATTERNS_H
#define REGEX_PATTERNS_H

#include <QRegularExpression>

namespace RegexPatterns {

inline const QRegularExpression internalNumber("^[A-Za-z0-9_]+$");
inline const QRegularExpression virtualNumber("^\\+?[1-9]\\d{9,14}$");
inline const QRegularExpression username("^[a-zA-Z0-9_\\.\\*\\-@]{3,64}$");
inline const QRegularExpression sipUri("^[a-zA-Z0-9_\\-\\.\\+]+@[a-zA-Z0-9\\-]+(\\.[a-zA-Z0-9\\-]+)+(\\:[0-9]{1,5})?(;\\S+)?$");

}

#endif // REGEX_PATTERNS_H
