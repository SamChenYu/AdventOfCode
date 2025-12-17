#include <functional>
#include <iostream>
#include <chrono>

#include "solutions/Day1.h"
#include "solutions/Day2.h"
#include "solutions/Day3.h"
#include "solutions/Day4.h"
#include "solutions/Day5.h"
#include "solutions/Day6.h"
#include "solutions/Day7.h"
#include "solutions/Day8.h"
#include "solutions/Day9.h"
#include "solutions/Day10.h"
#include "solutions/Day11.h"
#include "solutions/Day12.h"



void profile(std::function<void()> function) {
    auto begin = std::chrono::high_resolution_clock::now();
    function();
    auto end = std::chrono::high_resolution_clock::now();

    auto duration_micro = std::chrono::duration_cast<std::chrono::microseconds>(end - begin);
    auto duration_ms = std::chrono::duration_cast<std::chrono::milliseconds>(duration_micro);
    std::cout << "Function took " <<  duration_micro.count() << " us" << " / " << duration_ms.count() << " ms" << std::endl;

}


int main() {
    std::vector<std::function<void()>> functions{
        []() { day1(); },
        []() { day2(); },
        []() { day3(); },
        []() { day4(); },
        []() { day5(); },
        []() { day6(); },
        []() { day7(); },
        []() { day8(); },
        []() { day9(); },
        []() { day10(); },
        []() { day11(); },
        []() { day12(); },

    };


    // for (size_t i = 0; i < functions.size(); ++i) {
    //     std::cout << "=====================" << std::endl;
    //     std:: cout << "Day " << (i+1) << std::endl;
    //     profile(functions[i]);
    // }

    int i{8};
    std::cout << "=====================" << std::endl;
    std:: cout << "Day " << (i+1) << std::endl;
    profile(functions[i]);


    return 0;
}