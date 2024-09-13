#ifndef UTGRAM_ROUTER_HPP_INCLUDE
#define UTGRAM_ROUTER_HPP_INCLUDE

#include <unordered_map>

#include "base_router.hpp"
#include "request.hpp"
#include "utgram_base_responder.hpp"

typedef void (UtgramBaseResponder::*ResponderFunction)(Arguments);

class UtgramRouter : public BaseRouter {
public:
    UtgramRouter(UtgramBaseResponder* responder);
    void executeRequest(Request req);

private:
    void executePostRequest(Request req);
    void executePutRequest(Request req);
    void executeGetRequest(Request req);
    void executeDeleteRequest(Request req);

    UtgramBaseResponder* responder_;
};

#endif // UTGRAM_ROUTER_HPP_INCLUDE
