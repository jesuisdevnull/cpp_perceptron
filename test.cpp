#include <vector>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include "network/network.cpp"
#include "./vector-operations/vector-operations.hpp"


int main() {
   /* std::vector<std::vector<double>> input = {{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,1,1,0,1,0,0,0,0,0,1,1,0,0,1,0,0,0,0,0,1,0,1,1,1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{0,1,0,0,0}};*/
    std::vector<std::vector<double>> input = {{1,1,1,0,1,0,0,1,0},{0,1}}; 
    srand(time(0));
    SingleLayerNeuralNetwork nn = SingleLayerNeuralNetwork(3*3, 2, 0.05); 
    int i = 0;
    while(i < 2) {
        
	std::cout << "ITERATION " << i+1  << "\n";
        std::vector<double> output = nn.predictWithTraining(input.at(0), input.at(1)); 
        i++;
    }
}
