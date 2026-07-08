#include "server_unavailable_exception.h"

ServerUnavailableException::ServerUnavailableException(const std::string& msg) : message(msg) {}

const char* ServerUnavailableException::what() const noexcept{
    return message.c_str();
}
