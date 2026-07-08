#ifndef SERVER_UNAVAILABLE_EXCEPTION_H
#define SERVER_UNAVAILABLE_EXCEPTION_H

#include <stdexcept>

class ServerUnavailableException : public std::exception {
private:
    std::string message;
public:
    explicit ServerUnavailableException(const std::string& msg);
    const char* what() const noexcept override;
};
#endif // SERVER_UNAVAILABLE_EXCEPTION_H
