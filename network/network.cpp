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

    std::vector<double> predict(std::vector<double> input, bool isTraining) {
            std::vector<int> networkOutput;
            for(Neuron neuron:neurons) {
                int neuronOutput = neuron.predict(input);
                networkOutput.push_back(neuronOutput);
            }
            if(isTraining) {
                trainNeurons(input, networkOutput)    
            }
            return networkOutput;
        }

    private:
	std::vector<Neuron> neurons;
	double learningRate;

    void trainNeuron(std::vector<int> inputs,  std::vector<int> expectedOutput, std::vector<int> actualOutput) {
        int i = 0;
        for(Neuron neuron:neurons) {
            int expectedNeuronOutput = expectedOutput.at(i);
            int actualNeuronOutput = actualOutput.at(i);
            neuron.train(inputs, expectedNeuronOutput, actualNeuronOutput, learningRate)
        }    
    }
};
