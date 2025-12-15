cmake_minimum_required(VERSION 4.0)
project(AdventOfCode)

set(CMAKE_CXX_STANDARD 23)

add_executable(AdventOfCode main.cpp
        solutions/ImportFile.h
        solutions/Day1.h
        solutions/Day2.h
        solutions/Day3.h
        solutions/Day4.h
        solutions/Day5.h
        solutions/Day6.h
        solutions/Day7.h
        solutions/Day8.h
        solutions/Day9.h
        solutions/Day10.h
        solutions/Day11.h
        solutions/Day12.h)
