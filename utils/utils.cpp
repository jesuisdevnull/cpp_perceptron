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
            double num;
            std::vector<double> expectedOutput;
        
            std::string line;
            getline(myfile, line);
            std::stringstream inputStringstreamExpected(line);

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
            throw std::runtime_error("Could not open training examples file."); 
        }
    }
    auto engine = std::default_random_engine{};
    std::shuffle(std::begin(result),std::end(result),engine);
    return result;    
}

std::vector<std::vector<std::vector<double>>> read_testing_files(std::vector<std::string> filepaths) { 
    std::ifstream myfile;
    std::vector<std::vector<std::vector<double>>> result;
    for(auto filepath : filepaths) {       
        myfile.open(filepath);
        if (myfile.is_open()) {
            double num;
            std::vector<double> expectedOutput;
        
            std::string line;
            getline(myfile, line);
            std::stringstream inputStringstreamExpected(line);

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
            throw std::runtime_error("Could not open file containing test samples."); 
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
        throw std::runtime_error("Could not open knowledge base file."); 
    }
}

std::vector<double> read_individual_letter(std::string filepath) {
    std::ifstream myfile;
    myfile.open(filepath);
    if(myfile.is_open()) { 
        std::vector<double> result;
        std::string line;
        while(getline(myfile, line)) {
            std::stringstream rowStringStream(line);
            double num;
            while (rowStringStream >> num) {
                result.push_back(num);
            }
        }
        return result;
    } else {
        throw std::runtime_error("Could not open knowledge base file."); 
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
