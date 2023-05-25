#include "./utils.hpp"
#include "../network/network.cpp"
#include "../neuron/neuron.cpp"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <stdexcept>
#include <algorithm>
#include <random>

std::vector<std::vector<std::vector<double>>> read_training_files(std::vector<std::string> filepaths) { 
    std::ifstream myfile;
    std::vector<std::vector<std::vector<double>>> result;
    for(auto filepath : filepaths) {       
        myfile.open(filepath);
        if (myfile.is_open()) {
            std::cout << "File is open!" << "\n";
            double num;
            std::vector<double> expectedOutput;
        
            std::string line;
            getline(myfile, line);
            std::stringstream inputStringstreamExpected(line);
            std::cout << line << "\n";
            while(inputStringstreamExpected >> num) {
                expectedOutput.push_back(num);
            }

            while (getline(myfile, line)) {
                std::vector<double> input;
                std::vector<std::vector<double>> labeledInput;
                std::stringstream inputStringstreamInput(line);
                while (inputStringstreamInput >> num) {
                    input.push_back(num);
                }
                labeledInput.push_back(input);
                labeledInput.push_back(expectedOutput);
                result.push_back(labeledInput);
            }
            myfile.close();    
        } else { 
            std::cout << "File not open." << "\n";    
        }
    }
    auto engine = std::default_random_engine{};
    std::shuffle(std::begin(result),std::end(result),engine);
    return result;    
}


SingleLayerNeuralNetwork* read_knowledge_base(std::string filepath) {
    std::ifstream myfile;
    myfile.open(filepath);
    if(myfile.is_open()) {
        std::cout << "File is open!" << "\n";
        double learningRate;
	double errorMargin;
	std::string line;
	
	getline(myfile, line);
        std::stringstream learningRateStringStream(line);
	learningRateStringStream >> learningRate;;

	getline(myfile, line);
        std::stringstream errorMarginStringStream(line);
        errorMarginStringStream >> errorMargin;

	std::vector<Neuron> neurons;
	double num;
	while (getline(myfile, line)) { 
	     double bias;
	     std::vector<double> weights;

	     std::stringstream biasStringStream(line);
             biasStringStream >> bias;
             
             getline(myfile, line);
      	     std::stringstream weightsStringStream(line);
	     while (weightsStringStream >> num) {
                 weights.push_back(num);
	     }
             Neuron neuron = Neuron(weights, bias);
             neurons.push_back(neuron);
	}
        myfile.close();
	SingleLayerNeuralNetwork* nn = new SingleLayerNeuralNetwork(neurons,learningRate, errorMargin);
	return nn;
    } else { 
        throw "Couldn't open file.";
    }
}

int find_max_index(std::vector<double> vec) {
    double max = -999999;
    int result = -1;
    int i = 0;
    for (auto num:vec) {
	if (num > max) {
            max = num;
	    result = i;
	}
	i++;
    }
    return result;
}

std::string interpret_index(int i) {
    switch(i) {
        case 0: return "a";
	case 1: return "e";
	case 2: return "i";
	case 3: return "o";
	case 4: return "u";
	default: return "No reconocido";

    }
} 
