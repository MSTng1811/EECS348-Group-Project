#include <iostream>
#include <string>
#include <vector>
#include "Tokenizer.h"
#include "Parser.h"
#include "Evaluator.h"

int main() {
    std::string expression;

    while (true) {
        std::cout << "Enter a Boolean expression (or type 'exit' to quit): ";
        std::getline(std::cin, expression);

        if (expression == "exit") {
            break;
        }

        try {
            std::vector<std::string> tokens = tokenize(expression);
            if (tokens.empty()) {
                throw std::runtime_error("Invalid input");
            }
            std::vector<std::string> postfix = infixToPostfix(tokens);
            bool result = evaluatePostfix(postfix);
            std::cout << "The expression evaluates to: " << (result ? "True" : "False") << std::endl;
        } catch (const std::runtime_error& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }

    return 0;
}

