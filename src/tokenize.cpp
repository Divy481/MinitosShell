#include "tokenize.hpp"
#include <vector>
#include<string>



std::vector<std::string> tokenize(const std::string& input) {
    std::string token;
    std::vector<std::string> tokens;
    bool in_quotes = false;

    for (char ch : input) {
        if (ch == '"') {
            in_quotes = !in_quotes;
            continue;
        }

        if (!in_quotes && isspace(ch)) {
            if (!token.empty()) {
                tokens.push_back(token);
                token.clear();
            }
        } else {
            token += ch;
        }
    }

    if (!token.empty())
        tokens.push_back(token);

    return tokens;
}