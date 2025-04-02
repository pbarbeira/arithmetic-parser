#include <iostream>
#include <memory>
#include <utility>
#include <vector>
#include "parser/Expr.h"
#include "parser/Lexer.h"
#include "parser/Parser.h"
#include "parser/Token.h"
#include "visitor/Solver.h"

class Test {
    std::vector<std::unique_ptr<Token>> test;

public:
    explicit Test(std::vector<std::unique_ptr<Token>> test) : test(std::move(test)) {}

    void print() const {
        for (const auto& token : test) {
            std::cout << token->value << " ";
        }
        std::cout << std::endl;
    }
};

int main() {
    while (true) {
        std::cout << "> ";

        std::string input;
        if (!std::getline(std::cin, input)) {
            return 0;
        }

        if (input.empty()) {
            continue;
        }

        try {
            std::vector<std::unique_ptr<Token>> tokens = Lexer(input).lex();

            auto ast = Parser(std::move(tokens)).parse();
            auto res = Solver().visit(ast.get());

            std::cout << res << std::endl;
        }catch (std::exception& e) {
            std::cout << "Error: " << e.what() << std::endl;
        }
    }
}
