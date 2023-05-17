#include "utils/utils.hpp"
#include <iostream>
#include <vector>
#include "vector-operations/vector-operations.hpp"

int main() {
    std::vector<std::string> filenames = {"bit-arrays/a.txt","bit-arrays/e.txt","bit-arrays/i.txt","bit-arrays/o.txt","bit-arrays/u.txt"}; 
    std::vector<std::vector<std::vector<double>>> vec = read_files(filenames); 
    for(auto labeledV : vec) {
        //printVector(labeledV.at(0));
        printVector(labeledV.at(1));    
    }
    std::cout << "Number of training examples: " << vec.size() << "\n";
    return 1;
}
