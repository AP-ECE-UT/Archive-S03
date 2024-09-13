#ifndef COMMAND_LINE_INTERFACE_HPP_INCLUDE
#define COMMAND_LINE_INTERFACE_HPP_INCLUDE

#include <string>

#include "base_responder.hpp"
#include "base_router.hpp"

class CommandLineInterface {
public:
    CommandLineInterface(BaseRouter* router, BaseResponder* responder);
    void start();

private:
    void execute(std::string command);

    BaseRouter* router_;
    BaseResponder* responder_;
};

#endif // COMMAND_LINE_INTERFACE_HPP_INCLUDE
