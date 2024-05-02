#include "Tokenizer.h"
#include <cctype>
#include <stdexcept>

std::vector<std::string> tokenize(const std::string &expression) {
  std::vector<std::string> tokens;
  // Iterates through the length of the expression
  for (size_t i = 0; i < expression.length(); ++i) {
    // Skips over blank spaces
    if (isspace(expression[i]))
      continue;

    std::string token;

    // Checks if the character is a valid token
    if (expression[i] == 'T' || expression[i] == 'F' || expression[i] == '(' ||
        expression[i] == ')') {
      token = expression[i];
    } else if (expression[i] == '!' || expression[i] == '&' ||
               expression[i] == '|') {
      token += expression[i];

      if (i + 1 < expression.length() &&
          (expression[i + 1] == '&' || expression[i + 1] == '|')) {
        token += expression[i + 1];
        i++;
      }
    } else {
      // Invalid character detected
      throw std::runtime_error("Invalid input");
    }
    tokens.push_back(token);
  }
  return tokens;
}
