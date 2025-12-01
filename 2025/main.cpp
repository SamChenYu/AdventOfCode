#include <functional>
#include <iostream>
#include "solutions/Day1.h"


int main() {
    std::vector<std::function<void()>> functions{
        []() {day1();}
    };


    for (size_t i = 0; i < functions.size(); ++i) {
        functions[i]();
    }




    return 0;
}