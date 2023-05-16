#include <vector>
#include "../vector-operations/vector-operations.hpp"
#include "../neuron/neuron.cpp"

#include <stdexcept>
#include <iostream>

class SingleLayerNeuralNetwork {
    public:
        SingleLayerNeuralNetwork(int numberOfInputs, int numberOfNeurons, double learningRateInitializer) {
            for(int i = 0; i < numberOfNeurons; i++) {
                Neuron neuron = Neuron(numberOfInputs);
		neurons.push_back(neuron);
	    }
	    learningRate = learningRateInitializer;
        }

	void printWeights() {
	    std::cout << "NEURAL NETWORK WEIGHTS\n\n";
	    int i = 1;
	    for(Neuron neur:neurons) {
		std::cout << "NEUR" << i << " ";
		neur.printWeights();
		i++;
	    }
	    std::cout << "\n ";
	}

    std::vector<double> predict(std::vector<double> input) {
            std::vector<double> networkOutput;
            for(Neuron neuron:neurons) {
                double neuronOutput = neuron.predict(input);
                networkOutput.push_back(neuronOutput);
            }
            /* if(isTraining) {
                trainNeurons(input, networkOutput);    
            }*/
            return networkOutput;
        }

    std::vector<double> predictWithTraining(std::vector<double> input,std::vector<double> expectedOutput) {
	std::vector<double> networkOutput;
        printWeights();  
        int i = 0;
        for(Neuron& neuron:neurons) {
             double neuronOutput = neuron.predict(input);
             std::cout << "Neuron " << i << " weights: \n";
             neuron.printWeights();
             std::cout << "Input: ";
             printVector(input); 
             std::cout << "Expected output ";
             std::cout << expectedOutput.at(i) << "\n"; 
             std::cout << "Actual output: ";
             std::cout << neuronOutput << "\n\n"; 
             networkOutput.push_back(neuronOutput);
	     i++;
        }
        
	
        trainNeurons(input, expectedOutput, networkOutput);    
        
        printWeights();
        return networkOutput;
    }

    private:
	std::vector<Neuron> neurons;
	double learningRate;

    void trainNeurons(std::vector<double> inputs, std::vector<double> expectedOutput, std::vector<double> actualOutput) {
        
        std::cout << "Neural Network Input: ";
        printVector(inputs); 
        std::cout << "Neural Network Expected Output:  ";
        printVector(expectedOutput); 
        std::cout << "Neural Network Actual Output:  "; 
        printVector(actualOutput); 
        
        int i = 0;
        for(Neuron& neuron:neurons) {
                std::cout << "Training neuron " << i+1 << "\n";
            double expectedNeuronOutput = expectedOutput.at(i);
            double actualNeuronOutput = actualOutput.at(i);
	    neuron.train(inputs, expectedNeuronOutput, actualNeuronOutput, learningRate);
            i++;
	}    
    }
};
