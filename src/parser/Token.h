#include <utility>

//
// Created by pbarbeira on 28-03-2025.
//

#ifndef TOKEN_H
#define TOKEN_H

enum TokenType {
    PLUS, MINUS, STAR, SLASH,
    LEFT_BRACKET, RIGHT_BRACKET,
    NUMBER,
};

struct Token {
    std::string value;
    TokenType type;

    explicit Token(std::string  value, const TokenType& type) :
        value(std::move(value)), type(type) {}
};

#endif //TOKEN_H
