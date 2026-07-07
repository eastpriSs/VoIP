#include <iostream>

class Contact {
private:
    std::string name;
    std::string sip_uri;
    bool isOnline;
public:
    Contact(const std::string& name, const std::string& uri); 
};
