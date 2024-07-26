#pragma once
#include "includes.h"

namespace utils {
    void setColor(int color);
    unsigned int getTerminalWidth();
    void centerText(const std::string& text);
    int searchVector(const std::vector<std::string>& vec, const std::string& item);
}