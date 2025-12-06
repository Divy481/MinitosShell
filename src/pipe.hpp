#ifndef PIPE_HPP
#define PIPE_HPP
#include<vector>
#include<string>
void pipe_command(char** left_cmd,char** right_cmd);
bool praser_pipe(std::string &input,std::vector<char*>&left_cmd,
                 std::vector<char*>&right_cmd);

#endif  //PIPE_HPP