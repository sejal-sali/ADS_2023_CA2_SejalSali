#include "Helper.hpp"
void LOG_MESSAGE(const std::string& message) {
    std::cout << message << std::endl;
}

std::string trim(const std::string& str) {
    size_t first = str.find_first_not_of(" \t\r\n"); // Find first non-whitespace character
    size_t last = str.find_last_not_of(" \t\r\n");   // Find last non-whitespace character

    if (first == std::string::npos || last == std::string::npos)
        return ""; // Return empty string if input contains only whitespace

    return str.substr(first, last - first + 1); // Return the trimmed substring
}