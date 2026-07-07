#include <iostream>

class CallSession
{
    enum status
    {
      incoming,
      outgoing,
      ended,
      active
    } state;
    size_t ID;
    
};
