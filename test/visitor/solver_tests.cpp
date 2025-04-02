//
// Created by pbarbeira on 28-03-2025.
//

#include <gtest/gtest.h>
#include "../../src/visitor/Solver.h"

TEST(SolverTest, HandleNumberLiteral) {
    auto solver = Solver();

    auto literal = std::make_unique<Literal>(2);
    auto unary = std::make_unique<Unary>(std::move(literal));
    auto factor = std::make_unique<Factor>(std::move(unary));
    auto term = std::make_unique<Term>(std::move(factor));
    const auto expr = std::make_unique<Expr>(std::move(term));

    const auto res = solver.visit(expr.get());
    EXPECT_EQ(2.0, res);
}

TEST(SolverTest, HandleNegationUnary) {
    auto solver = Solver();

    auto literal = std::make_unique<Literal>(2);
    auto unary = std::make_unique<Unary>(std::move(literal), true);
    auto factor = std::make_unique<Factor>(std::move(unary));
    auto term = std::make_unique<Term>(std::move(factor));
    const auto expr = std::make_unique<Expr>(std::move(term));

    const auto res = solver.visit(expr.get());
    EXPECT_EQ(-2.0, res);
}

TEST(SolverTest, HandleLiteralUnary) {
    auto solver = Solver();

    auto literal = std::make_unique<Literal>(2);
    auto unary = std::make_unique<Unary>(std::move(literal));
    auto factor = std::make_unique<Factor>(std::move(unary));
    auto term = std::make_unique<Term>(std::move(factor));
    const auto expr = std::make_unique<Expr>(std::move(term));

    const auto res = solver.visit(expr.get());
    EXPECT_EQ(2.0, res);
}

TEST(SolverTest, HandleFactorMul) {
    auto solver = Solver();

    auto literal_1 = std::make_unique<Literal>(2);
    auto literal_2 = std::make_unique<Literal>(3);
    auto unary_1 = std::make_unique<Unary>(std::move(literal_1));
    auto unary_2 = std::make_unique<Unary>(std::move(literal_2));
    auto rightSide = std::make_unique<Factor>(std::move(unary_2));
    auto factor = std::make_unique<Factor>(std::move(unary_1), MUL, std::move(rightSide));
    auto term = std::make_unique<Term>(std::move(factor));
    const auto expr = std::make_unique<Expr>(std::move(term));

    auto res = solver.visit(expr.get());
    EXPECT_EQ(6.0, res);
}

//2 * 3 * 4 = 24
TEST(SolverTest, HandleFactorMulMultiple) {
    auto solver = Solver();

    auto literal_1 = std::make_unique<Literal>(2);
    auto literal_2 = std::make_unique<Literal>(3);
    auto literal_3 = std::make_unique<Literal>(4);
    auto unary_1 = std::make_unique<Unary>(std::move(literal_1));
    auto unary_2 = std::make_unique<Unary>(std::move(literal_2));
    auto unary_3 = std::make_unique<Unary>(std::move(literal_3));
    auto rightFactor = std::make_unique<Factor>(std::move(unary_3));
    auto rightSide = std::make_unique<Factor>(std::move(unary_2), MUL, std::move(rightFactor));
    auto factor = std::make_unique<Factor>(std::move(unary_1), MUL, std::move(rightSide));
    auto term = std::make_unique<Term>(std::move(factor));
    const auto expr = std::make_unique<Expr>(std::move(term));

    const auto res = solver.visit(expr.get());
    EXPECT_EQ(24.0, res);
}

TEST(SolverTest, HandleFactorDiv) {
    auto solver = Solver();

    auto literal_1 = std::make_unique<Literal>(6);
    auto literal_2 = std::make_unique<Literal>(3);
    auto unary_1 = std::make_unique<Unary>(std::move(literal_1));
    auto unary_2 = std::make_unique<Unary>(std::move(literal_2));
    auto rightSide = std::make_unique<Factor>(std::move(unary_2));
    auto factor = std::make_unique<Factor>(std::move(unary_1), DIV, std::move(rightSide));
    auto term = std::make_unique<Term>(std::move(factor));
    const auto expr = std::make_unique<Expr>(std::move(term));

    const auto res = solver.visit(expr.get());
    EXPECT_EQ(2.0, res);
}

TEST(SolverTest, HandleFactorDivMultiple) {
    auto solver = Solver();

    auto literal_1 = std::make_unique<Literal>(4);
    auto literal_2 = std::make_unique<Literal>(2);
    auto literal_3 = std::make_unique<Literal>(2);
    auto unary_1 = std::make_unique<Unary>(std::move(literal_1));
    auto unary_2 = std::make_unique<Unary>(std::move(literal_2));
    auto unary_3 = std::make_unique<Unary>(std::move(literal_3));
    auto rightFactor = std::make_unique<Factor>(std::move(unary_3));
    auto rightSide = std::make_unique<Factor>(std::move(unary_2), DIV, std::move(rightFactor));
    auto factor = std::make_unique<Factor>(std::move(unary_1), DIV, std::move(rightSide));
    auto term = std::make_unique<Term>(std::move(factor));
    const auto expr = std::make_unique<Expr>(std::move(term));

    const auto res = solver.visit(expr.get());
    EXPECT_EQ(1, res);
}


TEST(SolverTest, HandleTermSum) {
    auto solver = Solver();

    auto literal_1 = std::make_unique<Literal>(3);
    auto literal_2 = std::make_unique<Literal>(2);
    auto unary_1 = std::make_unique<Unary>(std::move(literal_1));
    auto unary_2 = std::make_unique<Unary>(std::move(literal_2));
    auto leftSide = std::make_unique<Factor>(std::move(unary_1));
    auto rightSideFactor = std::make_unique<Factor>(std::move(unary_2));
    auto rightSide = std::make_unique<Term>(std::move(rightSideFactor));
    auto term = std::make_unique<Term>(std::move(leftSide), ADD, std::move(rightSide));
    const auto expr = std::make_unique<Expr>(std::move(term));

    const auto res = solver.visit(expr.get());
    EXPECT_EQ(5.0, res);
}

TEST(SolverTest, HandleTermSub) {
    auto solver = Solver();

    auto literal_1 = std::make_unique<Literal>(3);
    auto literal_2 = std::make_unique<Literal>(2);
    auto unary_1 = std::make_unique<Unary>(std::move(literal_1));
    auto unary_2 = std::make_unique<Unary>(std::move(literal_2));
    auto leftSide = std::make_unique<Factor>(std::move(unary_1));
    auto rightSideFactor = std::make_unique<Factor>(std::move(unary_2));
    auto rightSide = std::make_unique<Term>(std::move(rightSideFactor));
    auto term = std::make_unique<Term>(std::move(leftSide), SUB, std::move(rightSide));
    const auto expr = std::make_unique<Expr>(std::move(term));

    const auto res = solver.visit(expr.get());
    EXPECT_EQ(1.0, res);
}

