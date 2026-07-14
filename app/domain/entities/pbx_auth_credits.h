#ifndef PBX_AUTH_CREDITS_H
#define PBX_AUTH_CREDITS_H

#include <QString>

class PBXAuthCredits {
public:
    PBXAuthCredits(const QString &clientId, const QString &clientSecret, const QString &server);

    QString clientId() const;
    QString clientSecret() const;
    QString server() const;

private:
    QString m_clientId;
    QString m_clientSecret;
    QString m_server;
};

#endif // PBX_AUTH_CREDITS_H
