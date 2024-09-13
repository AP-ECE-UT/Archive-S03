#include "utgram_router.hpp"

#include <iostream>
#include <string>

#include "../exceptions/exceptions.hpp"
#include "communication_consts.hpp"
#include "request.hpp"
#include "utgram_base_responder.hpp"

using namespace communication_consts;

UtgramRouter::UtgramRouter(UtgramBaseResponder* responder) {
    responder_ = responder;
}

void UtgramRouter::executeRequest(Request req) {
    switch (req.getActionType()) {
    case Request::ActionType::POST:
        executePostRequest(req);
        break;
    case Request::ActionType::PUT:
        executePutRequest(req);
        break;
    case Request::ActionType::GET:
        executeGetRequest(req);
        break;
    case Request::ActionType::DELETE:
        executeDeleteRequest(req);
        break;
    default:
        throw BadRequestException(err_messages::NO_MATCHING_ACTION_TYPE);
    }
}

void UtgramRouter::executePostRequest(Request req) {
    std::string command = req.getCommand();
    Arguments args = req.getArgs();
    if (command == commands::LOGIN) {
        responder_->login(args);
    }
    else if (command == commands::LOGOUT) {
        responder_->logout();
    }
    else if (command == commands::POST) {
        responder_->addPost(args);
    }
    else if (command == commands::CONNECT) {
        responder_->connect(args);
    }
    else if (command == commands::PRESENTATION) {
        responder_->addPresentation(args);
    }
    else if (command == commands::TA_FORM) {
        responder_->sendTAForm(args);
    }
    else if (command == commands::SET_PROFILE) {
        responder_->setProfile(args);
    }
    else if (command == commands::SEND_TA_REQUEST) {
        responder_->sendTARequest(args);
    }
    else if (command == commands::COURSE_POST) {
        responder_->addCoursePost(args);
    }
    else if (command == commands::CLOSE_TA_FORM) {
        responder_->closeTAForm(args);
    }
    else {
        throw NotFoundException(err_messages::NO_MATCHING_COMMAND);
    }
}

void UtgramRouter::executePutRequest(Request req) {
    std::string command = req.getCommand();
    Arguments args = req.getArgs();
    if (command == commands::MY_COURSES) {
        responder_->addToMyCourses(args);
    }
    else {
        throw NotFoundException(err_messages::NO_MATCHING_COMMAND);
    }
}

void UtgramRouter::executeGetRequest(Request req) {
    std::string command = req.getCommand();
    Arguments args = req.getArgs();
    if (command == commands::COURSES) {
        responder_->getCourses(args);
    }
    else if (command == commands::PERSONAL_PAGE) {
        responder_->getPersonalPage(args);
    }
    else if (command == commands::POST) {
        responder_->getPost(args);
    }
    else if (command == commands::NOTIFICATION) {
        responder_->getNotification();
    }
    else if (command == commands::MY_COURSES) {
        responder_->getMyCourses();
    }
    else if (command == commands::COURSE_CHANNEL) {
        responder_->getCourseChannel(args);
    }
    else if (command == commands::COURSE_POST) {
        responder_->getCoursePost(args);
    }
    else {
        throw NotFoundException(err_messages::NO_MATCHING_COMMAND);
    }
}

void UtgramRouter::executeDeleteRequest(Request req) {
    std::string command = req.getCommand();
    Arguments args = req.getArgs();
    if (command == commands::POST) {
        responder_->deletePost(args);
    }
    else if (command == commands::MY_COURSES) {
        responder_->deleteFromMyCourses(args);
    }
    else {
        throw NotFoundException(err_messages::NO_MATCHING_COMMAND);
    }
}
