#include "Parser.h"
#include <stack>

int getPrecedence(const std::string& op) {
    if (op == "!") return 3;
    if (op == "&") return 2;
    if (op == "|") return 2;
    if (op == "^") return 1;
    return 0;
}

bool isOperator(const std::string& token) {
    return token == "!" || token == "&" || token == "|" || token == "^";
}

std::vector<std::string> infixToPostfix(const std::vector<std::string>& tokens) {
    std::vector<std::string> postfix;
    std::stack<std::string> stack;

    for (const std::string& token : tokens) {
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
            while (!stack.empty() && getPrecedence(stack.top()) >= getPrecedence(token)) {
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

