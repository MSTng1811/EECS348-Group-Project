#include <iostream>
#include <string>
#include <vector>
#include "Tokenizer.h"
#include "Parser.h"
#include "Evaluator.h"

int main() {
    std::string expression;
    std::cout << "Enter a Boolean expression: ";
    std::getline(std::cin, expression);

    try {
        std::vector<std::string> tokens = tokenize(expression);
        std::vector<std::string> postfix = infixToPostfix(tokens);
        bool result = evaluatePostfix(postfix);
        std::cout << "The expression evaluates to: " << (result ? "True" : "False") << std::endl;
    } catch (const std::runtime_error& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}

