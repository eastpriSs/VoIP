#ifndef AUTH_CREDITS_H
#define AUTH_CREDITS_H

#include <QString>

class AuthCredits {
public:
    AuthCredits(QString login, QString password, QString sipServer, int port);
    QString getLogin() const;
    QString getPassword() const;
    QString getIDUri() const;
    QString getRegistrarUri() const;
    int getPort() const;

private:
    void validate() const;
    QString login;
    QString password;
    QString sipServer;
    int port;
};
#endif // AUTH_CREDITS_H
