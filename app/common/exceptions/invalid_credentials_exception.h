#ifndef INVALID_CREDENTIALS_EXCEPTION_H
#define INVALID_CREDENTIALS_EXCEPTION_H

#include <stdexcept>

class InvalidCredentialsException : public std::exception {
private:
    std::string message;
public:
    explicit InvalidCredentialsException(const std::string& msg);
    const char* what() const noexcept override;
};


#endif // INVALID_CREDENTIALS_EXCEPTION_H
