#pragma once

#include <algorithm>





static void day5() {

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
        if (str.empty()) {
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

    // Couldn't use a map because there are overlapping lower ranges
    std::vector<std::pair<unsigned long long , unsigned long long >> ranges{};

    // Populate the map with    lower => higher
    for (const auto& range : fresh) {

        auto dash_split = split(range, '-');

        unsigned long long first = std::stoull(dash_split[0]);
        unsigned long long second = std::stoull(dash_split[1]);

        ranges.emplace_back(first, second);
    }



    // Part 1
    // Go through each input line
    //int answer{0};
    // for (const auto& line : input) {
    //     unsigned long long num = std::stoull(line);
    //     // Check if it sits within the range bounds
    //     for (const auto& pair : ranges) {
    //         if (num >= pair.first && num <= pair.second) {
    //             answer++;
    //             break;
    //         }
    //     }
    // }


    // Part 2
    /*
        3-5         += 3
        10-14       += 5
        12-18       += 4
        16-20       += 2
                    == 14
    */
    /*
        3-5         += 3
        10-14       += 5
        12-27       += 13
        16-20       // needs to be skipped!
        18-21       // needs to be skipped!
                    == 21
    */
    // Calculate the total number of 'fresh' IDs
    // Be careful of overlapping ranges!
    std::sort(ranges.begin(), ranges.end(), [](auto& left, auto& right) {
        return left.first < right.first;
    });

    unsigned long long answer{0};

    unsigned long long largest_upper{0};


    for (int i = 0; i < ranges.size(); i++) {


        if (largest_upper > ranges[i].second) {
            continue; // the whole range has already been consumed
        }

        if (largest_upper > ranges[i].first) {

            // prev upper range is bigger than the first num
            // two cases: bigger than the current second (already covered above)
            //            smaller than the current second

            unsigned long long temp = ranges[i].second - largest_upper  ;
            answer += temp;
            largest_upper = ranges[i].second;
            continue;
        }

        // No overlapping
        unsigned long long temp = ranges[i].second - ranges[i].first + 1;
        largest_upper = std::max(largest_upper, ranges[i].second);
        answer += temp;
    }




    std:: cout << "Answer: " << answer << std::endl;
}