#pragma once

#include <vector>
#include <iostream>
#include <sstream>
#include <string>

#include "FileImport.h"

std::vector<std::string> split (const std::string &s, char delim) {
     std::vector<std::string> result;
     std::stringstream ss (s);
     std::string item;

     while (getline (ss, item, delim)) {
          result.push_back (item);
     }

     return result;
}

long process_id_part_1(long start, long end) {

     /*
          Since the young Elf was just doing silly patterns, you can find the invalid IDs by looking
          for any ID which is made only of some sequence of digits repeated twice. So, 55 (5 twice),
          6464 (64 twice), and 123123 (123 twice) would all be invalid IDs.
     */

     // Just check if first half of the string == second half of the string
     long answer = 0;

     for (long i = start; i <= end; i++) {

          std::string num_str = std::to_string(i);
          // Must be divisible by 2 to be repeatable
          if (num_str.length() % 2 != 0) {
               continue;
          }

          std::string firstHalf = num_str.substr(0, num_str.length() / 2);
          std::string secondHalf = num_str.substr(num_str.length() / 2);

          if (firstHalf == secondHalf) {
               answer += i;
          }
     }
     return answer;
}

long process_id_part_2(long start, long end) {

     /*
          Now, an ID is invalid if it is made only of some sequence of digits repeated at least twice.
          So, 12341234 (1234 two times), 123123123 (123 three times), 1212121212 (12 five times), and
          1111111 (1 seven times) are all invalid IDs.
     */

     long answer = 0;
     for (long i = start; i <= end; i++) {
          // Go through the range of nums
          std::string num_str = std::to_string(i);

          for (int pattern_length = 1; pattern_length <= num_str.length() / 2; pattern_length++) {
               // GO through all possible lengths of the pattern
               bool patternMatches = true;
               std::string current_pattern = num_str.substr(0, pattern_length);


               for (int k=pattern_length; k<num_str.length(); k+=pattern_length) {
                    // Check through the remaining string to check if the pattern matches
                    std::string temp_str = num_str.substr(k, pattern_length);
                    if (temp_str.find(current_pattern) == std::string::npos) {
                         patternMatches = false;
                         break;
                    }
               }

               if (patternMatches) {
                    answer += i;
                    break;
               }

          }
     }
     return answer;
}



static void day2() {



     long answer = 0;

     std::vector<std::string> text = import_file("../solutions/Day2.txt");

     // Input is only one line
     // Split delimited by commas
     auto comma_split = split(text[0], ',');

     for (const auto& line : comma_split) {
          // Split delimited by dash
          auto dash_split = split(line, '-');
          //answer += process_id_part_1(std::stol(dash_split[0]), std::stol(dash_split[1]));
          answer += process_id_part_2(std::stol(dash_split[0]), std::stol(dash_split[1]));

     }

     std:: cout << "Answer " << answer << std::endl;



}