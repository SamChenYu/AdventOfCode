#pragma once

#include <cmath>
#include <exception>
#include <map>
#include <unordered_set>
#include <limits>

#include "ImportFile.h"


static double distance(const std::array<int, 3>& a, const std::array<int, 3>& b) {
    return sqrt((a[0]-b[0])*(a[0]-b[0]) + (a[1]-b[1])*(a[1]-b[1]) + (a[2]-b[2])*(a[2]-b[2]) );
}



static std::vector<std::pair<double, std::pair<int, int>>> get_sorted_closest_nodes( const std::vector<std::array<int, 3>>& arr) {

    std::vector<std::pair<double, std::pair<int, int>>> sorted_closest_nodes{};

    for (int i=0; i<arr.size(); i++) {
        for (int j=i+1; j<arr.size(); j++) {
            double temp_dist = distance(arr[i], arr[j]);
            auto indices_pair = std::make_pair(i, j);
            sorted_closest_nodes.emplace_back( temp_dist, indices_pair ) ;
        }
    }
    std::sort(sorted_closest_nodes.begin(), sorted_closest_nodes.end());
    return sorted_closest_nodes;
}





static void day8() {
    // IMPORT FILES AND PARSE INTO ints 2D array


    // Test
    //std::string filename = "../solutions/Day8Test.txt";     int circuits_to_count = 10;

    // Actual
     std::string filename = "../solutions/Day8.txt";     int circuits_to_count = 1000;



    const auto text = import_file(filename);
    std::vector<std::array<int, 3>> arr{};
    for (const auto & line : text) {
        auto split_line = split(line, ',');
            std::array<int, 3> temp_arr{
                std::stoi(split_line[0]), std::stoi(split_line[1]), std::stoi(split_line[2])
            };
            arr.push_back(temp_arr);
    }

    // Assert that the input size is a even number (needs to connect all pairs)
    if (text.size() % 2 != 0) {
        std::cout << "Input size is not divisible by two! Returning...";
        return;
    }

    auto connections = get_sorted_closest_nodes(arr);
    // Only keep the first circuit_to_count nodes
    connections.erase(connections.begin() + circuits_to_count, connections.end());











    // Now the map has the information of the shortest connections - now we need to find which ones are in common
    std::cout << "Processing common graphs" << std::endl;



    // for ( auto pair : connections) {
    //     std::cout << pair.second.first << " -> " << pair.second.second << std::endl;
    // }




   //Basically , go through the node and add everything that connects, then remove it from the array
    std::vector<int> unique_graph_node_count{};
    std::unordered_set<int> unique_graph_nodes{}; // Temp set that gets reset every loop




    while (!connections.empty()) {

        // Add the first element to the hashset so there is SOMETHING
        unique_graph_nodes.insert(connections[connections.size()-1].second.first);
        unique_graph_nodes.insert(connections[connections.size()-1].second.second);
        int temp_count{2};
        connections.erase(connections.end()-1);

        bool added_a_node{true};

        while (added_a_node) {
            added_a_node = false; // reset the flag
            for (int i=connections.size()-1; i>=0; i--) {

                int firstIndex = connections[i].second.first;
                int secondIndex = connections[i].second.second;

                if (unique_graph_nodes.contains(firstIndex) || unique_graph_nodes.contains(secondIndex)) {

                    if (! (unique_graph_nodes.contains(firstIndex) && unique_graph_nodes.contains(secondIndex))) {
                        temp_count++;
                        added_a_node = true;
                    }

                    unique_graph_nodes.insert(firstIndex);
                    unique_graph_nodes.insert(secondIndex);
                    connections.erase(connections.begin() + i);

                }

            }
        }



        unique_graph_node_count.push_back(temp_count);
        unique_graph_nodes.clear();
        temp_count = 0;

    }

    std::sort(unique_graph_node_count.begin(), unique_graph_node_count.end(), [](const auto&a, const auto&b) { return  a > b; });


    unsigned long long answer{1};
    for (int i=0; i<3; i++ ) {
        answer *= unique_graph_node_count[i];
    }


    std::cout << "Answer : " << answer << std::endl;
}

// 27540
// 33299000
// 7110