//
// Created by pbarbeira on 28-03-2025.
//

#ifndef SCANNER_H
#define SCANNER_H

#include <vector>

class Lexer {
    int _start{};
    int _current{};
    int _line{};
    std::string _input;
    std::vector<std::string> _tokens;

    public:
        explicit Lexer(const std::string& input):
            _input(input){}

        std::vector<std::string> lex() {
            std::vector<std::string> tokens;

            return tokens;
        }
};

#endif //SCANNER_H
