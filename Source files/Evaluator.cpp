#include "Evaluator.h"
#include <stack>

bool evalOp(const std::string &op, bool a, bool b = false) {
  if (op == "!")
    return !a;
  if (op == "&")
    return a && b;
  if (op == "|")
    return a || b;
  if (op == "$")
    return a != b;
  if (op == "@")
    return !(a && b);
  return false;
}

bool evaluatePostfix(const std::vector<std::string> &postfix) {
  std::stack<bool> stack;
  for (const std::string &token : postfix) {
    if (token == "T" || token == "F") {
      stack.push(token == "T");
    } else {
      if (token == "!") {
        bool val = stack.top();
        stack.pop();
        stack.push(evalOp(token, val));
      } else {
        bool val2 = stack.top();
        stack.pop();
        bool val1 = stack.top();
        stack.pop();
        stack.push(evalOp(token, val1, val2));
      }
    }
  }
  return stack.top();
}
