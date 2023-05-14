#include <vector>
#include "../neuron/neuron.cpp"
#include <stdexcept>

class SingleLayerNeuralNetwork {
    public:
        SingleLayerNeuralNetwork(int numberOfInputs, int numberOfNeurons, double learningRateInitializer) {
            for(int i = 0; i < numberOfNeurons; i++) {
                Neuron neuron = Neuron(numberOfInputs);
		neurons.push_back(neuron);
	    }
	    learningRate = learningRateInitializer;
        } 

    private:
	std::vector<Neuron> neurons;
	double learningRate;
};
