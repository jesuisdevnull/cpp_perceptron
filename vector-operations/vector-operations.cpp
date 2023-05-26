#include <vector>
#include <stdexcept>
#include <iostream>
#include "vector-operations.hpp"

double dot_product(std::vector<double> a, std::vector<double> b) {
    if (a.size() != b.size()) {
        throw std::invalid_argument("Vector dimensions do not match");
    }
    double result = 0;
    for (int i = 0; i < a.size(); i++) {
        result += a.at(i) * b.at(i);
    }
    return result;
}

std::vector<double> add_vector(std::vector<double> a, std::vector<double> b) {
    if (a.size() != b.size()) {
        throw std::invalid_argument("Vector dimensions do not match");
    }
    std::vector<double> result;
    int i = 0;
    for (double num : a) {
       result.push_back(num + b.at(i));
       i++;
    }
    return result;
}


void printVector(std::vector<int> vec) {
    std::cout << "[ ";
    for (int num : vec) {
        std::cout << num << " ";    
    }
    std::cout << "]\n";
}

void printVector(std::vector<double> vec) {
    std::cout << "[ ";
    for (double num : vec) {
        std::cout << num << " ";    
    }
    std::cout << "]\n";
}
