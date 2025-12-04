#pragma once

#include "FileImport.h"





static int get_adjacent_num(std::vector<bool>& grid, int row_size,
        std::array<int, 3>& left, std::array<int, 3>& right, std::array<int, 2>& middle) {


    int count{0};

    for (int i=0; i<grid.size(); i++) {

        if (!grid[i]) {
            continue;
        }

        int tempCount{0};


        for (int j=0; j<middle.size(); j++) {
            int tempIndex = (i + middle[j]);
            if (tempIndex > 0 and tempIndex < grid.size()) {
                if (grid[tempIndex]) {
                    tempCount++;
                }
            }
        }

        if (i % row_size != 0) { // has the left
            for (int j=0; j<left.size(); j++) {
                int tempIndex = (i + left[j]);
                if (tempIndex > 0 and tempIndex < grid.size()) {
                    if (grid[tempIndex]) {
                        tempCount++;
                    }
                }
            }
        }

        if  (i % row_size != row_size - 1) { // has the right
            for (int j=0; j<right.size(); j++) {
                int tempIndex = (i + right[j]);
                if (tempIndex > 0 and tempIndex < grid.size()) {
                    if (grid[tempIndex]) {
                        tempCount++;
                    }
                }
            }
        }


        if (tempCount < 4) {
            count++;
            grid[i] = false; // PART 2
        }
    }

    return count;
}

static void day4() {

    /*
        The forklifts can only access a roll of paper if there are fewer than four rolls of paper
        in the 8 adjacent positions

                X X X
                X o X
                X X X

            (x-1, y-1) (x, y-1) (x+1, y-1)
            (x-1, y)   (x)      (x+1, y)
            (x-1, y+1) (x, y+1) (x+1, y+1)
     */

    std::vector<std::string> text = import_file("../solutions/Day4.txt");

    const size_t row_size = text[0].size();

    std::vector<bool> grid{};
    grid.reserve(text.size() * (row_size*2));

    for (int i=0; i<text.size(); i++) {
        for (int j=0; j<row_size; j++) {
            grid.push_back((text[i].at(j) == '@'));
        }

    }

    std::array<int, 3> left{{
        -(int)row_size - 1,         // Top left
        -1,                         // Left
        (int)row_size - 1,          // Bottom left
    }};

    std::array<int, 3> right{{
        -(int)row_size + 1,         // Top right
        1,                          // Right
        (int) row_size + 1           // Bottom right
    }};


    std::array<int, 2> middle{{
        -(int)row_size,            // Top
        (int) row_size,             // Bottom
    }};

    int answer = 0;
    // answer += get_adjacent_num(grid, row_size, left, right, middle); // Part 1
    int removed = -1;

    while (removed != 0 ) {
        removed = get_adjacent_num(grid, (int) row_size, left, right, middle);
        answer += removed;
    }


    std::cout << "Answer: " << answer << std::endl;
}

