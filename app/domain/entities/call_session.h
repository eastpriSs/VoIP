#ifndef CALL_SESSION_H
#define CALL_SESSION_H

#include <QString>
#include <QList>
#include "sip_uri.h"

class CallSession
{
public:
    enum class Status {
        Incoming,
        Outgoing,
        Active,
        Ended
    };

    CallSession();

    void addMember(const SipUri& uri);
    void removeMember(const SipUri& uri);

    QList<SipUri> getMembers() const;

    Status getStatus() const;
    void setStatus(Status newStatus);

private:
    Status state;
    QList<SipUri> members;
};

#endif // CALL_SESSION_H
