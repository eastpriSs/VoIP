#ifndef SIP_URI_H
#define SIP_URI_H

#include <QString>

class SipUri {
public:
    explicit SipUri(const QString& uri);
    SipUri(const QString& contact, const QString& serverDomain);

    QString toString() const;
    bool operator==(const SipUri& other) const;

private:
    void validate() const;
    QString uri;
};

#endif // SIP_URI_H
