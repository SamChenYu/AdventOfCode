#include <functional>
#include <iostream>

#include "solutions/Day1.h"
#include "solutions/Day2.h"
#include "solutions/Day3.h"


int main() {
    std::vector<std::function<void()>> functions{
        []() { day1(); },
        []() { day2(); },
        []() { day3(); }

    };


    // for (size_t i = 0; i < functions.size(); ++i) {
    //     functions[i]();
    // }

    int run = 2;


    functions[run]();


    return 0;
}