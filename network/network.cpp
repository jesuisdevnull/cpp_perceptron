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

/* This single-layered neural network, much like the neurons that make it up, can be constructed ffrom scratch or from a pre-existing knowledge base. This is represented by each of the constructor methods: one initializes each neuron randomñy, while the other loads prefetched values.  */

class SingleLayerNeuralNetwork {
    public:
        SingleLayerNeuralNetwork(int numberOfInputs, int numberOfNeurons, double learningRateInitializer) { 
    	    std::random_device rd;  // Will be used to obtain a seed for the random number engine
    	    std::mt19937 gen(rd()); // Standard mersenne_twister_engine seeded with rd()
   	        std::uniform_real_distribution<> dis(-5,5);
	        for(int i = 0; i < numberOfNeurons; i++) {
                Neuron neuron = Neuron(numberOfInputs,gen,dis);
		    neurons.push_back(neuron);
	        }
	        learningRate = learningRateInitializer;
	/* An error margin of 0.02 results in 65% accuracy, while an error margin of 0.000000000011 results in 70%, with the same number of epochs. */
	   //errorMargin = 0.02;
            errorMargin = 0.00000000001;
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
        int i = 0;
        for(Neuron& neuron:neurons) {
             double neuronOutput = neuron.predict(input); //round(neuron.predict(input));
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
            if(abs(error) > errorMargin) {
                std::cout << "Training neuron " << neuronId << " (difference between outputs was " << abs(error) << ")\n";
                neuron.train(neuronId, inputs, error, learningRate);
            } else { 
                std::cout << "No need to train neuron " << neuronId << " (difference between outputs was " << error << ")\n";
            }
            i++;
	}    
    }
};
#endif
