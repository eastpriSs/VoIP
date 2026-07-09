#include "call_repository_impl.h"
#include <QDebug>

namespace {

QString extractPureSipUri(const QString& rawUri)
{
    QString trimmed = rawUri.trimmed();
    int start = trimmed.indexOf('<');
    int end = trimmed.lastIndexOf('>');

    if (start != -1 && end != -1 && end > start) {
        return trimmed.mid(start + 1, end - start - 1).trimmed();
    }
    return trimmed;
}

}

CallRepositoryImpl::CallRepositoryImpl(std::shared_ptr<sip::ModuleSIP> sipService)
    : sipService(sipService)
{
    connect(sipService.get(), &sip::ModuleSIP::incomingCallReceived, this, &CallRepositoryImpl::onIncomingCall);
}

void CallRepositoryImpl::callSipAccount(const SipUri &distUri)
{
    int code = sipService->doCall(distUri);
    if (code != sip::OK) {
        throw std::runtime_error(sipService->getTextError(code).toStdString());
    }
}

void CallRepositoryImpl::acceptSipCall()
{
    int code = sipService->doAcceptCall();
}

void CallRepositoryImpl::rejectSipCall()
{
    int code = sipService->doRejectCall();
}

void CallRepositoryImpl::onIncomingCall(QString remoteUri, int callID)
{
    emit incomingCall(SipUri(extractPureSipUri(std::move(remoteUri))), callID);
}
