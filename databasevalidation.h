#ifndef DATABASEVALIDATION_H
#define DATABASEVALIDATION_H

#include "validation.h"
#include <memory>
#include <QHash>

namespace Validation {

class DataBaseValidation : public IValidation {
public:
    explicit DataBaseValidation(std::unique_ptr<IValidation> next = nullptr);

    bool validate(const QString&, const QString&, QString&) override;

private:
    std::unique_ptr<IValidation> next;
};

}
#endif // DATABASEVALIDATION_H
