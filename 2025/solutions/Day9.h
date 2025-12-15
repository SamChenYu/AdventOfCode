#pragma once

#include "ImportFile.h"

static signed long long mod(signed long long a) {
    if (a < 0) {
        a *= -1;
    }

    return a;
}


static void day9() {


    auto text = import_file("../solutions/Day9.txt");

    std::vector<std::pair<signed long long,signed long long> >positions{};

    for (auto line: text) {

        auto str_split = split(line, ',');

        signed long long first = std::stoull(str_split[0]);
        signed long long second = std::stoull(str_split[1]);

        positions.emplace_back(first,second);

        // std::cout << line << std::endl;
    }

    signed long long max_area{0};

    std::pair<signed long long, signed long long> first_point{0, 0};

    std::pair<signed long long, signed long long> second_point{0, 0};

    for (int i=0; i<positions.size(); i++) {
        for (int j=i+1; j<positions.size(); j++) {

            signed long long temp_area = (mod(positions[i].first - positions[j].first)+1) * (mod(positions[i].second - positions[j].second)+1);

            if (temp_area > max_area) {
                max_area = temp_area;
                first_point = positions[i];
                second_point = positions[j];
            }
        }
    }

    std::cout << "Max Area: " << max_area << std::endl;
    std::cout << first_point.first << " " << first_point.second << std::endl;
    std::cout << second_point.first << " " << second_point.second << std::endl;

}