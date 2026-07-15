#include "my_call.h"
#include <QDebug>


using namespace pj;

namespace sip_private {

// ----------------------------------- MyCall

MyCall::MyCall(Account &acc, int call_id, StateCallback cb)
    : Call(acc, call_id), stateCallback(std::move(cb)), muteVoice(false) {}

void MyCall::onCallState(OnCallStateParam &prm) {
    CallInfo ci = getInfo();
    qInfo() << "call state:" << ci.stateText;
    if (stateCallback) {
        stateCallback(ci.id, ci.state, QString::fromStdString(ci.stateText));
    }
}

void MyCall::onCallMediaState(OnCallMediaStateParam &prm) {
    CallInfo ci = getInfo();
    for (unsigned i = 0; i < ci.media.size(); i++) {
        if (ci.media[i].type == PJMEDIA_TYPE_AUDIO) {
            try {
                AudioMedia aud_med = getAudioMedia(i);
                AudDevManager& mgr = Endpoint::instance().audDevManager();

                if (ci.media[i].status == PJSUA_CALL_MEDIA_ACTIVE ||
                    ci.media[i].status == PJSUA_CALL_MEDIA_REMOTE_HOLD) {

                    aud_med.startTransmit(mgr.getPlaybackDevMedia());
                    mgr.getCaptureDevMedia().startTransmit(aud_med);
                    aud_med.adjustTxLevel(muteVoice ? 0.0f : 1.0f);

                } else {
                    aud_med.stopTransmit(mgr.getPlaybackDevMedia());
                    mgr.getCaptureDevMedia().stopTransmit(aud_med);
                }
            }
            catch(const Error &e) {
            }
        }
    }
}

void MyCall::setMuteVoice(bool v) {
    muteVoice = v;
    applyMute();
}

void MyCall::applyMute() {
    try {
        CallInfo ci = getInfo();
        for (unsigned i = 0; i < ci.media.size(); i++) {
            if (ci.media[i].type == PJMEDIA_TYPE_AUDIO &&
                ci.media[i].status == PJSUA_CALL_MEDIA_ACTIVE) {

                AudioMedia aud_med = getAudioMedia(i);
                aud_med.adjustTxLevel(muteVoice ? 0.0f : 1.0f);
            }
        }
    } catch (const Error &e) {
        // todo: сделать вывод ошибки понятный для пользователя
        qInfo() << "Mute не сработал.";
    }
}

}
