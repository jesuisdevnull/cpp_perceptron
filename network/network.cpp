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
        for(Neuron neuron:neurons) {
        double neuronOutput = neuron.predict(input);
             networkOutput.push_back(neuronOutput);
	}
	trainNeurons(input, expectedOutput, networkOutput);    
        return networkOutput;
    }

    private:
	std::vector<Neuron> neurons;
	double learningRate;

    void trainNeurons(std::vector<double> inputs, std::vector<double> expectedOutput, std::vector<double> actualOutput) {
        int i = 0;
        for(Neuron& neuron:neurons) {
            int expectedNeuronOutput = expectedOutput.at(i);
            int actualNeuronOutput = actualOutput.at(i);
	    std::cout<<"Neuron "<< i << " before adjustment: ";
	    neuron.printWeights();
	    neuron.train(inputs, expectedNeuronOutput, actualNeuronOutput, learningRate);
            std::cout<<"Neuron "<< i << " after adjustment: ";
	    neuron.printWeights();
            i++;
	}    
    }
};
