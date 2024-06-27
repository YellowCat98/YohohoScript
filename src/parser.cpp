#include "parser.h"
bool isNumber(const std::string& str) {
      return !str.empty() && std::all_of(str.begin(), str.end(), ::isdigit);
}
Parser::Parser(const std::vector<std::string>& tokens)
    : tokens(tokens), token_index(0) {} // Initialize tokens and token_index

void Parser::parse() {
    while (token_index < tokens.size() - 1) {
        std::string tokenType = tokens[token_index];
        std::string tokenValue = tokens[token_index + 1];
        if (tokenType == "[PRINT]") {
            if (tokenValue != "[STRING]") {
                throw std::invalid_argument("No string defined for PRINT statement. exiting...");
            }
            std::cout << tokens[token_index + 2] << std::endl;
        } else if (tokenType == "[ADD]") {
            std::cout << tokens[token_index + 3] + tokens[token_index + 5] << std::endl;
        } else if (tokenType == "[HALT]") {
            exit(0);
        } else if (tokenType == "[UNKNOWN]") {
            throw std::invalid_argument("Unknown Identifier: " + tokenValue);
        } else if (tokenType == "[END_LINE]") {
            std::cout << "\nend line found. continuing execution.";
        } else if (tokenType == "[AWAIT]") {
            int duration = std::stoi(tokens[token_index + 2]);
            std::this_thread::sleep_for(std::chrono::seconds(duration));
        }
        token_index += 2;
    }
}