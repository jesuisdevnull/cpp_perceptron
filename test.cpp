#include "./vector-operations/vector-operations.hpp"
#include "utils/utils.hpp"

#include <vector>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include "network/network.cpp"
#include <fstream>

int main() {
    /*
    std::vector<std::string> filenames = {"bit-arrays/a.txt","bit-arrays/e.txt","bit-arrays/i.txt","bit-arrays/o.txt","bit-arrays/u.txt"}; 
    std::vector<std::vector<std::vector<double>>> vec = read_files(filenames); 
    srand(time(0));
    bool process = true;
    int i = 0;
    int j = 0;
    */
    std::ifstream base;
     
    base.open("base.txt");
    if (base.is_open()) {
	base.close();
	std::cout << "Found knowledge base! loading..."  << "\n";
      SingleLayerNeuralNetwork nn = read_knowledge_base("base.txt");
    nn.printWeights();
    } else {
	std::cout << "Creating neural network from scratch..."  << "\n";
        SingleLayerNeuralNetwork nn = SingleLayerNeuralNetwork(160, 5, 0.05); 
    nn.printWeights();
    }
    /*
    bool result = nn.saveKnowledge("base.txt");
    if (result) { 
	std::cout << "Saved knowledge!"  << "\n";
    } else {
	std::cout << "Couldn't save knowledge"  << "\n";
    }
    
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
    */
    return 1;
}
