#include"shell.hpp"

//shell loop
//input parsing 
//command excution
//handle built-in command cd,pwd,etc.
//excute external commands
//manage enivrnemt variable 
//manage path 
//error handling  


void shell_loop(char** env){
    std::string input;
    std::vector<char*> argc;
    while(true){
        std::cout<<"[SHELL]> ";
        if(!std::getline(std::cin,input)){
            perror("EXIT");
            break;
        }
        std::vector<std::string> tokens = tokenize(input);

        for(auto& token:tokens){
            argc.push_back(const_cast<char*>(token.c_str()));
        }

        argc.push_back(nullptr);
        
    }
}
int main(int argc,char** argv,char** env){
    (void)argc;
    (void)argv;
    shell_loop(env);
    return 0;
}