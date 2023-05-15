#include <vector>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include "network/network.cpp"
#include "./vector-operations/vector-operations.hpp"

void printVector(std::vector<double> vec);
void printVector(std::vector<int> vec);

int main() {
    /*
        std::vector<double> b {10,10,10,1};
        double c = dot_product(a,b);
        std::cout << c << "\n";
        Neuron neuron = Neuron(a,-134);
        std::cout << neuron.predict(b) << "\n";
    */
    srand(time(0));
    SingleLayerNeuralNetwork nn = SingleLayerNeuralNetwork(3*3, 5, 0.05); 
    std::vector<double> input {1,1,1,0,1,0,0,1,0};
    std::vector<double> expected {0,0,0,0,1};
    int i = 0;
    while(true) {
	i++;
        std::vector<double> output = nn.predictWithTraining(input, expected); 
	std::cout << "ITERATION " << i  << "\n";
        nn.printWeights();	
	std::cout << "Input to Neural Network: ";
        printVector(input);  
        std::cout << "Expected output: ";
        printVector(expected); 
        std::cout << "Actual output: ";	
        printVector(output);    
    }

}
