#pragma once
#include <vector>
#include <optional>
#include "/../../entities/contact.h"

namespace voip {
namespace domain {

class IContactRepository {
public:
    virtual ~IContactRepository() = default;

    virtual bool save(const Contact& contact) = 0;
    virtual std::optional<Contact> findByName(const std::string& name) = 0;
    virtual std::vector<Contact> findAll() = 0;
    // ...
};

} // namespace domain
} // namespace voip
