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

    std::vector<int> predict(std::vector<double> input) {
            std::vector<int> networkOutput;
            for(Neuron neuron:neurons) {
                int neuronOutput = neuron.predict(input);
                networkOutput.push_back(neuronOutput);
            }
            return networkOutput;
        }

    private:
	std::vector<Neuron> neurons;
	double learningRate;
};
