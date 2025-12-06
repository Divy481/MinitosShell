#include"pipe.hpp"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string>
#include <vector>
#include "tokenize.hpp"


void pipe_command(char** left_cmd,char** right__cmd){
    int fd[2];
    if(pipe(fd)==-1){
        perror("pipe");
        return;
    }

    pid_t pid1 = fork();
    if(pid1 ==0){
        //Left Command Processed
        dup2(fd[1],STDOUT_FILENO);
        close(fd[0]);
        close(fd[1]);
        execvp(left_cmd[0],left_cmd);
        perror("Left COmmand Error");
        exit(1);
    }

    pid_t pid2 = fork();
    if(pid2 == 0){
        dup2(fd[0],STDIN_FILENO);
        close(fd[1]);
        close(fd[0]);
        execvp(right__cmd[0],right__cmd);
        perror("Right command Error");
        exit(1);
    }

    close(fd[0]);
    close(fd[1]);
    waitpid(pid1,NULL,0);
    waitpid(pid2,NULL,0);
}

bool praser_pipe(std::string &input,std::vector<char*>&left_cmd,
                 std::vector<char*>&right_cmd){
        
    std::size_t pos = input.find('|');

    if(pos == std::string::npos){
        return false;
    }

    std::string left = input.substr(0,pos);
    std::string right = input.substr(pos+1);
    std::vector<std::string> t1 = tokenize(left);
    for(auto& s:t1)left_cmd.push_back(const_cast<char*>(s.c_str()));
    left_cmd.push_back(nullptr);
    
    std::vector<std::string> t2 = tokenize(right);
    for(auto& s:t2)right_cmd.push_back(const_cast<char*>(s.c_str()));
    right_cmd.push_back(nullptr);

    return true;
}