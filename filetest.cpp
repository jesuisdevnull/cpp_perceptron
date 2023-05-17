#include "utils/utils.hpp"
#include <iostream>
#include <vector>
#include "vector-operations/vector-operations.hpp"

int main() {
    std::vector<std::vector<double>> vec = read_file("bit-arrays/a.txt"); 
    for(auto v : vec) {
        printVector(v);    
    }
    return 1;
}
