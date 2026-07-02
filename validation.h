#ifndef VALIDATION_H
#define VALIDATION_H

#include <QString>
namespace Validation {

class IValidation {
public:
    virtual ~IValidation() = default;
    virtual bool validate(const QString& username, const QString& password, QString& error) = 0;
};

}
#endif // VALIDATION_H
