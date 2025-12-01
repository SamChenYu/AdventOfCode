#pragma once
#include <fstream>
#include <mutex>
#include <string>
#include <vector>

static std::vector<std::string> import_file(const std::string &filename);

// Doubly linkedlist implementation
class Node {
public:
    Node() : m_Value(0), m_Counter{nullptr}, m_Left(nullptr), m_Right(nullptr) { }

    void set(int value) { m_Value = value; }

    void set_left(Node* left) { m_Left = left; }

    void set_right(Node* right) { m_Right = right; }

    void set_counter(int* counter) { m_Counter = counter; }

    Node& operator -=(const int& count) {
        Node* result = this;
        for (int i=0; i<count; i++) {
            if (result->get() == 0) (*m_Counter)++;
            result = result->get_left();
        }
        return *result;
    }

    Node& operator +=(const int& count) {
        Node* result = this;
        for (int i=0; i<count; i++) {
            if (result->get() == 0) (*m_Counter)++;
            result = result->get_right();
        }
        return *result;
    }

    [[nodiscard]]
    int get() const { return m_Value; }

    [[nodiscard]]
    Node* get_left() const { return m_Left; }

    [[nodiscard]]
    Node* get_right() const { return m_Right; }


private:
    int m_Value;
    int* m_Counter;
    Node* m_Left; // Descending
    Node* m_Right; // Ascending
};


// Solution!

static void day1() {

    int counter = 0;

    // Init the Lock
    std::array<Node, 100> nodes{};
    for (int i=1; i<99; i++) {
        nodes[i].set(i);
        nodes[i].set_counter(&counter);
        nodes[i].set_left(&nodes[i-1]);
        nodes[i].set_right(&nodes[i+1]);
    }
    nodes[0].set(0);              nodes[0].set_counter(&counter);
    nodes[0].set_left(&nodes[99]);      nodes[0].set_right(&nodes[1]);

    nodes[99].set(99);            nodes[99].set_counter(&counter);
    nodes[99].set_left(&nodes[98]);     nodes[99].set_right(&nodes[0]);


    // Start Solution
    Node* temp_node = &nodes[50];
    std::vector<std::string> text = import_file( "../Solutions/Day1.txt");

    for (auto line : text) {

        // Parse the line
        bool isDirectionLeft{};
        std::string magnitudeStr{};
        int magnitude{};
        isDirectionLeft = (line.at(0) == 'L') ? true : false;
        for (int i=1; i<line.length(); i++) {
            if (std::isdigit(line[i])) {
                magnitudeStr += line[i];
            }
        }
        magnitude = std::stoi(magnitudeStr);


        // Apply the L / R rotations!
        if (isDirectionLeft) {
            temp_node = &((*temp_node)-=magnitude); // POINTER HELL!!!!
        } else {
            temp_node = &((*temp_node)+=magnitude); // POINTER HELL!!!!
        }
        std::cout << temp_node->get() << std::endl;
    }
    std::cout << "Total: " << counter << std::endl;

}















// Old solution -> couldn't be bothered with lock underflow or overflow bugs

class LockInt {

public:
    explicit LockInt() : m_Value{50}, m_CounterRef{0} {}

    LockInt& operator-=(const int& other) {

        m_Value -= other;
        bool incrementCounter{true};
        if (m_Value == 0) {
            incrementCounter = false;
        }

        if (m_Value > other) {
            return *this;
        }

        while (m_Value < 0) {
            std::cout << " Incremented! ";
            m_Value += 100;
            if (incrementCounter) {m_CounterRef++;} else {incrementCounter = true;}
        }

        return *this;
    }

    LockInt& operator+=(const int& other) {
        m_Value += other;
        bool incrementCounter{true};

        if (m_Value == 99) {
            incrementCounter = false;
        }

        if (m_Value < other) {
            return *this;
        }

        while (m_Value > 99) {
            std::cout << " Incremented! ";

            m_Value -= 100;
            if (incrementCounter) {m_CounterRef++;} else {incrementCounter = true;}
        }
        return *this;
    }

    [[nodiscard]]
    int answer() const {
        return m_CounterRef;
    }

    [[nodiscard]]
    int get() const {
        return m_Value;
    }

private:
    int m_CounterRef;
    int m_Value;
};



 static void day1_old() {
      // Number of times the dial is left pointing at 0 after any rotation in the sequence
      // The dial starts at 50
      std::vector<std::string> text = import_file("../Solutions/Day1Test.txt");

      LockInt lock{};

      for (auto line : text) {
          // Parse the line
          bool isDirectionLeft{};
          std::string magnitudeStr{};
          int magnitude{};

          isDirectionLeft = (line.at(0) == 'L') ? true : false;
          for (int i=1; i<line.length(); i++) {
              if (line[i]) {
                  magnitudeStr += line[i];
              }
          }
          magnitude = std::stoi(magnitudeStr);

          std:: cout << lock.get() << " " << magnitude;
          if (isDirectionLeft) {
              lock-=magnitude;
          } else {
              lock+=magnitude;
          }
          std::cout << lock.get() << std::endl;
      }

     std:: cout << "Answer " << lock.answer() << std::endl;
}










static std::vector<std::string> import_file(const std::string &filename) {
    std::vector<std::string> text{};
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Error opening file.txt\n";
        return text;
    }

    std::string str{};
    while (std::getline(file, str)) {
        text.push_back(str);
    }
    file.close();
    return text;
}