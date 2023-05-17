#include <vector>
#include <stdexcept>
#include <cstdlib>
#include <math.h>
#include <iostream>
#include "../vector-operations/vector-operations.hpp" 

class Neuron {
    public:
        Neuron(int numberOfInputs) {
            for (int i = 0; i < numberOfInputs; i++) {
                int randomWeight = rand() % 10 + 1;
                weights.push_back(randomWeight);
                bias = 0;
            }
        }

        Neuron(std::vector<double> initialized_weights) {
            weights = initialized_weights;
            bias = 0;   
        }

        Neuron(std::vector<double> initialized_weights, double initialized_bias) {
            weights = initialized_weights;
            bias = initialized_bias;
        }

	void printWeights() {
            printVector(weights);
	}

        double predict(std::vector<double> inputs) {
            return activation(inputs);
        }
    
        void train(int neuronId, std::vector<double> inputs,double error, double learningRate) {
            /*
            double net = dot_product(weights, inputs);
            std::cout << "Learning rate: " << learningRate	<< "\n";
            std::cout << "Expected output " << expectedNeuronOutput	<< "\n";
            std::cout << "Actual neuron output: " << actualNeuronOutput  << "\n"; 
            std::cout << "Output difference " << outputDifference << "\n";
            std::cout << "Net input: " << net << "\n";
            std::cout << "Evaluated derivative: " << evaluatedDerivative << "\n";
            */
            double learningTimesError = learningRate * error; // * evaluatedDerivative;
            std::vector<double> deltaWeights;
            int i = 0;
            for (double weight:weights) {
		double input = inputs.at(i);
		double individualWeightDifference = learningTimesError * input;
                std::cout << "Calculating adjustment for weight " << i+1 << "...\n";
                std::cout << "Input " << i << " for weight " << i+1 <<": " << input << "\n"; 
                std::cout << "Final multiplication: " << learningTimesError  << "*" << input << "\n";
                std::cout << "Delta weight for weight " << i+1 << ": " << individualWeightDifference << "\n\n";
                 
                deltaWeights.push_back(individualWeightDifference);
		i++;
            }
            std::cout << "Delta weight matrix for neuron " << i <<":\n";
            printVector(deltaWeights); 
            adjustWeights(deltaWeights);
        }

    private:
        std::vector<double> weights;
        double bias;

        double activation(std::vector<double> inputs) {
            double sum_result = dot_product(weights, inputs);
            return sigmoid(sum_result + bias);
        }

        double sigmoid(double input) {
           return 1/(1+exp(-input));     
        }

        double sigmoidDerivative(double input) {
            return sigmoid((input)*(1-sigmoid(input)));    
        }

        void adjustWeights(std::vector<double> delta) {
            std::vector<double> adjustedWeights = add_vector(weights, delta);
            weights = adjustedWeights;    
        }


        /*int heaviside_step(double input) {
            if (input > 0) {
                return 1;
            }  
            return 0;
        }*/

        
};
