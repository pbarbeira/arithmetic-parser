//
// Created by pbarbeira on 28-03-2025.
//

#ifndef PARSER_H
#define PARSER_H

#include <vector>
#include <memory>

#include "Expr.h"
#include "Token.h"

class Parser {
    std::vector<std::unique_ptr<Token>> _tokens;
    int _current;

    [[nodiscard]] bool _eof() const {
        return _current == _tokens.size();
    }

    [[nodiscard]] Token* _peek() const {
        if (_eof()) {
            return new Token("", END);
        }
        return _tokens[_current].get();
    }

    std::unique_ptr<Literal> _literal() {
        if (_peek()->type == LEFT_BRACKET) {
            _current++;
            auto group = _expression();
            _current++;
            return std::make_unique<Literal>(std::move(group));
        }
        return std::make_unique<Literal>(std::stod(_tokens[_current++]->value));
    }
    
    std::unique_ptr<Unary> _unary() {
        bool negation = false;
        if (_peek()->type == MINUS) {
            negation = true;
            _current++;
        }
        auto value = _literal();
        return std::make_unique<Unary>(std::move(value), negation);
    }
    
    std::unique_ptr<Factor> _factor() {
        auto left = _unary();
        Operation op;
        switch (_peek()->type) {
            case STAR: op = MUL; break;
            case SLASH: op = DIV; break;
            default: return std::make_unique<Factor>(std::move(left));;
        }

        _current++;

        auto right = std::move(_factor());
        return std::make_unique<Factor>(std::move(left), op, std::move(right));
    }
    
    std::unique_ptr<Term> _term() {
        auto left = _factor();
        Operation op;
        switch (_peek()->type) {
            case PLUS: op = ADD; break;
            case MINUS: op = SUB; break;
            default: return std::make_unique<Term>(std::move(left));
        }

        _current++;

        auto right = std::move(_term());
        return std::make_unique<Term>(std::move(left), op, std::move(right));
        
    }
    
    std::unique_ptr<Expr> _expression() {
        auto term = std::move(_term());
        return std::make_unique<Expr>(std::move(term));
    }

    public:
        explicit Parser(std::vector<std::unique_ptr<Token>> tokens):
            _tokens(std::move(tokens)), _current(0) {}

        std::unique_ptr<Expr> parse() {
            return std::move(_expression());
        }
};

#endif //PARSER_H
