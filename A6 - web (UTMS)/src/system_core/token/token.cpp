#include "token.hpp"

#include <string>

Token::Token() { valid_ = false; }

Token::Token(std::string id, std::string pass, bool valid) {
    id_ = id;
    pass_ = pass;
    valid_ = valid;
}

std::string Token::getId() { return id_; }

std::string Token::getPass() { return pass_; }

bool Token::isValid() { return valid_; }

void Token::disable() { valid_ = false; }
