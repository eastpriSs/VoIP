#include "call_session.h"

CallSession::CallSession(SipUri&& dist) : dist(dist), state(Status::Ended) {}

SipUri CallSession::getDist() const
{
    return dist;
}

CallSession::Status CallSession::getStatus() const {
    return state;
}

void CallSession::setStatus(CallSession::Status newStatus) {
    state = newStatus;
}
