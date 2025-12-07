#pragma once

#include <vector>
#include <string>

inline std::vector<std::string> import_file(const std::string &filename) {
    std::vector<std::string> text{};
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Error opening file.txt\n";
        return text;
    }

    std::string str{};
    while (std::getline(file, str)) {
        text.push_back(str);
    }
    file.close();
    return text;
}