#include "call_session.h"

CallSession::CallSession() : state(Status::Ended) {}

void CallSession::addMember(const SipUri& uri) {
    if (!members.contains(uri)) {
        members.append(uri);
    }
}

void CallSession::removeMember(const SipUri& uri) {
    members.removeAll(uri);
}

QList<SipUri> CallSession::getMembers() const {
    return members;
}

CallSession::Status CallSession::getStatus() const {
    return state;
}

void CallSession::setStatus(CallSession::Status newStatus) {
    state = newStatus;
}
