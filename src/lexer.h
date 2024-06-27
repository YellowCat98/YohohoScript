#pragma once
#include "includes.h"

class Lexer {
public:
    Lexer(const std::string& sourceCode);
    std::vector<std::string> tokenize();
private:
    std::string sourceCode;
};