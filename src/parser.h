#pragma once
#include "includes.h"


class Parser {
public:
    Parser(const std::vector<std::string>& tokens);
    void parse();
private:
    std::map<std::string, std::any> variables;
    std::vector<std::string> tokens;
    int token_index;
};