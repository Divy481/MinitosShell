#include"shell.hpp"

std::vector<std::string>tokenize(const std::string& input){
    std::string token;
    std::vector<std::string>tokens;
    bool is_quotes = false;
    for(size_t i=0;i<input.size();i++){
        char ch = input[i];
        if(ch =='"'){
            is_quotes =! is_quotes;
            continue;
        }

        if(!is_quotes && std::isspace(ch)){
            if(!token.empty()){
                tokens.push_back(token);
                token.clear();
            }
        }else{
            token += ch;
        }
    }

    if(!token.empty()){
        tokens.push_back(token);
    }
    return tokens;
}