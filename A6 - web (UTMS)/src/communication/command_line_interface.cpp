#include "command_line_interface.hpp"

#include <iostream>
#include <string>

#include "../exceptions/exceptions.hpp"
#include "base_responder.hpp"
#include "base_router.hpp"
#include "request.hpp"

CommandLineInterface::CommandLineInterface(BaseRouter* router,
                                           BaseResponder* responder) {
    router_ = router;
    responder_ = responder;
}

void CommandLineInterface::start() {
    std::string command;
    while (std::getline(std::cin, command)) {
        if (command == "")
            continue;

        execute(command);
    }
}

void CommandLineInterface::execute(std::string command) {
    try {
        Request req(command);
        router_->executeRequest(req);
    }
    catch (BadRequestException) {
        responder_->badRequest();
    }
    catch (NotFoundException) {
        responder_->notFound();
    }
    catch (PermissionDeniedException) {
        responder_->permissionDenied();
    }
    catch (EmptyException) {
        responder_->empty();
    }
    catch (...) {
        // TODO
    }
}
