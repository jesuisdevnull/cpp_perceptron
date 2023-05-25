#include <vector>
#include <string>
#include "../network/network.cpp"

std::vector<std::vector<std::vector<double>>> read_training_files(std::vector<std::string> filepaths);

std::vector<std::vector<std::vector<double>>> read_testing_files(std::vector<std::string> filepaths);

SingleLayerNeuralNetwork* read_knowledge_base(std::string filepath);

std::vector<double> read_individual_letter(std::string filepath);

int find_max_index(std::vector<double> vec);

std::string interpret_index(int i);
