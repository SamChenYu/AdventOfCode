#pragma once

#include "ImportFile.h"

// Part 2 forward declaration
static void check_recursive(const std::vector<std::string>& text, int& answer, int i, int j, int depth);


static void day7() {

    //int answer{0}; // Part 1
    int answer{1};
    auto text = import_file("../solutions/Day7.txt");
    std::pair<int, int> entry_point{};

    for (int i=0; i<text.size()-1; i++) {
        // The tachyon split never goes into another tacyhon, just place it directly below
        std::string line = text[i];

        for (int j=0; j<line.size(); j++) {
            if (line[j] == 'S' || line[j] == '|') {
                // Place the tachyon below

                if (line[j] == 'S') {
                    entry_point.first = i+1;
                    entry_point.second = j;
                }

                std::string& line_below = text[i+1];
                if (line_below.at(j) == '^') {
                    answer++; // Part 1
                    std::string& second_line_below = text[i+2];
                    line_below[j-1] = '|';
                    line_below[j+1] = '|';
                    second_line_below[j-1] = '|';
                    second_line_below[j+1] = '|';
                } else {
                    line_below[j] = '|';
                }
            }

        }

    }


    std::cout << "Tachyons Split: " << answer << std::endl;


    answer = 1;
    check_recursive(text, answer, entry_point.first, entry_point.second, 1);
    std::cout << "Different paths: " << answer << std::endl;
}

static void check_recursive(const std::vector<std::string>& text, int& answer, int i, int j, int depth) {
    //std::cout << "Depth :" << depth << std::endl;
    if (i >= text.size()-1) return;

    // Check if there is a split below first
    if (text[i+1].at(j) == '^') {

        check_recursive(text, answer, i+1, j-1, depth+1);
        answer++;
        check_recursive(text, answer, i+1, j+1, depth+1);

    } else if (text[i+1].at(j) == '|') {
        check_recursive(text, answer, i+1, j, depth+1);
    }
}








