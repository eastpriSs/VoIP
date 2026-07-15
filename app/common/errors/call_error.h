#ifndef CALL_ERROR_H
#define CALL_ERROR_H

#include <QString>
#include <QMetaType>

/*

PJ_SUCCESS (0) - успешное выполнение
PJ_EINVAL - неверный параметр
PJ_ENOMEM - недостаточно памяти
PJ_ETIMEDOUT - таймаут операции
PJ_EBUSY - объект занят
PJ_ENOTFOUND - не найдено
PJ_EUNKNOWN - неизвестная ошибка

*/

enum class CallErrorType {
    Success,
    InvalidParam,
    MemoryError,
    TimeOut,
    Busy,
    NotFound,
    Unknown
};

struct CallError {
    CallErrorType type;
    QString message;
};

Q_DECLARE_METATYPE(CallError)

#endif // CALL_ERROR_H
