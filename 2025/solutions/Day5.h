#pragma once

#include <unordered_map>







static void day5() {
    int answer{0};
    std::cout << "Answer: " << answer << std::endl;
}




static void day5_part1() {

    std::string filename("../solutions/Day5.txt");

    std::vector<std::string> fresh{};
    std::vector<std::string> input{};

    bool processingFresh{true};

    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Error opening file.txt\n";
        return;
    }

    std::string str{};
    while (std::getline(file, str)) {
        if (str == "") {
            processingFresh = false;
            continue;
        }
        if (processingFresh) {
            fresh.push_back(str);
        } else {
            input.push_back(str);
        }

    }
    file.close();
    
    std:: cout << std::endl;

    std::vector<std::pair<unsigned long long , unsigned long long >> map{};


    // Populate the map with    lower => higher
    for (const auto& range : fresh) {

        auto dash_split = split(range, '-');

        unsigned long long first = std::stoull(dash_split[0]);
        unsigned long long second = std::stoull(dash_split[1]);

        map.emplace_back(first, second);
    }

    int answer{0};

    // Go through each input line
    for (const auto& line : input) {
        unsigned long long num = std::stoull(line);
        // Check if it sits within the range bounds
        for (const auto& pair : map) {
            if (num >= pair.first && num <= pair.second) {
                answer++;
                break;
            }
        }
    }

    std:: cout << "Answer: " << answer << std::endl;
}