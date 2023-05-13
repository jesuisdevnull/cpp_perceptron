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

