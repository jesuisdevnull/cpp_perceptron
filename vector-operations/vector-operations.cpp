#include <vector>
#include <stdexcept>
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

std::vector<double> scale_vector(std::vector<double> vec, double scalar) {
    std::vector<double> scaledVector;
    for(double num : vec) {
        double scaled = num * scalar;
        scaledVector.push_back(scaled);    
    }
    return scaledVector;
}

std::vector<double> add_vector(std::vector<double> a, std::vector<double> b) {
    if (a.size() != b.size()) {
        throw std::invalid_argument("Vector dimensions do not match");
    }
    std::vector<double> result;
    for (double num : a) {
       result.push_back(a+b); 
    }
    return result;
}
