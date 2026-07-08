#ifndef AUTH_ERROR_H
#define AUTH_ERROR_H

#include <QString>
#include <QMetaType>

enum class AuthErrorType {
    InvalidCredentials,
    ServerUnavailable,
    Timeout,
    Unknown
};

struct AuthError {
    AuthErrorType type;
    QString message;
};

Q_DECLARE_METATYPE(AuthError)

#endif // AUTH_ERROR_H
