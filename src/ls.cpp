#include "ls.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <dirent.h>
#include <cstring>
#include <algorithm>
#include <iomanip>
#include <sys/stat.h>
#include <unistd.h>

// Colors
#define RESET   "\033[0m"
#define BLUE    "\033[34m"   // Directory
#define GREEN   "\033[32m"   // Executable
#define CYAN    "\033[36m"   // Symlink

// -------------------------------------------------------------------
// Strip ANSI escape codes → return visible length
// -------------------------------------------------------------------
int visible_length(const std::string& s) {
    int len = 0;
    bool esc = false;

    for (char c : s) {
        if (c == '\033') {
            esc = true;
        } else if (esc && c == 'm') {
            esc = false;
        } else if (!esc) {
            len++;
        }
    }
    return len;
}

// -------------------------------------------------------------------
// Apply color based on file type
// -------------------------------------------------------------------
std::string colored_name(const char* path, const char* name) {
    struct stat st;
    std::string full = std::string(path) + "/" + name;

    if (lstat(full.c_str(), &st) == -1) {
        return name;
    }

    if (S_ISDIR(st.st_mode))
        return std::string(BLUE) + name + RESET;

    if (S_ISLNK(st.st_mode))
        return std::string(CYAN) + name + RESET;

    if (st.st_mode & S_IXUSR)
        return std::string(GREEN) + name + RESET;

    return name;
}

// -------------------------------------------------------------------
// Print in TWO columns with perfect alignment
// -------------------------------------------------------------------
void print_two_columns(const std::vector<std::string>& items) {
    if (items.empty()) return;

    size_t n = items.size();
    size_t mid = (n + 1) / 2;

    int maxLen = 0;
    for (auto& name : items)
        maxLen = std::max(maxLen, visible_length(name));

    int colWidth = maxLen + 4;

    for (size_t i = 0; i < mid; i++) {
        // Left side
        std::string left = items[i];
        std::cout << left;
        std::cout << std::string(colWidth - visible_length(left), ' ');

        // Right side
        if (i + mid < n) {
            std::string right = items[i + mid];
            std::cout << right;
        }

        std::cout << "\n";
    }
}

// -------------------------------------------------------------------
// Main ls command
// -------------------------------------------------------------------
int ls_command(char** args) {
    const char* path = ".";
    bool showHidden = false;

    for (int i = 1; args[i]; i++) {
        if (strcmp(args[i], "-a") == 0)
            showHidden = true;
        else
            path = args[i];
    }

    DIR* dir = opendir(path);
    if (!dir) {
        perror("ls");
        return -1;
    }

    std::vector<std::string> items;
    struct dirent* entry;

    while ((entry = readdir(dir)) != nullptr) {
        if (!showHidden && entry->d_name[0] == '.')
            continue;

        items.push_back(colored_name(path, entry->d_name));
    }

    closedir(dir);

    std::sort(items.begin(), items.end(),
              [](const std::string& a, const std::string& b) {
                  return a < b;
              });

    print_two_columns(items);
    return 0;
}
