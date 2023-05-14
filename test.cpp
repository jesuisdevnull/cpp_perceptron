#include <vector>
#include <iostream>
#include "vector-operations/vector-operations.hpp"
#include "network/network.cpp"


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
    SingleLayerNeuralNetwork nn = SingleLayerNeuralNetwork(3*3, 5, 0.5);    
    std::vector<double> input {1,1,1,0,1,0,0,1,0};
    std::vector<int> output = nn.predict(input); 
    std::cout << "Input to Neural Network: ";
    printVector(input); 
    std::cout << "Output: ";
    printVector(output);    
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
