#ifndef CRYPTO_H
#define CRYPTO_H

#include <QObject>
#include <QString>

class Crypto : public QObject
{
    Q_OBJECT
public:
    explicit Crypto(QObject *parent = nullptr);

    QString encrypt(const QString &text);
    QString decrypt(const QString &text);

private:
    const int SHIFT = 3;
};

#endif // CRYPTO_H
