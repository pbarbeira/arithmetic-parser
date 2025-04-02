//
// Created by pbarbeira on 28-03-2025.
//

#include <gtest/gtest.h>
#include "../src/parser/Lexer.h"
#include "../src/parser/Parser.h"
#include "../src/visitor/Solver.h"

struct Token;
TEST(ArithmeticParserTest, HandlesSimpleExpression) {
    std::string input = "1 + 2 * (3 + 3)";

    std::vector<std::unique_ptr<Token>> tokens = Lexer(input).lex();
    EXPECT_EQ(9, tokens.size());

    auto ast = Parser(std::move(tokens)).parse();
    auto res = Solver().visit(ast.get());
    EXPECT_EQ(13, res);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}