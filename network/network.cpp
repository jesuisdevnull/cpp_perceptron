#include <vector>
#include "../vector-operations/vector-operations.hpp"
#include "../neuron/neuron.cpp"
#include <cmath>
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
            errorMargin = 0.05;
        }

	void printWeights() {
	    std::cout << "NEURAL NETWORK WEIGHTS\n\n";
	    int i = 1;
	    for(Neuron neur:neurons) {
		std::cout << "NEUR" << i << " ";
		neur.printWeights();
		i++;
	    }
	    std::cout << "\n";
	}

    std::vector<double> predict(std::vector<double> input) {
            std::vector<double> networkOutput;
            for(Neuron neuron:neurons) {
                double neuronOutput = neuron.predict(input);
                networkOutput.push_back(neuronOutput);
            }
            return networkOutput;
        }

    std::vector<double> predictWithTraining(std::vector<double> input,std::vector<double> expectedOutput) {
	std::vector<double> networkOutput;
//        printWeights();  
        int i = 0;
        for(Neuron& neuron:neurons) {
             double neuronOutput = round(neuron.predict(input));
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
            double absoluteError = abs(error);
            if(absoluteError > errorMargin) {
                std::cout << "Training neuron " << neuronId << " (absolute error was " << absoluteError << ")\n";
                neuron.train(neuronId, inputs, error, learningRate);
            } else { 
                std::cout << "No need to train neuron " << neuronId << " (absolute error was " << absoluteError << ")\n";
            }
            i++;
	}    
    }
};
