#include "./vector-operations/vector-operations.hpp"
#include "utils/utils.hpp"

#include <vector>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include "network/network.cpp"
#include <fstream>

int main() {
    
    std::vector<std::string> filenames = {"bit-arrays/a.txt","bit-arrays/e.txt","bit-arrays/i.txt","bit-arrays/o.txt","bit-arrays/u.txt"}; 
    std::vector<std::vector<std::vector<double>>> vec = read_training_files(filenames); 
    srand(time(0));
    bool process = true;
    int i = 0;
    int j = 0;
    std::ifstream base;
    SingleLayerNeuralNetwork* nnp; 
    base.open("base.txt");
    if (base.is_open()) {
	base.close();
	std::cout << "Found knowledge base! loading..."  << "\n";
    nnp = read_knowledge_base("base.txt");
    } else {
	std::cout << "Creating neural network from scratch..."  << "\n";
        nnp = new SingleLayerNeuralNetwork(160, 5, 0.05); 
    }
    SingleLayerNeuralNetwork nn = *nnp; 
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
        if(j > 100) {
            process = false;
        }
    	bool result = nn.saveKnowledge("base.txt");
    	if (result) { 
		std::cout << "Saved knowledge!"  << "\n";
    	} else {
		std::cout << "Couldn't save knowledge"  << "\n";
    	}
    }
    
    delete(nnp);
    return 1;
}
