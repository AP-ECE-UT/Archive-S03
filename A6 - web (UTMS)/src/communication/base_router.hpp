#ifndef BASE_ROUTER_HPP_INCLUDE
#define BASE_ROUTER_HPP_INCLUDE

#include "request.hpp"

class BaseRouter {
public:
    virtual void executeRequest(Request req) = 0;
};

#endif // BASE_ROUTER_HPP_INCLUDE
