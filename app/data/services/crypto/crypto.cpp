#include "crypto.h"

Crypto::Crypto(QObject *parent)
    : QObject{parent}
{}

QString Crypto::encrypt(const QString &text)
{
    QString result = text;
    for (int i = 0; i < result.length(); ++i) {
        result[i] = QChar(result[i].unicode() + SHIFT);
    }
    return result;
}

QString Crypto::decrypt(const QString &text)
{
    QString result = text;
    for (int i = 0; i < result.length(); ++i) {
        result[i] = QChar(result[i].unicode() - SHIFT);
    }
    return result;
}
