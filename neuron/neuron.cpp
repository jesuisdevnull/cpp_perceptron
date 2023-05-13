#include <vector>
#include <stdexcept>
#include <cstdlib>
#include <ctime>
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

        int predict(std::vector<double> inputs) {
            return activation(inputs);
        }
    
    private:
        std::vector<double> weights;
        double bias;

        int activation(std::vector<double> inputs) {
            double sum_result = dot_product(weights, inputs);
            return heaviside_step(sum_result + bias);
        }

        int heaviside_step(double input) {
            if (input > 0) {
                return 1;
            }  
            return 0;
        }
};
