#include "../vector-operations/vector-operations.hpp"
#include "../neuron/neuron.cpp"

#include <random>
#include <vector>
#include <cmath>
#include <stdexcept>
#include <iostream>
#include <fstream>

#ifndef NET_H
#define NET_H
class SingleLayerNeuralNetwork {
    public:
        SingleLayerNeuralNetwork(int numberOfInputs, int numberOfNeurons, double learningRateInitializer) { 
    	    std::random_device rd;  // Will be used to obtain a seed for the random number engine
    	    std::mt19937 gen(rd()); // Standard mersenne_twister_engine seeded with rd()
   	    std::uniform_real_distribution<> dis(-1.5,1.5);
	    for(int i = 0; i < numberOfNeurons; i++) {
                Neuron neuron = Neuron(numberOfInputs,gen,dis);
		neurons.push_back(neuron);
	    }
	    learningRate = learningRateInitializer;
            errorMargin = 0.05;
        }

	SingleLayerNeuralNetwork(std::vector<Neuron> initializedNeurons, double initializedLearningRate, double initializedErrorMargin) {
		neurons = initializedNeurons;
		learningRate = initializedLearningRate;
		errorMargin = initializedErrorMargin;
	}

	void printWeights() {
	    std::cout << "NEURAL NETWORK WEIGHTS\n\n";
	    int i = 1;
	    for(Neuron& neur:neurons) {
		std::cout << "NEUR" << i << " ";
		neur.printWeights();
		i++;
	    }
	    std::cout << "\n";
	}

    std::vector<double> predict(std::vector<double> input) {
            std::vector<double> networkOutput;
            for(Neuron neuron:neurons) {
                double neuronOutput =neuron.predict(input);
                networkOutput.push_back(neuronOutput);
            }
            return networkOutput;
        }

    std::vector<double> predictWithTraining(std::vector<double> input,std::vector<double> expectedOutput) {
	std::vector<double> networkOutput;
//        printWeights();  
        int i = 0;
        for(Neuron& neuron:neurons) {
             double neuronOutput = round(neuron.predict(input)); //round(neuron.predict(input));
           //  std::cout << "Neuron " << i << " weights:";
          //   neuron.printWeights();
          //   std::cout << "Input: ";
          //   printVector(input); 
         //    std::cout << "Expected output ";
           //  std::cout << expectedOutput.at(i) << "\n"; 
           //  std::cout << "Actual output: ";
           //  std::cout << neuronOutput << "\n\n"; 
             networkOutput.push_back(neuronOutput);
	     i++;
        } 	
        trainNeurons(input, expectedOutput, networkOutput);    
        
        //printWeights();
        return networkOutput;
    }

    bool saveKnowledge(std::string filepath) {
	    std::ofstream outputFile;
	    outputFile.open(filepath);
	    if(outputFile.is_open()) {
		outputFile << std::to_string(learningRate) << "\n";
		outputFile << std::to_string(errorMargin) << "\n"; 
		int i = 0;
		for(Neuron& neuron:neurons) {
		    outputFile << neuron.getSerializableRepresentation();
		    if (i < neurons.size()-1) {
                        outputFile << "\n";
		    }
		}
		outputFile.close();
		return true;
	    }
            return false;
    }

    private:
	std::vector<Neuron> neurons;
	double learningRate;
        double errorMargin;

    void trainNeurons(std::vector<double> inputs, std::vector<double> expectedOutput, std::vector<double> actualOutput) {
        /*
            std::cout << "Neural Network Input: ";
            printVector(inputs); 
            std::cout << "Neural Network Expected Output:  ";
            printVector(expectedOutput); 
            std::cout << "Neural Network Actual Output:  "; 
            printVector(actualOutput); 
        */
        int i = 0;
        for(Neuron& neuron:neurons) {
            int neuronId = i + 1;
            double expectedNeuronOutput = expectedOutput.at(i);
            double actualNeuronOutput = actualOutput.at(i);
	    double error = expectedNeuronOutput - actualNeuronOutput;
            if(error != 0) {
                std::cout << "Training neuron " << neuronId << " (difference between outputs was " << error << ")\n";
                neuron.train(neuronId, inputs, error, learningRate);
            } else { 
                std::cout << "No need to train neuron " << neuronId << " (difference between outputs was " << error << ")\n";
            }
            i++;
	}    
    }
};
#endif
