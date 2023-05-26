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

    /* 
        This single-layered neural network, much like the neurons that make it up, can be constructed ffrom scratch or from a pre-existing knowledge base. 
        This is represented by each of the constructor methods: one initializes each neuron randomñy, while the other loads prefetched values.  
    */

    class SingleLayerNeuralNetwork {
        public:
            SingleLayerNeuralNetwork(int numberOfInputs, int numberOfNeurons, double learningRateInitializer) { 
                std::random_device rd; 
                std::mt19937 gen(rd()); 
                std::uniform_real_distribution<> dis(-5,5);
                for(int i = 0; i < numberOfNeurons; i++) {
                    Neuron neuron = Neuron(numberOfInputs,gen,dis);
                    neurons.push_back(neuron);
                }
                learningRate = learningRateInitializer;
                /* 
                    An error margin of 0.02 results in 65% accuracy, while an error margin of 
                    0.00000000001 results in 70%, with the same number of epochs, or full loops over the
                    training set (500).
                */

                /* errorMargin = 0.02; */
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

        /* The prediction function returns a vector of doubles, which is later interpreted in order to inform the user of the neural network's guess.*/

        std::vector<double> predict(std::vector<double> input) {
            std::vector<double> networkOutput;
            for(Neuron neuron:neurons) {
                double neuronOutput = neuron.predict(input);
                networkOutput.push_back(neuronOutput);
            }
            return networkOutput;
        }

        /* This method works the same way as predict(), but also kickstarts the training process. */

        std::vector<double> predictWithTraining(std::vector<double> input,std::vector<double> expectedOutput) {
            std::vector<double> networkOutput;
            int i = 0;
            for(Neuron& neuron:neurons) {
                double neuronOutput = neuron.predict(input);
                networkOutput.push_back(neuronOutput);
            i++;
            } 	
            trainNeurons(input, expectedOutput, networkOutput);    
            return networkOutput;
        }

        /* This method is the one responsible for saving the neural network's knowledge base, which is then loaded next time the program gets executed.
        It's a plain-text file containing string representations of the network (error margin, bias, learning rate) as well as each of its neurons. */

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

        /* 
            We loop over the arraty of neurons and check what their output was for this specific training example. Each neuron is supposed to be associated
            with a single letter (since there are as many neurons as there are indices in the output vector), so we take advantage of that by keeping the 
            indices in sync (that's the index variable i).
        
            Usually, the delta rule dictates that a neuron should only be trained if its error is not equal to 0. But, considering we're working with
            real values and not rounding (since it both causes the network to converge too quickly), I found it suitable to use an error margin instead. So,
            the neuron only gets trained if the absolute value of the difference in outputs is greater than the network's acceptable error margin. 

            The end result is basically the same.
        */
        void trainNeurons(std::vector<double> inputs, std::vector<double> expectedOutput, std::vector<double> actualOutput) {
            int i = 0;
            for(Neuron& neuron:neurons) {
                int neuronId = i + 1;
                double expectedNeuronOutput = expectedOutput.at(i);
                double actualNeuronOutput = actualOutput.at(i);
                double error = expectedNeuronOutput - actualNeuronOutput;
                if(abs(error) > errorMargin) {
                    neuron.train(neuronId, inputs, error, learningRate);
                }
                i++;
            }    
        }
    };
#endif
