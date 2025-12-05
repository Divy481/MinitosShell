#ifndef HISTORY_HPP
#define HISTORY_HPP

#include<vector>
#include<string>
#include<ctime>
void save_history(const std::string& cmd, std::time_t t);
void load_history(std::vector<std::string>& cmds,
                  std::vector<std::time_t>& times);
void history_command();
#endif   //HISTROY_HPP