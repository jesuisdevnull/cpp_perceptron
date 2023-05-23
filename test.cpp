#include "./vector-operations/vector-operations.hpp"
#include "utils/utils.hpp"

#include <vector>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include "network/network.cpp"
#include <fstream>

int main(int argc, char* argv[]) {
    if (argc > 1) {
    std::vector<std::string> filenames = {"bit-arrays/a.txt","bit-arrays/e.txt","bit-arrays/i.txt","bit-arrays/o.txt","bit-arrays/u.txt"}; 
    std::vector<std::string> filenames_tr = {"testing-samples/a.txt","testing-samples/e.txt","testing-samples/i.txt","testing-samples/o.txt","testing-samples/u.txt"}; 
    std::vector<std::vector<std::vector<double>>> vec = read_training_files(filenames); 
    std::vector<std::vector<std::vector<double>>> vec_tr = read_training_files(filenames_tr); 
    srand(time(0));
    int i = 0;
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
    
    if (strcmp(argv[1], "train") == 0) {
        bool process = true;
    int j = 0;
        
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
            if(j > 10) {
                process = false;
            }
    	    bool result = nn.saveKnowledge("base.txt");
    	    if (result) { 
	        std::cout << "Saved knowledge!"  << "\n";
    	    } else {
	        std::cout << "Couldn't save knowledge"  << "\n";
    	    }
    	}
    } else if (strcmp(argv[1],"test")==0) {
	
   	for(auto labeledV : vec_tr) {
	    std::cout << "\nSample " << i+1  << "\n";
	    std::cout << "Expected output" << "\n";
	    printVector(labeledV.at(1));
	    std::cout << "Actual output" << "\n";
	    printVector(nn.predict(labeledV.at(0)));
	    i++;	    
	} 
    }
    
    delete(nnp);
    return 0;
    } else{
        return 1;
    }
}
