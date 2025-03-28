//
// Created by pbarbeira on 28-03-2025.
//

#include <gtest/gtest.h>

#include "../../cmake-build-debug/_deps/googletest-src/googlemock/include/gmock/gmock-matchers.h"
#include "../../src/parser/Lexer.h"
#include <algorithm>

TEST(LexerTest, HandleEmptyStream) {
    const std::string input;
    const auto result = Lexer(input).lex();
    EXPECT_EQ(0, result.size());
}

TEST(LexerTest, HandleBinaryPlusOp) {
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

TEST(LexerTest, HandleBinaryMinusOp) {
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

TEST(LexerTest, HandleBinaryStarOp) {
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

TEST(LexerTest, HandleBinarySlashOp) {
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

TEST(LexerTest, HandleBrackets) {
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

TEST(LexerTest, HandleNegatives) {
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

TEST(LexerTest, HandleExpression) {
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

