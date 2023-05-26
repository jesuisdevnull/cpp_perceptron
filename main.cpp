/* Jesus Raziel Gonzalez Sosa, C.I. 28.074.361  */

#include "vector-operations/vector-operations.hpp"
#include "network/network.cpp"
#include "utils/utils.hpp"

#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <ctime>

#include <vector>
#include <random>
#include <algorithm>
#include <stdexcept>

/* Check whether the given string is a positive.iinteger.  */
bool is_number(const std::string& s)
{
    std::string::const_iterator it = s.begin();
    while (it != s.end() && std::isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
}

int main(int argc, char* argv[]) {
    std::cout << "Single Layer Neural Network 1.0\n\n";
    if (argc > 1) {
        srand(time(0));
        std::ifstream base;
        SingleLayerNeuralNetwork* nnp; 

        base.open("base.txt");
        if (base.is_open()) {
            base.close();
            try {
                nnp = read_knowledge_base("base.txt");
            } catch (const std::runtime_error& e) {
                std::cout << "Could not read knowledge file. Exiting.";
                return 1;
            }
        } else {
	        std::cout << "Could not find knowledge base. Creating neural network from scratch."  << "\n";
            nnp = new SingleLayerNeuralNetwork(160, 5, 0.07); 
        }

        SingleLayerNeuralNetwork nn = *nnp; 
        int i = 0;

        if (strcmp(argv[1], "train") == 0) {
            if (argc < 3) {
                std::cout << "Not enough parameters for training. Exiting." << "\n";
                return 1;
            } else {
               std::string epochArg(argv[2]);
               if (!is_number(epochArg)) {
                    std::cout << "Invalid argument for number of epochs." << "\n";
                    return 1;
               } else {
                    int parsedEpoch = atoi(argv[2]);
                    if (parsedEpoch < 0) {
                        std::cout << "Number of epochs cannot be a negative number." << "\n";
                        return 1;
                    }
               }
            }
            std::vector<std::string> filenames = {"training-samples/a.txt","training-samples/e.txt","training-samples/i.txt","training-samples/o.txt","training-samples/u.txt"}; 
            std::vector<std::vector<std::vector<double>>> vec = read_training_files(filenames); 
            bool process = true; 
            int j = 0;
            int epochs = atoi(argv[2]);
            std::random_device rd; 
            auto rng = std::default_random_engine { rd() };
    	    while(process) {
                for (auto labeledV : vec) {
                    i++;    
	                std::cout << "ITERATION " << i+1 << "\n";
                    std::vector<double> output = nn.predictWithTraining(labeledV.at(0), labeledV.at(1));
                }
                j++;
                if(j > epochs) {
                    process = false;
                } else {
                    std::shuffle(std::begin(vec), std::end(vec), rng);   
                }
    	    }       
    	    bool result = nn.saveKnowledge("base.txt");
    	    if (result) { 
	            std::cout << "Saved knowledge!"  << "\n";
    	    } else {
	            std::cout << "Couldn't save knowledge"  << "\n";
    	    }
        } else if (strcmp(argv[1],"test") == 0) {
            if (argc > 2) { 
                std::string filepath(argv[2]);
                std::vector<double> input = read_individual_letter(filepath);
                std::cout << "Network thinks this is an: : " << interpret_index(find_max_index(nn.predict(input))) << "\n";
            } else {
                std::vector<std::string> filenames_tr = {"testing-samples/a.txt","testing-samples/e.txt","testing-samples/i.txt","testing-samples/o.txt","testing-samples/u.txt"}; 
                std::vector<std::vector<std::vector<double>>> vec_tr = read_testing_files(filenames_tr); 
		int successes = 0;
		int attempts = 0;
		double accuracy;
                for(auto labeledV : vec_tr) {
		    std::string label = 
 interpret_index(find_max_index(labeledV.at(1)));                   std::cout << "\nSample " << i+1  << "\n";
                    std::cout << "Label for this output: " << label  << "\n"; 
		    std::string outLabel =interpret_index(find_max_index(nn.predict(labeledV.at(0))));
                    std::cout << "Network thinks this is an: : " <<outLabel << "\n";
                    attempts++;
		    if (label == outLabel) {
			successes++;
		    }
		    i++;

                }
		accuracy = ((double)successes/attempts)*100;
		std::cout << accuracy << "% accuracy (" << successes << " out of " << attempts << " attempts)" << "\n"; 
            }
        } else if (strcmp(argv[1],"help") == 0){ 
	    std::cout << "The program creates a new neural network at startup. If it can find a 'base.txt' file in the same directory where it is run, it will attempt to load it, otherwise it will generate a new one from scratch. \n\nRunning the program with the 'train' argument causes the neural network to loop over and learn from the training set as many times as specified in the second argument (minimum 0, which causes it to loop over it 1 time)\n\nRunning it with the test argument has different behavior depending on whether the third argument (a filepath) is supplied. If none is given, the neural network will attempt to classify the entire training set, whole if it is it will attempt to classify a single letter contained in the filepath given. Formatting info for both the letter and knowledge base can be found in the documentation.\n\nFile locatons relative to the executable:\n\nTraining samples: ./training-samples \nTesting samples: ./testing-samples\nKnowledge base: ./base.txt\n\n"; 
	} else  {
            std::cout << "No valid CLI arguments were found. Please pass either of the following arguments when running the program:\n\ntrain {0-9}*\ntest [filename]\nhelp\n";
        }   
        delete(nnp);
        return 0;
    } else {
        std::cout << "No CLI arguments were found. Please pass either of the following arguments when running the program:\n\ntrain {0-9}+\ntest [filename]\nhelp\n";
        return 0;
    }
}
