#ifndef VALIDATION_H
#define VALIDATION_H

#include <QString>

namespace Validation {

class IValidation {
public:
    virtual ~IValidation() = default;
    virtual bool validate(const QString&, const QString&, QString&) = 0;
};

}
#endif // VALIDATION_H
