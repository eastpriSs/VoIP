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

    CallSession(SipUri&& dist);
    Status getStatus() const;
    SipUri getDist() const;
    void setStatus(Status newStatus);


private:
    Status state;
    SipUri dist;
};

#endif // CALL_SESSION_H
