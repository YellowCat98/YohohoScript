#include "lexer.h"

std::vector<std::string> split(const std::string& str) {
    std::vector<std::string> tokens;
    std::string token;
    bool inQuotes = false;
    std::string currentToken;
    for (char ch : str) {
        if (ch == '"') {
            inQuotes = !inQuotes;
            if (!inQuotes) {
                currentToken += ch;
                tokens.push_back(currentToken);
                currentToken.clear();
            } else {
                if (!currentToken.empty()) {
                    std::istringstream iss(currentToken);
                    while (iss >> token) {
                        tokens.push_back(token);
                    }
                }
                currentToken = ch;
            }
        } else if (inQuotes) {
            currentToken += ch;
        } else if (isspace(ch)) {
            if (!currentToken.empty()) {
                tokens.push_back(currentToken);
                currentToken.clear();
            }
        } else {
            currentToken += ch;
        }
    }
    if (!currentToken.empty()) {
        tokens.push_back(currentToken);
    }
    return tokens;
}

Lexer::Lexer(const std::string& sourceCode) : sourceCode(sourceCode) {}

std::vector<std::string> Lexer::tokenize() {
    std::vector<std::string> tokens = {};
    std::vector<std::string> sourceCode = split(this->sourceCode);
    std::regex AZ("^[A-Za-z]+$");
    std::regex zeronine("[0-9]+");
    std::regex operators("[=]");
    for (const std::string& word : sourceCode) {
        if (word.empty()) {
            continue;
        }
        if (word.front() == '"' && word.back() == '"') {
            tokens.emplace_back("[STRING]");
            tokens.emplace_back(word.substr(1, word.size() - 2));
        } else if (word == "[PRINT]" || word == "[ADD]" || word == "[HALT]" || word == "[AWAIT]" || word == "[VAR]" || word == "[INPUT]") {
            tokens.emplace_back(word);
        } else if (std::regex_match(word, zeronine)) {
            tokens.emplace_back("[INTEGER]");
            tokens.emplace_back(word);
        } else if (std::regex_match(word, operators)) {
            tokens.emplace_back("[OPERATOR]");
            tokens.emplace_back(word);
        } else if (std::regex_match(word, AZ)) {
            tokens.emplace_back("[IDENTIFIER]");
            tokens.emplace_back(word);
        } else {
            tokens.emplace_back("[UNKNOWN]");
            tokens.emplace_back(word);
        }
    }
    return tokens;
}