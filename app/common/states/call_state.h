#ifndef CALL_STATE_H
#define CALL_STATE_H

enum class CallState {
    None,
    Calling,
    Incoming,
    Early,         // Идут гудки
    Connecting,
    Active,
    Disconnected
};

#endif // CALL_STATE_H
