#include "invalid_credentials_exception.h"

InvalidCredentialsException::InvalidCredentialsException(const std::string& msg) : message(msg) {}

const char* InvalidCredentialsException::what() const noexcept {
    return message.c_str();
}
