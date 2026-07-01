#ifndef DATABASEVALIDATION_H
#define DATABASEVALIDATION_H

#include "validation.h"

namespace Validation {

class DataBaseValidation : public IValidation {
public:
    explicit DataBaseValidation(std::unique_ptr<IValidation> next = nullptr);

    bool validate(const QString& username, const QString&, QString& password) override;

private:
    std::unique_ptr<IValidation> next;
};

}
#endif // DATABASEVALIDATION_H
