//
// Created by pbarbeira on 28-03-2025.
//

#ifndef EXPR_H
#define EXPR_H

#include <memory>

struct Expr;
struct Term;
struct Factor;
struct Unary;
struct Literal;

template<typename T>
struct Visitor{
    virtual ~Visitor() = default;

    virtual T visitExpr(Expr* expr) = 0;
    virtual T visitTerm(Term* term) = 0;
    virtual T visitFactor(Factor* factor) = 0;
    virtual T visitUnary(Unary* unary) = 0;
    virtual T visitLiteral(Literal* literal) = 0;
};

/*
 * Grammar:
 * Expr -> Term
 * Term -> Factor | Factor ("+" | "-") Term
 * Factor -> Unary | Unary ("*" | "/") Factor
 * Unary -> "-" Literal | Literal
 * Literal -> NUMBER | Group
 * Group -> "(" Expr ")"
 */

enum Operation {
    ADD, SUB, MUL, DIV, NONE
};

struct Literal {
    double value;
    std::unique_ptr<Expr> group;

    explicit Literal(const double& value):
        value(value), group(nullptr){};

    explicit Literal(std::unique_ptr<Expr> group):
        value(0), group(std::move(group)){}

    [[nodiscard]] bool isGroup() const{
        return group != nullptr;
    }

    template<typename T>
    T accept(Visitor<T>* visitor){
        return visitor->visitLiteral(this);
    }
};

struct Unary {
    bool negation;
    std::unique_ptr<Literal> value;

    explicit Unary(std::unique_ptr<Literal> value, const bool negation = false):
        negation(negation), value(std::move(value)){}

    template<typename T>
    T accept(Visitor<T>* visitor){
        return visitor->visitUnary(this);
    }
};

struct Factor {
    std::unique_ptr<Unary> left;
    Operation op;
    std::unique_ptr<Factor> right;

    explicit Factor(std::unique_ptr<Unary> left):
        left(std::move(left)), op(NONE), right(nullptr){}

    explicit Factor(std::unique_ptr<Unary> left, const Operation& op, std::unique_ptr<Factor>right):
        left(std::move(left)), op(std::move(op)), right(std::move(right)){}

    bool isUnary() const {
        return right == nullptr;
    }

    template<typename T>
    T accept(Visitor<T>* visitor){
        return visitor->visitFactor(this);
    }
};

struct Term {
    std::unique_ptr<Factor> left;
    Operation op;
    std::unique_ptr<Term> right;

    explicit Term(std::unique_ptr<Factor> left):
        left(std::move(left)), op(NONE), right(nullptr){};

    explicit Term(std::unique_ptr<Factor> left, const Operation& op, std::unique_ptr<Term> right):
        left(std::move(left)), op(std::move(op)), right(std::move(right)){}

    bool isFactor() const {
        return right == nullptr;
    }

    template<typename T>
    T accept(Visitor<T>* visitor){
        return visitor->visitTerm(this);
    }
};

struct Expr {
    std::unique_ptr<Term> term;

    explicit Expr(std::unique_ptr<Term> term):
        term(std::move(term)){}

    template<typename T>
    T accept(Visitor<T>* visitor){
        return visitor->visitExpr(this);
    }
};

#endif //EXPR_H
