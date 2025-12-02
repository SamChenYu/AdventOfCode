#include <functional>
#include <iostream>

#include "solutions/Day1.h"
#include "solutions/Day2.h"

int main() {
    std::vector<std::function<void()>> functions{
        []() { day1(); },
        []() { day2(); }
    };


    // for (size_t i = 0; i < functions.size(); ++i) {
    //     functions[i]();
    // }

    int run = 1;


    functions[run]();


    return 0;
}