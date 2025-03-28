//
// Created by pbarbeira on 28-03-2025.
//

#include <gtest/gtest.h>

#include "../../cmake-build-debug/_deps/googletest-src/googlemock/include/gmock/gmock-matchers.h"
#include "../../src/parser/Lexer.h"
#include <algorithm>

TEST(ScannerTest, HandleEmptyStream) {
    const std::string input;
    const auto result = Lexer(input).lex();
    EXPECT_EQ(0, result.size());
}

TEST(ScannerTest, HandleBinaryPlusOp) {
    const std::string input = "1 + 1";

    const auto result = Lexer(input).lex();
    EXPECT_EQ(3, result.size());
    
    const auto resultValues = std::transform(result.begin(), result.end(), result.begin(),
        [](const Token& t) { return t.value; });
    ASSERT_THAT(resultValues, testing::ElementsAre("1", "+", "1"));

    const auto resultTypes = std::transform(result.begin(), result.end(), result.begin(),
        [](const Token& t) { return t.type; });
    ASSERT_THAT(resultTypes, testing::ElementsAre(
            NUMBER, PLUS, NUMBER
    ));
}

TEST(ScannerTest, HandleBinaryMinusOp) {
    const std::string input = "1 - 1";

    const auto result = Lexer(input).lex();
    EXPECT_EQ(3, result.size());

    const auto resultValues = std::transform(result.begin(), result.end(), result.begin(),
        [](const Token& t) { return t.value; });
    ASSERT_THAT(resultValues, testing::ElementsAre("1", "-", "1"));

    const auto resultTypes = std::transform(result.begin(), result.end(), result.begin(),
        [](const Token& t) { return t.type; });
    ASSERT_THAT(resultTypes, testing::ElementsAre(
            NUMBER, MINUS, NUMBER
    ));
}

TEST(ScannerTest, HandleBinaryStarOp) {
    const std::string input = "1 * 1";

    const auto result = Lexer(input).lex();
    EXPECT_EQ(3, result.size());

    const auto resultValues = std::transform(result.begin(), result.end(), result.begin(),
        [](const Token& t) { return t.value; });
    ASSERT_THAT(resultValues, testing::ElementsAre("1", "*", "1"));

    const auto resultTypes = std::transform(result.begin(), result.end(), result.begin(),
        [](const Token& t) { return t.type; });
    ASSERT_THAT(resultTypes, testing::ElementsAre(
            NUMBER, STAR, NUMBER
    ));
}

TEST(ScannerTest, HandleBinarySlashOp) {
    const std::string input = "1 / 1";

    const auto result = Lexer(input).lex();
    EXPECT_EQ(3, result.size());

    const auto resultValues = std::transform(result.begin(), result.end(), result.begin(),
        [](const Token& t) { return t.value; });
    ASSERT_THAT(resultValues, testing::ElementsAre("1", "/", "1"));

    const auto resultTypes = std::transform(result.begin(), result.end(), result.begin(),
        [](const Token& t) { return t.type; });
    ASSERT_THAT(resultTypes, testing::ElementsAre(
            NUMBER, SLASH, NUMBER
    ));
}

TEST(ScannerTest, HandleBrackets) {
    const std::string input = "(1 + 1)";

    const auto result = Lexer(input).lex();
    EXPECT_EQ(3, result.size());

    const auto resultValues = std::transform(result.begin(), result.end(), result.begin(),
        [](const Token& t) { return t.value; });
    ASSERT_THAT(resultValues, testing::ElementsAre("(", "1", "+", "1", ")"));

    const auto resultTypes = std::transform(result.begin(), result.end(), result.begin(),
        [](const Token& t) { return t.type; });
    ASSERT_THAT(resultTypes, testing::ElementsAre(
            LEFT_BRACKET, NUMBER, PLUS, NUMBER, RIGHT_BRACKET
    ));
}

TEST(ScannerTest, HandleNegatives) {
    const std::string input = "-1 + 1";

    const auto result = Lexer(input).lex();
    EXPECT_EQ(3, result.size());

    const auto resultValues = std::transform(result.begin(), result.end(), result.begin(),
        [](const Token& t) { return t.value; });
    ASSERT_THAT(resultValues, testing::ElementsAre("-", "1", "+", "1"));

    const auto resultTypes = std::transform(result.begin(), result.end(), result.begin(),
        [](const Token& t) { return t.type; });
    ASSERT_THAT(resultTypes, testing::ElementsAre(
            MINUS, NUMBER, PLUS, NUMBER
    ));
}

TEST(ScannerTest, HandleExpression) {
    const std::string input = "1 + 2 * (3 + 4)";

    const auto result = Lexer(input).lex();
    EXPECT_EQ(9, result.size());

    const auto resultValues = std::transform(result.begin(), result.end(), result.begin(),
        [](const Token& t) { return t.value; });
    ASSERT_THAT(resultValues, testing::ElementsAre("1", "+", "2", "*", "(", "3", " +", "4", ")"));

    const auto resultTypes = std::transform(result.begin(), result.end(), result.begin(),
        [](const Token& t) { return t.type; });
    ASSERT_THAT(resultTypes, testing::ElementsAre(
            NUMBER, PLUS, NUMBER, STAR, LEFT_BRACKET, NUMBER, PLUS, NUMBER, RIGHT_BRACKET
    ));
}

