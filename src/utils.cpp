#include "utils.h"

namespace utils {
    #if defined(_WIN32) || defined(_WIN64)
        void setColor(int color) {
            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(hConsole, color);
        }
    #endif
    unsigned int getTerminalWidth() {
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
        return csbi.dwSize.X;
    }
    void centerText(const std::string& text) {
        unsigned int terminalWidth = getTerminalWidth();
        unsigned int textLength = text.length();
        unsigned int padding = (terminalWidth - textLength) / 2;

        for (unsigned int i = 0; i < padding; ++i) {
            std::cout << " ";
        }
        std::cout << text << std::endl;
    }
}
