#include "lexer.h"
#include "parser.h"
#include "utils.h"

std::string ifStreamToStr(std::ifstream& file) {
    std::ostringstream ss;
    ss << file.rdbuf();
    std::string string = ss.str();
    return string;
}

int main(int argc, char* argv[]) {
    std::ifstream inputFile(argv[1]);
    try {
        if (!inputFile.is_open()) {
            throw std::invalid_argument(std::string("File ") + argv[1] + " Not found.\nIf the file exists, note that certain file systems are case sensitive.\nwhich means that \"Hello!\" does not equal to \"HELLO!\".");
        }

        if (inputFile.bad()) {
            throw std::invalid_argument(std::string("Unable to open file \"") + argv[1] + "\", file may be corrupt.");
        }
        Lexer lex(ifStreamToStr(inputFile));
        std::vector<std::string> token = lex.tokenize();
        Parser par(token);
        par.parse();
    } catch (const std::exception& e) {
        utils::setColor(4);
        std::cout << "Error:" << std::endl;
        utils::setColor(7);
        std::cout << e.what() << std::endl;
        return 1;
    }
}