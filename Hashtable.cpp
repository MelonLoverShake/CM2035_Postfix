#include "HashTable.h"
#include <cmath>
#include <stdexcept>
#include <limits>
#include <iostream>
#include <sstream>

// Constructor: initialize the values array with NaN
HashTable::HashTable() {
    for (int i = 0; i < LETTERS_COUNT; ++i) {
        values[i] = std::numeric_limits<double>::quiet_NaN();
    }
}

// Hash function to convert a character to an index
int HashTable::hashFunc(char key) {
    return key - 'A';
}

// Function to check if the character is a valid variable (A-Z)
void HashTable::checkVariable(char key) {
    if (key < 'A' || key > 'Z') {
        throw std::runtime_error("Variables should be from A to Z");
    }
}

// Insert a value into the hash table
void HashTable::insert(char key, double value) {
    checkVariable(key);
    int index = hashFunc(key);
    values[index] = value;
}

// Search for a value in the hash table
double HashTable::search(char key) {
    checkVariable(key);
    int index = hashFunc(key);
    if (std::isnan(values[index])) {
        throw std::runtime_error("Unknown variable \"" + std::string(1, key) + "\"");
    }
    return values[index];
}

// Remove a value from the hash table
void HashTable::remove(char key) {
    checkVariable(key);
    int index = hashFunc(key);
    values[index] = std::numeric_limits<double>::quiet_NaN();
}
void HashTable::print() {
    std::ostringstream oss;
    oss << "{ ";

    bool first = true;
    for (int i = 0; i < LETTERS_COUNT; ++i) {
        if (!std::isnan(values[i])) {
            if (!first) {
                oss << ", ";
            }
            char variable = 'A' + i;
            oss << "\"" << variable << "\": " << values[i];
            first = false;
        }
    }

    if (first) {
        oss << "{}";
    }

    oss << " }";
    std::cout << oss.str() << std::endl;
}