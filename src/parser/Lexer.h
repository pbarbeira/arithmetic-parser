//
// Created by pbarbeira on 28-03-2025.
//

#ifndef SCANNER_H
#define SCANNER_H

#include <vector>
#include "Token.h"
#include <memory>
#include <regex>

class Lexer {
    int _start{};
    int _current{};
    int _line{};
    std::string _input;

    bool _hasNext()const {
        return _current < _input.size();
    }

    static std::string _removeWhiteSpace(const std::string& str) {
        std::regex pattern(R"(\s+)");
        return std::regex_replace(str, pattern, "");
    }

    std::unique_ptr<Token> _numberToken() {
        _start = _current - 1;
        while (std::isdigit(_input[_current])){
            _current++;
        }
        std::string value = _input.substr(_start, _current - _start);
        return std::make_unique<Token>(value, NUMBER);
    }


    [[nodiscard]] std::unique_ptr<Token> _nextToken() {
        char c = _input[_current++];
        switch (c) {
            case '+': return std::make_unique<Token>("+", PLUS);
            case '-': return std::make_unique<Token>("-", MINUS);
            case '*': return std::make_unique<Token>("*", STAR);
            case '/': return std::make_unique<Token>("/", SLASH);
            case '(': return std::make_unique<Token>("(", LEFT_BRACKET);
            case ')': return std::make_unique<Token>(")", RIGHT_BRACKET);
            default:
                if (std::isdigit(c)) {
                    return _numberToken();
                }
                throw std::runtime_error("Unexpected character");
        }
    }

    public:
        explicit Lexer(const std::string& input):
            _input(_removeWhiteSpace(input)){}

        [[nodiscard]] std::vector<std::unique_ptr<Token>> lex() {
            std::vector<std::unique_ptr<Token>> tokens;
            while (this->_hasNext()) {
                auto token = this->_nextToken();
                tokens.push_back(std::move(token));
            }
            return tokens;
        }

};

#endif //SCANNER_H
