#include "request.hpp"

#include <iostream>
#include <locale>
#include <map>
#include <string>

#include "../exceptions/exceptions.hpp"
#include "../general/io_utils.hpp"
#include "communication_consts.hpp"

using namespace std;
using namespace communication_consts;

Request::ActionType Request::getActionFromString(string str) {
    if (str == "POST")
        return Request::ActionType::POST;
    if (str == "GET")
        return Request::ActionType::GET;
    if (str == "DELETE")
        return Request::ActionType::DELETE;
    if (str == "PUT")
        return Request::ActionType::PUT;
    throw BadRequestException(err_messages::NO_MATCHING_ACTION_TYPE);
}

Request::Request(std::string command) {
    auto splitedString = io_utils::splitString(command, COMMANDS_DELIM);
    actionType_ = Request::getActionFromString(splitedString[0]);
    if (!Request::validateCommandName(splitedString[1])) {
        throw NotFoundException(err_messages::NO_MATCHING_COMMAND);
    }
    command_ = splitedString[1];
    splitedString = io_utils::mergeInside(splitedString, DOUBLE_QUOTES);
    if (splitedString.size() % 2 == 0) {
        throw BadRequestException(err_messages::CAN_NOT_CONVERTED_TO_REQUEST);
    }

    for (int i = 3; i < (int)splitedString.size(); i += 2) {
        if (args_.find(splitedString[i]) != args_.end()) {
            throw BadRequestException(err_messages::CAN_NOT_CONVERTED_TO_REQUEST);
        }
        args_[splitedString[i]] = splitedString[i + 1];
    }
}

bool Request::validateCommandName(std::string cmd) {
    return (cmd == commands::LOGIN or cmd == commands::LOGOUT or
            cmd == commands::COURSES or cmd == commands::POST or
            cmd == commands::PERSONAL_PAGE or cmd == commands::CONNECT or
            cmd == commands::NOTIFICATION or cmd == commands::PRESENTATION or
            cmd == commands::MY_COURSES or cmd == commands::TA_FORM or
            cmd == commands::SET_PROFILE or cmd == commands::SEND_TA_REQUEST or
            cmd == commands::COURSE_CHANNEL or cmd == commands::CLOSE_TA_FORM or
            cmd == commands::COURSE_POST);
}

Request::ActionType Request::getActionType() { return actionType_; }

std::string Request::getCommand() { return command_; }

Arguments Request::getArgs() { return args_; }
