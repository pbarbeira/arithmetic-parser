//
// Created by pbarbeira on 28-03-2025.
//

#include <gtest/gtest.h>

#include "../../cmake-build-debug/_deps/googletest-src/googlemock/include/gmock/gmock-matchers.h"
#include "../../src/parser/Lexer.h"

TEST(ScannerTest, HandleEmptyStream) {
    const std::string input;
    const auto result = Lexer(input).lex();
    EXPECT_EQ(0, result.size());
}

TEST(ScannerTest, HandleBinaryPlusOp) {
    const std::string input = "1 + 1";
    const auto result = Lexer(input).lex();
    EXPECT_EQ(3, result.size());
    ASSERT_THAT(result, testing::ElementsAre("1", "+", "1"));
}

TEST(ScannerTest, HandleBinaryMinusOp) {
    const std::string input = "1 - 1";
    const auto result = Lexer(input).lex();
    EXPECT_EQ(3, result.size());
    ASSERT_THAT(result, testing::ElementsAre("1", "-", "1"));
}

TEST(ScannerTest, HandleBinaryStarOp) {
    const std::string input = "1 * 1";
    const auto result = Lexer(input).lex();
    EXPECT_EQ(3, result.size());
    ASSERT_THAT(result, testing::ElementsAre("1", "*", "1"));
}

TEST(ScannerTest, HandleBinarySlashOp) {
    const std::string input = "1 / 1";
    const auto result = Lexer(input).lex();
    EXPECT_EQ(3, result.size());
    ASSERT_THAT(result, testing::ElementsAre("1", "/", "1"));
}

TEST(ScannerTest, HandleBrackets) {
    const std::string input = "(1 + 1)";
    const auto result = Lexer(input).lex();
    EXPECT_EQ(3, result.size());
    ASSERT_THAT(result, testing::ElementsAre("(", "1", "+", "1", ")"));
}

TEST(ScannerTest, HandleNegatives) {
    const std::string input = "-1 + 1";
    const auto result = Lexer(input).lex();
    EXPECT_EQ(3, result.size());
    ASSERT_THAT(result, testing::ElementsAre("-", "1", "+", "1"));
}

TEST(ScannerTest, HandleExpression) {
    const std::string input = "1 + 2 * (3 + 4)";
    const auto result = Lexer(input).lex();
    EXPECT_EQ(9, result.size());
    ASSERT_THAT(result, testing::ElementsAre("1", "+", "2", "*", "(", "3", " +", "4", ")"));
}

