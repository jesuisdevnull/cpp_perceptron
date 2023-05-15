#include <vector>
#include <stdexcept>
#include <cstdlib>
#include <ctime>
#include <math.h>
#include "../vector-operations/vector-operations.hpp" 

class Neuron {
    public:
        Neuron(int numberOfInputs) {
            srand(time(0));
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

        double predict(std::vector<double> inputs) {
            return activation(inputs);
        }
    
        void train(std::vector<double> inputs, int expectedNeuronOutput, double actualNeuronOutput, double learningRate) {
            int i = 0;
            for (double weight:weights) {
                double netInput = dot_product(weights, inputs);
                double evaluatedDerivative = sigmoidDerivative(netInput);
                double outputDifference = (expectedNeuronOutput - actualNeuronOutput);
                // Oh, this updates the weights all at once! That makes sense. It's scalar-vector product.
                double scalar = learningRate * outputDifference * evaluatedDerivative;
                std::vector<double> deltaWeights = scale_vector(inputs, scalar);
                adjustWeights(deltaWeights);
            }
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
