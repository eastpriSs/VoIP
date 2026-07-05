#ifndef LEXICALVALIDATION_H
#define LEXICALVALIDATION_H

#include "validation.h"
#include <memory>

namespace validation {

class LexicalValidation : public IValidation {
public:
    explicit LexicalValidation(std::unique_ptr<IValidation> next = nullptr);
    bool validate(const QString& username, const QString& password, QString& error) override;

private:
    std::unique_ptr<IValidation> next;

};

}
#endif // LEXICALVALIDATION_H
