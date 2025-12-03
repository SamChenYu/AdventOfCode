#include <functional>
#include <iostream>
#include <chrono>

#include "solutions/Day1.h"
#include "solutions/Day2.h"
#include "solutions/Day3.h"

void profile(std::function<void()> function) {
    auto begin = std::chrono::high_resolution_clock::now();
    function();
    auto end = std::chrono::high_resolution_clock::now();

    auto duration_micro = std::chrono::duration_cast<std::chrono::microseconds>(end - begin);
    auto duration_ms = std::chrono::duration_cast<std::chrono::milliseconds>(duration_micro);
    std::cout << "Function took " <<  duration_micro.count() << " us" << " / " << duration_ms << std::endl;

}


int main() {
    std::vector<std::function<void()>> functions{
        []() { day1(); },
        []() { day2(); },
        []() { day3(); }
    };


    for (size_t i = 0; i < functions.size(); ++i) {
        std::cout << "=====================" << std::endl;
        std:: cout << "Day " << (i+1) << std::endl;
        profile(functions[i]);
    }



    return 0;
}