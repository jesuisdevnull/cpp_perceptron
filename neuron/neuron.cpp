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
                int randomWeight = rand() % 100 + 1;
                weights.push_back(randomWeight);
                bias = rand() % 100 + 1;
            }
        }

        Neuron(std::vector<double> initialized_weights) {
            weights = initialized_weights;
            bias = rand() % 100+1;   
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
    
        void train(std::vector<double> inputs, int expectedNeuronOutput, double actualNeuronOutput, double learningRate) {
            int i = 0;
            std::vector<double> deltaWeights;
            for (double weight:weights) {
                double outputDifference = (expectedNeuronOutput - actualNeuronOutput);
                double scalar = learningRate * outputDifference;
		double input = inputs.at(i);
		double individualWeightDifference = scalar * input;
		deltaWeights.push_back(individualWeightDifference);
		i++;
            }
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
	    printVector(weights);
        }


        /*int heaviside_step(double input) {
            if (input > 0) {
                return 1;
            }  
            return 0;
        }*/

        
};
