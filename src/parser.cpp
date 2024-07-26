#include "parser.h"
bool isNumber(const std::string& str) {
      return !str.empty() && std::all_of(str.begin(), str.end(), ::isdigit);
}
Parser::Parser(const std::vector<std::string>& tokens)
    : tokens(tokens), token_index(0) {} // Initialize tokens and token_index

void Parser::parse() {
    while (token_index < tokens.size()) {
        std::string tokenType = tokens[token_index];
        
        if (tokenType == "[PRINT]") {
            if (tokens[token_index + 1] != "[STRING]" && tokens[token_index + 1] != "[IDENTIFIER]" && tokens[token_index + 1] != "[INTEGER]") {
                throw std::invalid_argument("No string defined for PRINT statement. exiting...");
            }
            if (tokens[token_index + 1] == "[STRING]" && tokens[token_index + 1] == "[INTEGER]") {
                std::cout << tokens[token_index + 2] << std::endl;
                
            }

            if (tokens[token_index + 1] == "[IDENTIFIER]") {
                int varToken_index = utils::searchVector(variables, tokens[token_index + 2]);

                std::cout << variables[varToken_index + 1];
            }
            token_index += 3; // Move past [PRINT] [STRING] "value"
        } else if (tokenType == "[ADD]") {
            // Assuming ADD takes two integers
            if (tokens[token_index + 1] != "[INTEGER]" || tokens[token_index + 3] != "[INTEGER]") {
                throw std::invalid_argument("Invalid integers for ADD statement. exiting...");
            }
            int result = std::stoi(tokens[token_index + 2]) + std::stoi(tokens[token_index + 4]);
            std::cout << result << std::endl;
            token_index += 5; // Move past [ADD] [INTEGER] value [INTEGER] value
        } else if (tokenType == "[HALT]") {
            exit(0);
        } else if (tokenType == "[UNKNOWN]") {
            throw std::invalid_argument("Unknown Identifier: " + tokens[token_index + 1]);
        } else if (tokenType == "[AWAIT]") {
            int duration = std::stoi(tokens[token_index + 2]);
            std::this_thread::sleep_for(std::chrono::seconds(duration));
            token_index += 3; // Move past [AWAIT] [INTEGER] value
        } else if (tokenType == "[INPUT]") {
            std::string value;
            std::cout << tokens[token_index + 2];
            std::cin >> value;
            token_index += 3; // move past [INPUT] [STRING] value
        } else if (tokenType == "[VAR]") {
            variables.push_back(tokens[token_index + 5]);
            variables.push_back(tokens[token_index + 2]);
            variables.push_back(tokens[token_index + 6]);

            token_index += 7; // move past [VAR] [IDENTIFIER] value [OPERATOR] = [TYPE] value2
        } else {
            throw std::invalid_argument("Unexpected token: " + tokenType);
        }
    }
}
