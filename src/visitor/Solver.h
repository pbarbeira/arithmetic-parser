//
// Created by pbarbeira on 28-03-2025.
//

#ifndef SOLVER_H
#define SOLVER_H

#include "../parser/Expr.h"

class Solver : public Visitor<double> {
    friend class SolverTest;

    double visitExpr(Expr* expr) override {
        return expr->term->accept<double>(this);
    };

    double visitTerm(Term* term) override {
        if (term->isFactor()) {
            return term->left->accept(this);
        }
        const double v1 = term->left->accept(this);
        const double v2 = term->right->accept(this);
        switch (term->op) {
            case ADD: return v1 + v2;
            case SUB: return v1 - v2;
            default: throw std::runtime_error("Invalid factor token\n");
        }
    };

    double visitFactor(Factor* factor) override {
        if (factor->isUnary()) {
            return factor->left->accept(this);
        }

        const double v1 = factor->left->accept(this);
        const double v2 = factor->right->accept(this);
        switch (factor->op) {
            case MUL: return v1 * v2;
            case DIV: return v1 / v2;
            default: throw std::runtime_error("Invalid factor token\n");
        }
    };

    double visitUnary(Unary* unary) override {
        const double value = unary->value->accept(this);
        return unary->negation ? -value : value;
    };

    double visitLiteral(Literal* literal) override {
        return literal->isGroup() ?
            literal->group->accept(this) :
            literal->value;
    };
    public:
        double visit(Expr* expr) {
            return visitExpr(expr);
        }
};

#endif //SOLVER_H
