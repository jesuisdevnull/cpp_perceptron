#include <vector>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include "network/network.cpp"
#include "./vector-operations/vector-operations.hpp"

void printVector(std::vector<double> vec);
void printVector(std::vector<int> vec);

int main() {
    srand(time(0));
    SingleLayerNeuralNetwork nn = SingleLayerNeuralNetwork(3*3, 5, 1); 
    std::vector<double> input {1,1,1,0,1,0,0,1,0};
    std::vector<double> expected {0,0,0,0,1};
    int i = 0;
    while(i < 1000) {
    
        std::vector<double> output = nn.predictWithTraining(input, expected); 
	std::cout << "ITERATION " << i+1  << "\n";
        i++;
    }

}
