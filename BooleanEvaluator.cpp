#include "BooleanEvaluator.h"
#include "Tokenizer.h"
#include "Parser.h"
#include "Evaluator.h"

//Call tokenizer
bool evaluateBooleanExpression(const std::string& expr) {
    std::vector<std::string> tokens = tokenize(expr);
    std::vector<std::string> postfix = infixToPostfix(tokens);
    return evaluatePostfix(postfix);
}

