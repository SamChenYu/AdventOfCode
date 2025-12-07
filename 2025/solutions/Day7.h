#pragma once

#include "ImportFile.h"
#include <unordered_map>

static void day7() {

    unsigned long long answer{1};
    auto text = import_file("../solutions/Day7.txt");
    std::pair<int, int> entry_point{};

    for (int i=0; i<text.size()-1; i++) {
        // The tachyon split never goes into another tachyon, just place it directly below
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


    answer = 0;



    // Backtracking method

    std::vector<std::vector<unsigned long long>> map{text.size(), std::vector<unsigned long long>(text[0].size(), 0)};
    // Init the last table
    std::string& last_line = text.back();

    for (int i=0; i<last_line.size(); i++ ) {
        if (last_line.at(i) == '|') {
            map[text.size()-1][i] = 1;
        }
    }




    for (int i=text.size()-2; i>=0; i--) {

        std::string& line = text[i];
        std::string& line_below = text[i+1];
        int curr_index = i;
        int below_index = i+1;


        for (int j=0; j<line.size(); j++) {
            if (line[j] == '|' && map[below_index].at(j) != 0) {
                // Two straight lines, propagate it up
                map[curr_index][j] = map[below_index].at(j);
            }

            if (line[j] == '|' && line_below[j] == '^') {
                unsigned long long  left = map[below_index].at(j-1);
                unsigned long long  right = map[below_index].at(j+1);
                unsigned long long  sum = left+right;
                map[curr_index][j] = sum;
            }
        }

    }

    unsigned long long total{map[entry_point.first][entry_point.second]};
    std::cout << "Different paths: " << total << std::endl;
}






