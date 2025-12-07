#pragma once

#include <algorithm>

#include "ImportFile.h"

// Part 2
static void day6() {

    auto text = import_file("../solutions/Day6.txt");

    std::string operators = text[text.size()-1];
    // Remove the operators from the array
    text.erase(text.end());
    // This time I will have to go through each index of every single string at the same time

    // Calculate the longest string line
    std::vector<std::string> temp_copy = text;
    std::sort(temp_copy.begin(), temp_copy.end(), [](const std::string& a, const std::string& b) {
        return a.size() > b.size();
    });
    size_t n = temp_copy[0].size();



    std::vector<std::string> transformed_input{n}; // Organize by column instead of horizontal
    int column_ptr{-1};

    std::vector<char> transformed_operators{};

    for (int char_ptr = 0; char_ptr < n; char_ptr++) { // Iterate through the std::string


        if ((operators.size() > char_ptr && (operators.at(char_ptr) == '+' || operators.at(char_ptr) == '*'))) {
            // Operator present
            transformed_operators.push_back(operators.at(char_ptr));
            column_ptr++;

        }
        // Consume the column of text into the corresponding index
        for (int text_ptr = 0; text_ptr < text.size(); text_ptr++) {
            if (text[text_ptr].size() > char_ptr) {
                transformed_input[char_ptr] = transformed_input[char_ptr] + text[text_ptr].at(char_ptr);
            }
        }


    }

    column_ptr = 0;
    int operator_ptr{0};
    std::vector<unsigned long long> temp{};
    // Init temp to 0 or 1 based on if it is a + or * operator
    for (int i = 0; i < transformed_operators.size(); i++) {
        if (transformed_operators[i] == '*') {
            temp.push_back(1);
        } else {
            temp.push_back(0);
        }
    }


    for (int i = 0; i < transformed_input.size(); i++) {

        std::string t_input = transformed_input[i];

        if (std::all_of(t_input.begin(), t_input.end(), ::isspace)) {
            column_ptr++;
            operator_ptr++;
            continue;
        }
        unsigned long long casted_input = std::stoull(t_input);

        if (transformed_operators[operator_ptr] == '*') {
            temp[column_ptr] = temp[column_ptr] * casted_input;
        } else {
            temp[column_ptr] = temp[column_ptr] + casted_input;
        }
    }

    unsigned long long answer{0};
    for (auto m : temp) {
        answer += m;
    }

    std:: cout << "Answer: " << answer << std::endl;
}



// Part 1
static void day6_part1() {

    auto text = import_file("../solutions/Day6Test.txt");

    std::vector<std::string> operators{};
    // Parse the operators
    std::string operators_str = text[text.size()-1];
    for (int i=0; i<operators_str.size(); i++) {
        std::string temp{operators_str[i]};
        if (!(temp == " ")) {
            operators.push_back(temp);
        }
    }

    // Remove the operators from the array
    text.erase(text.end());


    // Iterate over the ints

    std::vector<unsigned long long> mem{};
    bool first_iteration{true};
     for (int i=0; i<text.size(); i++) { // Iterate over the whole vector<std::string>

         std::string line = text[i];
         std::string temp_str{}; // Append to this string to find out the next number
         bool started_parsing{false};
         int column_ptr{0};

         for (int j=0; j<line.size(); j++) { // Iterate over the std::string

             std::string c{line[j]};

             if (c != " ") {
                 started_parsing = true;
                 temp_str += c;
             }

             if (started_parsing && c == " " || j == line.size()-1 ) { // The j condition is because nums only get added once you see " " after an num - which means the last number might not be parsed
                 // Reached the end of the numbers - parse
                 if (first_iteration) {
                     mem.push_back(std::stoull(temp_str));
                     temp_str="";
                     started_parsing = false;
                 } else {
                     // Apply the operations
                     unsigned long long temp = std::stoull(temp_str);
                     if (operators[column_ptr] == "+") {
                         //std:: cout << temp << " " << mem[column_ptr] << " " << " added" << std::endl;
                         mem[column_ptr] = mem[column_ptr] + temp;
                     } else if (operators[column_ptr] == "*") {
                         //std:: cout << temp << " " << mem[column_ptr] << " " << " multiplied " << std::endl;
                         mem[column_ptr] = mem[column_ptr] * temp;
                     }
                     column_ptr++;
                     temp_str = "";
                     started_parsing = false;
                 }
             }

         }
         first_iteration = false;
     }
     unsigned long long answer{0};
     for (auto m : mem) {
         answer += m;
         //std:: cout << m << std::endl;
     }
     std::cout << "Answer: " << answer << std::endl;



}