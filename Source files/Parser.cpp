#include "Parser.h"
#include <stack>
#include <stdexcept>

int getPrecedence(const std::string &op) {
  if (op == "!")
    return 3;
  if (op == "&" || op == "|" || op == "@")
    return 2;
  if (op == "$")
    return 1; // Correct precedence for XOR
  return 0;
}

bool isOperator(const std::string &token) {
  return token == "!" || token == "&" || token == "|" || token == "$" ||
         token == "@";
}

bool isValidExpression(const std::vector<std::string> &tokens) {
  // Check if the expression starts or ends with an operator
  if (tokens.front() == "&" || tokens.front() == "|" || tokens.front() == "$" ||
      tokens.front() == "@")
    return false;
  if (tokens.back() == "&" || tokens.back() == "|" || tokens.back() == "$" ||
      tokens.back() == "@")
    return false;

  for (size_t i = 0; i < tokens.size() - 1; ++i) {
    // Check for consecutive operators
    if (isOperator(tokens[i]) && isOperator(tokens[i + 1]))
      return false;
    // Check for invalid operator placement
    if ((tokens[i] == "!" || tokens[i] == "&" || tokens[i] == "|") &&
        tokens[i + 1] == ")")
      return false;
    if (tokens[i] == "(" && (tokens[i + 1] == "&" || tokens[i + 1] == "|" ||
                             tokens[i + 1] == "$" || tokens[i + 1] == "@"))
      return false;
    // Check for adjacent operands without an operator
    if ((tokens[i] == "T" || tokens[i] == "F") &&
        (tokens[i + 1] == "T" || tokens[i + 1] == "F"))
      return false;
  }
  return true;
}

std::vector<std::string>
infixToPostfix(const std::vector<std::string> &tokens) {
  if (!isValidExpression(tokens)) {
    throw std::runtime_error("Invalid expression");
  }

  std::vector<std::string> postfix;
  std::stack<std::string> stack;

  for (const std::string &token : tokens) {
    if (token == "T" || token == "F") {
      postfix.push_back(token);
    } else if (token == "(") {
      stack.push(token);
    } else if (token == ")") {
      while (!stack.empty() && stack.top() != "(") {
        postfix.push_back(stack.top());
        stack.pop();
      }
      stack.pop(); // Pop the '('
    } else if (isOperator(token)) {
      while (!stack.empty() &&
             getPrecedence(stack.top()) >= getPrecedence(token)) {
        postfix.push_back(stack.top());
        stack.pop();
      }
      stack.push(token);
    }
  }

  while (!stack.empty()) {
    postfix.push_back(stack.top());
    stack.pop();
  }
  return postfix;
}
