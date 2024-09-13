#ifndef REQUEST_HPP_INCLUDE
#define REQUEST_HPP_INCLUDE

#include <map>
#include <string>

constexpr char COMMANDS_DELIM = ' ';
constexpr char DOUBLE_QUOTES = '"';

using Arguments = std::map<std::string, std::string>;

class Request {
public:
    Request(std::string command);

    enum ActionType { POST,
                      PUT,
                      GET,
                      DELETE };

    ActionType getActionType();
    std::string getCommand();
    Arguments getArgs();

    static Request::ActionType getActionFromString(std::string str);
    static bool validateCommandName(std::string cmd);

private:
    ActionType actionType_;
    std::string command_;
    Arguments args_;
};

#endif // REQUEST_HPP_INCLUDE
