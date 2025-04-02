//
// Created by pbarbeira on 28-03-2025.
//

#include <gtest/gtest.h>

#include "../../src/parser/Parser.h"
#include "../../src/visitor/Solver.h"

TEST(ParserTest, ParseAddExpression) {
    std::vector<std::unique_ptr<Token>> tokens;
    tokens.emplace_back(std::make_unique<Token>("1", NUMBER));
    tokens.emplace_back(std::make_unique<Token>("+", PLUS));
    tokens.emplace_back(std::make_unique<Token>("1", NUMBER));

    auto parser = Parser(std::move(tokens));  // Move the vector
    const auto expr = parser.parse();
    auto solver = Solver();
    const auto res = solver.visit(expr.get());
    EXPECT_EQ(2, res);
}


TEST(ParserTest, ParseSubExpression) {
    std::vector<std::unique_ptr<Token>> tokens;
    tokens.emplace_back(std::make_unique<Token>("1", NUMBER));
    tokens.emplace_back(std::make_unique<Token>("-", MINUS));
    tokens.emplace_back(std::make_unique<Token>("1", NUMBER));

    auto parser = Parser(std::move(tokens));  // Move the vector
    const auto expr = parser.parse();
    auto solver = Solver();
    const auto res = solver.visit(expr.get());
    EXPECT_EQ(0, res);
}


TEST(ParserTest, ParseMulExpression) {
    std::vector<std::unique_ptr<Token>> tokens;
    tokens.emplace_back(std::make_unique<Token>("4", NUMBER));
    tokens.emplace_back(std::make_unique<Token>("*", STAR));
    tokens.emplace_back(std::make_unique<Token>("2", NUMBER));

    auto parser = Parser(std::move(tokens));  // Move the vector
    const auto expr = parser.parse();
    auto solver = Solver();
    const auto res = solver.visit(expr.get());
    EXPECT_EQ(8, res);
}


TEST(ParserTest, ParseDivExpression) {
    std::vector<std::unique_ptr<Token>> tokens;
    tokens.emplace_back(std::make_unique<Token>("4", NUMBER));
    tokens.emplace_back(std::make_unique<Token>("/", SLASH));
    tokens.emplace_back(std::make_unique<Token>("2", NUMBER));

    auto parser = Parser(std::move(tokens));  // Move the vector
    const auto expr = parser.parse();
    auto solver = Solver();
    const auto res = solver.visit(expr.get());
    EXPECT_EQ(2, res);
}

TEST(ParserTest, ParsePrecedenceExpression) {
    std::vector<std::unique_ptr<Token>> tokens;
    tokens.emplace_back(std::make_unique<Token>("4", NUMBER));
    tokens.emplace_back(std::make_unique<Token>("+", PLUS));
    tokens.emplace_back(std::make_unique<Token>("4", NUMBER));
    tokens.emplace_back(std::make_unique<Token>("/", SLASH));
    tokens.emplace_back(std::make_unique<Token>("2", NUMBER));
    tokens.emplace_back(std::make_unique<Token>("+", PLUS));
    tokens.emplace_back(std::make_unique<Token>("1", NUMBER));

    auto parser = Parser(std::move(tokens));  // Move the vector
    const auto expr = parser.parse();
    auto solver = Solver();
    const auto res = solver.visit(expr.get());
    EXPECT_EQ(7, res);
}

TEST(ParserTest, ParseParenthesizedExpression) {
    std::vector<std::unique_ptr<Token>> tokens;
    tokens.emplace_back(std::make_unique<Token>("(", LEFT_BRACKET));
    tokens.emplace_back(std::make_unique<Token>("4", NUMBER));
    tokens.emplace_back(std::make_unique<Token>("+", PLUS));
    tokens.emplace_back(std::make_unique<Token>("4", NUMBER));
    tokens.emplace_back(std::make_unique<Token>(")", RIGHT_BRACKET));
    tokens.emplace_back(std::make_unique<Token>("/", SLASH));
    tokens.emplace_back(std::make_unique<Token>("2", NUMBER));

    auto parser = Parser(std::move(tokens));  // Move the vector
    const auto expr = parser.parse();
    auto solver = Solver();
    const auto res = solver.visit(expr.get());
    EXPECT_EQ(4, res);
}
