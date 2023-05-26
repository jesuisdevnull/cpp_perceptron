#include "../vector-operations/vector-operations.hpp" 
#include <vector>
#include <stdexcept>
#include <cstdlib>
#include <math.h>
#include <iostream>
#include <random>
#include <string>

#ifndef NEUR_H
#define NEUR_H

/* A neuron can be constructed bt either specifying the number of inputs it takes, or by manually setting all the weights and inputs. These constructors align with both scenarios in which we might create a Neural Network: either from scratch, or from an existing knowledge base.
 
 Bias is initially set to 0, and is adjusted during the learning process. Each weight is initialized to a random real value within a range.*/

class Neuron {
    public:
        Neuron(int numberOfInputs, std::mt19937& gen, std::uniform_real_distribution<>& dis) {
            for (int i = 0; i < numberOfInputs; i++) {
                double randomWeight = dis(gen);
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

   /* We train each neuron by using the so-called Delta rule, which states that each weight shouldbe adjusted by the product of the network's learning rate, the diffefence between the expected and actual output, and the input that corresponds tothe weight in question.
    
    We loop over the weight vector and calculate each adjustment, pushing it into another vector.in order to update every weight all at once.

    We also adjust the bias in the same way.
*/
        void train(int neuronId, std::vector<double> inputs,double error, double learningRate) {
            double learningTimesError = learningRate * error;
            std::vector<double> deltaWeights;
            int i = 0;
            for (double weight:weights) {
		double input = inputs.at(i);
		double individualWeightDifference = learningTimesError * input;
               deltaWeights.push_back(individualWeightDifference);
		i++;
            }
            adjustWeights(deltaWeights);
            double deltaBias = error * learningRate;
	    bias += deltaBias;
	}

	/* Essentially a string representation of the neuron.  */
        std::string getSerializableRepresentation() {
		std::string rep;
		rep.append(std::to_string(bias));
		rep.append("\n");
		for (auto weight:weights) {
		    rep.append(std::to_string(weight));
		    rep.append(" ");
		}
		return rep;
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


};
#endif
