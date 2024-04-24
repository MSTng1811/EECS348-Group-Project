#include <iostream>
#include <string>
#include "BooleanEvaluator.h"

int main() {
    std::string expression;
    std::cout << "Enter a Boolean expression: ";
    try {
        if (!std::getline(std::cin, expression)) {
            throw std::runtime_error("Failed to read input");
        }
        bool result = evaluateBooleanExpression(expression);
        std::cout << "The expression evaluates to: " << (result ? "True" : "False") << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    return 0;
}

