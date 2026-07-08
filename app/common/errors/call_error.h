#ifndef CALL_ERROR_H
#define CALL_ERROR_H

#include <QString>
#include <QMetaType>

enum class CallErrorType {

};

struct CallError {
    CallErrorType type;
    QString message;
};

Q_DECLARE_METATYPE(CallError)

#endif // CALL_ERROR_H
