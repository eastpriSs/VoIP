#ifndef I_CALL_INITIATOR_H
#define I_CALL_INITIATOR_H

// внутреедоменный интерфейс скрывающий callConroller
#include <QString>

class ICallInitiator {
public:
    virtual ~ICallInitiator() = default;
    virtual void initiateCall(const QString& number, const QString& serverDomain) = 0;
    virtual void initiateCall(const QString& number) = 0;
};

#endif // I_CALL_INITIATOR_H
