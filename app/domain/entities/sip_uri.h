#ifndef SIP_URI_H
#define SIP_URI_H

#include <QString>

class SipUri {
public:
    explicit SipUri(const QString& uri);
    QString toString() const;
    bool operator==(const SipUri& other) const;

private:
    QString uri;
    void validate() const;
};
#endif // SIP_URI_H
