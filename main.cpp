#include <vector>
#include <iostream>
#include <cmath>
#include <stdexcept>
#include <cstdlib>
#include <time.h>

using namespace std;

int generateBoundedRandomInt(int lowerBound, int upperBound) {
    return (rand() % (upperBound - lowerBound + 1));    
}

class Neuron {
    public:
        Neuron(vector<double> initWeights, double initBias) {
            weights = initWeights;
            bias = initBias;
        }

        vector<double> getWeights() {
            return weights;
        }        

        double getBias() {
            return bias;
        }
        
        string toString() {
            string result = "[ ";
            for (double weight : weights) {
                result.append(to_string(weight));
                result.append(" ");    
            }
            result.append("] (");
            result.append(to_string(bias));
            result.append(")");
            return result;
        } 

        double processInputs(vector<double> inputs) {
            if(inputs.size() != weights.size()) {
                throw invalid_argument("Input vector must be the same size as neuron weight vector.");
            }
            double weightedSumResult = weightedSum(inputs);
            double output = (weightedSumResult >= bias) ? activation(weightedSumResult) : 0;
            return output;
        }

    private:
        vector<double> weights;
        double bias;
        
        double weightedSum(vector<double> inputs) {
            int index = 0;
            double result = 0;
            for (double input:inputs) {
                result += input * weights.at(index);
                index++;
            }
            return result;
        }
        
        double sigmoid(float x) {
            return (1/(1+exp(-x)));
        }
        
        double activation(double sumResult) {
            return sigmoid(sumResult);
        }       
};

class Perceptron {
    public:
        Perceptron(int numberOfInputs, int numberOfOutputs, int numberOfNeurons) {
            int lowerBound = 1;
            int upperBound = 100;
            for(int i = 0; i < numberOfInputs; i++) {
                vector<double> randomWeights = generateRandomWeights(numberOfInputs,lowerBound, upperBound);
                double randomBias = generateBoundedRandomInt(lowerBound, upperBound);
                Neuron neuron = Neuron(randomWeights, randomBias);
                neurons.push_back(neuron);
            }
        }

        string toString() {
            string result = "[\n";
            for (Neuron neur:neurons) {
                result.append("    ");
                result.append(neur.toString());
                result.append("\n");
            }
            result.append("]\n");
            return result;
        }
    private:
        vector<Neuron> neurons;

        vector<double> generateRandomWeights(int numberOfWeights, int lowerBound, int upperBound) {
            vector<double> weights;
            for(int i = 0; i < numberOfWeights; i++) {
                weights.push_back(generateBoundedRandomInt(lowerBound, upperBound));
            }
            return weights;
        }
        
};

int main() {
    srand(time(0));
   // vector<double> v_weights = {1, 1.2, 5, 4.0, 2};
   // vector<double> v_inputs = {10, 2, -4,0, 1};
   // double bias = 10;
   // Neuron neuron = Neuron(v_weights,bias);
   // cout << "Hello, world!\n";
   // cout << neuron.processInputs(v_inputs) << "\n";
   // cout << neuron.toString();
   Perceptron perc = Perceptron(10, 5, 10);
   cout << perc.toString();
}
