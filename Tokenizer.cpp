#include "Tokenizer.h"
#include <cctype>

std::vector<std::string> tokenize(const std::string& expression) {
    std::vector<std::string> tokens;
    //Iterates through the length of the expression
    for (size_t i = 0; i < expression.length(); ++i) {

	//Skips over blank spaces
        if (isspace(expression[i]))
            continue;

        std::string token;

	//Checks if the opperator is only one character and if it is one character, it sets it equal to token
        if (expression[i] == 'T' || expression[i] == 'F' || expression[i] == '(' || expression[i] == ')') {
            token = expression[i];
        } else {

            // Handle multi-char operators
            if (expression[i] == '!' || expression[i] == '&' || expression[i] == '|' || expression[i] == '^') {
                token += expression[i];
		
                if (i + 1 < expression.length() && (expression[i + 1] == '&' || expression[i + 1] == '|')) {
                    token += expression[i + 1];
                    i++;
                }
            }
        }
        if (!token.empty())
            tokens.push_back(token);
    }
    return tokens;
}

