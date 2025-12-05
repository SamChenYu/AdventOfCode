cmake_minimum_required(VERSION 4.0)
project(AdventOfCode)

set(CMAKE_CXX_STANDARD 23)

add_executable(AdventOfCode main.cpp
        solutions/FileImport.h
        solutions/Day1.h
        solutions/Day2.h
        solutions/Day3.h
        solutions/Day4.h
        solutions/Day5.h)
