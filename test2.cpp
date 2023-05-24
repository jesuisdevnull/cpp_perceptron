#include <vector>
#include <iostream>
#include "vector-operations/vector-operations.hpp"

int main() {
    std::vector<double> a {1,2,3,4,5};
    std::vector<double> b {5,4,3,2,1};
    std::vector<double> c = add_vector(a,b);
    printVector(c);
    return 0;
}
