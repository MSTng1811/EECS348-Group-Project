#include "BooleanEvaluator.h" // Assuming this header provides the evaluateBooleanExpression function.
#include "Evaluator.h"
#include "Parser.h"
#include "Tokenizer.h"
#include <algorithm> // Needed for std::find
#include <iostream>
#include <limits>
#include <string>
#include <vector>

// Helper function to check if any operator is present in the tokens
bool containsOperator(const std::vector<std::string> &tokens) {
  const std::vector<char> operators = {'&', '!', '$', '@', '|'};
  for (const auto &token : tokens) {
    // Check each token if it's one of the operators
    if (std::any_of(token.begin(), token.end(), [&](char c) {
          return std::find(operators.begin(), operators.end(), c) !=
                 operators.end();
        })) {
      return true;
    }
  }
  return false;
}

int main(int argc, char **argv) {
  if (argc == 2) {
    // Command-line mode: evaluate the expression provided as an argument.
    std::string expression(argv[1]);
    try {
      bool result = evaluateBooleanExpression(expression);
      std::cout << (result ? "True" : "False") << std::endl;
      return 0;
    } catch (const std::exception &e) {
      std::cerr << "Error: Invalid Input. " << e.what() << std::endl;
      return 1;
    }
  } else {
    // Interactive mode: allow the user to enter expressions manually.
    std::string expression;
    std::cout << "Enter 'exit' to quit or a Boolean expression to evaluate:"
              << std::endl;

    while (true) {
      std::cout << "> ";
      std::getline(std::cin, expression);

      if (expression == "exit") {
        break;
      }

      try {
        std::vector<std::string> tokens = tokenize(expression);
        if (tokens.empty() || !containsOperator(tokens)) {
          throw std::runtime_error("Invalid input");
        }
        std::vector<std::string> postfix = infixToPostfix(tokens);
        bool result = evaluatePostfix(postfix);
        std::cout << "The expression evaluates to: "
                  << (result ? "True" : "False") << std::endl;
      } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
      }
    }
  }

  return 0;
}