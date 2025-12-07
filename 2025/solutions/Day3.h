#pragma once

#include <iostream>
#include <ostream>
#include <string>
#include <vector>
#include "ImportFile.h"


static unsigned long long  get_biggest_joltage_part1(std::string input) {

    int firstNum{-1};
    int firstIndex{-1};

    int secondNum{-1};

    for (int i=0; i<input.length()-1; i++) {
        // Find the largest num that is NOT the last num
        int num = std::stoi(std::string(1, input[i]));
        firstIndex = num > firstNum ? i : firstIndex;
        firstNum = num > firstNum ? num : firstNum;

    }

    for (int i=firstIndex+1; i<input.length(); i++ ) {
        int num = std::stoi(std::string(1, input[i]));
        secondNum = num > secondNum ? num : secondNum;
    }

    std::string str_num = std::to_string(firstNum) + std::to_string(secondNum);



    return std::stoull(str_num);
}


static unsigned long long  get_biggest_joltage_part2(const std::string &input) {

    // For your nth number, you need to make sure there is at least 12-n numbers left
    // For example input:   811111111111119 (length = 15)
    // For the first int, you need to make sure that there are at least 11 int on the right
    // Therefore your selection is in the first 4 ints
    std::string str_num{};

    int previousPtr{-1};

    for (int i=1; i<13; i++) { // Loop through so I know which index of the string

        // Calculate the selection window
        int start{previousPtr+1};
        int end{(int) input.length() - (12-i)};

        int temp{-1};
        for (int j=start; j<end; j++) {
            int num = std::stoi(std::string(1, input[j]));
            previousPtr = num > temp ? j : previousPtr;
            temp = num > temp ? num : temp;
        }

        str_num += std::to_string(temp);
    }

    return std::stoull(str_num);
}

static void day3() {
    std::vector<std::string> text = import_file("../solutions/Day3.txt");

    unsigned long long  total_joltage{0};

    for (auto line: text) {
        //total_joltage += get_biggest_joltage_part1(line);
        total_joltage += get_biggest_joltage_part2(line);
    }

    // std:: cout << get_biggest_joltage_part2("234234234234278") << std::endl;

    std:: cout << "Total Joltage: " << total_joltage << std::endl;
}
