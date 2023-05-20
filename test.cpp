#include <vector>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include "network/network.cpp"
#include "./vector-operations/vector-operations.hpp"
#include "utils/utils.hpp"


int main() {
    std::vector<std::string> filenames = {"bit-arrays/a.txt","bit-arrays/e.txt","bit-arrays/i.txt","bit-arrays/o.txt","bit-arrays/u.txt"}; 
    std::vector<std::vector<std::vector<double>>> vec = read_files(filenames); 
    srand(time(0));
    SingleLayerNeuralNetwork nn = SingleLayerNeuralNetwork(160, 5, 0.05); 
    bool process = true;
    int i = 0;
    int j = 0;
    nn.printWeights();
    while(process) {
        for (auto labeledV : vec) {
            i++;    
	    std::cout << "ITERATION " << i+1  << "\n";
	    //std::cout << "Size of input vector :" << labeledV.at(0).size() << "\n";
	    //std::cout << "Size of expected vector"  << labeledV.at(1).size() << "\n";
            //printVector(labeledV.at(0));
            std::vector<double> output = nn.predictWithTraining(labeledV.at(0), labeledV.at(1)); 
        }
        j++;
        if(j > 100*6) {
            process = false;
        }
    }
    nn.printWeights();
    return 1;
}
