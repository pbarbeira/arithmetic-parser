cmake_minimum_required(VERSION 3.30)
project(arithmetic_parser)

enable_testing()

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/heads/main.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(run_tests
        test/test_main.cpp
        test/parser/lexer_tests.cpp
        test/parser/parser_tests.cpp
        test/visitor/solver_tests.cpp
)

target_link_libraries(run_tests
        GTest::gtest
        GTest::gtest_main
        GTest::gmock
        GTest::gmock_main
)

set(CMAKE_CXX_STANDARD 20)

add_executable(arithmetic_parser
        src/main.cpp
        src/parser/Parser.h
        src/parser/Lexer.h
        src/parser/Token.h
        src/parser/Expr.h
        src/visitor/Solver.h
)
