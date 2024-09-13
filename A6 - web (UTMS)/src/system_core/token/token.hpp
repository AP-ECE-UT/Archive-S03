#ifndef TOKEN_HPP_INCLUDE
#define TOKEN_HPP_INCLUDE

#include <string>

class Token {
public:
    Token();
    Token(std::string id, std::string pass, bool valid);
    std::string getId();
    std::string getPass();
    bool isValid();
    void disable();

private:
    std::string id_;
    std::string pass_;
    bool valid_;
};

#endif // TOKEN_HPP_INCLUDE
