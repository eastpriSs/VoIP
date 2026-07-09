#ifndef CALL_REPOSITORY_IMPL_H
#define CALL_REPOSITORY_IMPL_H

#include "call_repository.h"
#include "module_sip.h"
#include "sip_uri.h"

class CallRepositoryImpl : public ICallRepository {
    Q_OBJECT
public:
    CallRepositoryImpl(std::shared_ptr<sip::ModuleSIP> sipService);
    void callSipAccount(const SipUri& distUri) override;
    void acceptSipCall() override;
    void rejectSipCall() override;

private slots:
    void onIncomingCall(QString remoteUri, int callID);
    void onCallStateChanged(int callId, int pjsip_state, const QString& stateText);

private:
    std::shared_ptr<sip::ModuleSIP> sipService;
};
#endif // CALL_REPOSITORY_IMPL_H
