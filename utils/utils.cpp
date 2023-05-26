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


/*
    Helper function that loads all training data for the neural network. Each file has the following contents:
    1. Five space separated numbers on the first line, either a 0 or a 1. This is the label for each image in the file.
    2. N lines containing 160 space separated numbers. It represents the bit matrix of the 16x10 image, but flattened into one dimension.

    Hence, the return value is a list of value-label pairs, each representing a training example for a specific letter. This is a truncated
    sample of the training file for the letter "e", for reference's sake:

    Line 1:
    0 1 0 0 0
    Line 2:
    0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 1 1 0 0 0 0 0 0 1 1 0 0 1 0 0 0 0 0 1 0 0 0 1 0 0 0 0 1 0 0 0 0 1 0 0 0 1 1 0 0 0 1 1 0 0 0 1 1 1 1 1 0 0 0 0 0 1 0 0 0 0 0 0 0 0 0 0 1 0 0 0 0 0 0 0 0 0 1 1 0 0 0 1 1 0 0 0 0 1 1 1 1 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
    Line 3:
    0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 1 1 0 0 0 0 0 1 1 0 0 1 0 0 0 0 0 1 0 0 0 1 0 0 0 0 1 0 0 0 0 1 0 0 0 0 1 0 1 1 1 1 0 0 0 0 1 0 0 0 0 0 0 0 0 0 1 1 0 0 0 0 0 0 0 0 0 1 1 0 0 0 0 0 0 0 0 0 1 1 1 1 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
    Line 4:
    0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 1 1 1 0 0 0 0 0 1 1 0 0 1 0 0 0 0 0 1 0 0 0 1 0 0 0 0 1 0 0 1 1 0 0 0 0 0 1 1 1 1 0 0 0 0 0 0 1 0 0 0 0 0 0 0 0 0 1 1 0 0 0 0 0 0 0 0 0 1 1 0 0 0 0 0 0 0 0 0 1 1 1 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
    Line 5:
    0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 1 1 1 0 0 0 0 0 0 1 0 0 1 0 0 0 0 1 1 0 0 0 1 0 0 0 0 1 0 0 0 0 1 0 0 0 0 1 0 0 1 1 0 0 0 0 1 0 1 1 1 0 0 0 0 0 1 0 0 0 0 0 0 0 0 0 1 0 0 0 0 0 0 0 0 0 0 1 1 1 1 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0

    If we unflatten Line 5, we'll see the matrix representation of the letter itself:

    Unflattened line 5:

    0 0 0 0 0 0 0 0 0 0 
    0 0 0 0 0 0 0 0 0 0 
    0 0 0 0 0 0 0 0 0 0 
    0 0 0 0 0 0 0 0 0 0 
    0 0 0 0 1 1 1 1 0 0 
    0 0 0 0 1 0 0 1 0 0 
    0 0 1 1 0 0 0 1 0 0 
    0 0 1 0 0 0 0 1 0 0 
    0 0 1 0 0 1 1 0 0 0 
    0 1 0 1 1 1 0 0 0 0 
    0 1 0 0 0 0 0 0 0 0 
    0 1 0 0 0 0 0 0 0 0 
    0 0 1 1 1 1 1 0 0 0 
    0 0 0 0 0 0 0 0 0 0 
    0 0 0 0 0 0 0 0 0 0 
    0 0 0 0 0 0 0 0 0 0
*/

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

/* Essentially the same as the previous function, but for testing samples. */

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

/* 
    Helper function that reads, parses, knowledge base and initializes a neural network with it. The knowledge base is generated by the saveKnowledge() 
    method of a SingleLayerNeuralNetwork instance. 
*/

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

/* 
    Helper function that reads a file containing the matrix representation of a single letter in a file, and returns a label that can be parsed by a
    neural network's predict() function. Such a file has 16 lines of 10 space-separated values that conform the 16x10 matrix. Here's an instance of the
    lowercase letter "e" in such a format:

    0 0 0 0 0 0 0 0 0 0
    0 0 0 0 0 0 0 0 0 0
    0 0 0 0 0 0 0 0 0 0
    0 0 0 0 0 0 0 0 0 0
    0 0 0 0 0 0 0 0 0 0
    0 0 0 1 1 1 0 0 0 0
    0 0 0 1 0 0 1 0 0 0
    0 0 1 1 0 0 0 1 0 0
    0 1 1 0 0 0 1 1 0 0
    0 1 0 1 1 1 1 0 0 0
    0 1 0 0 0 0 0 0 0 0
    0 1 1 0 0 0 0 0 0 0
    0 0 1 0 0 0 0 0 0 0
    0 0 1 1 1 0 0 1 0 0
    0 0 0 0 1 1 1 1 0 0
    0 0 0 0 0 0 0 0 0 0

*/

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

/* Used in conjunction with interpret_index() to interpret the neural network's output.*/

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

/* 
    The index of the highest element the output vector (as well as the input label) of a neural network is used to determine what the network's guess
    (or its expected output) actually is. This works because the input vector label is a binary vector with only one nonzero value, and the output vector's
    values can be interpreted as the probability of a specific letter being the answer. Hence, if we take the index of the highest element in the
    output vector and interpret it, we get the network's best guess for a given input.
*/

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
