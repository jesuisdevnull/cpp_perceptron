#include "./utils.hpp"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <stdexcept>
#include <algorithm>
#include <random>

std::vector<std::vector<std::vector<double>>> read_files(std::vector<std::string> filepaths) { 
    std::ifstream myfile;
    std::vector<std::vector<std::vector<double>>> result;
    for(auto filepath : filepaths) {       
        myfile.open(filepath);
        if (myfile.is_open()) {
            std::cout << "File is open!" << "\n";
            double num;
            std::vector<double> expectedOutput;
        
            std::string line;
            getline(myfile, line);
            std::stringstream inputStringstreamExpected(line);
            std::cout << line << "\n";
            while(inputStringstreamExpected >> num) {
                expectedOutput.push_back(num);
            }

            while (getline(myfile, line)) {
                std::vector<double> input;
                std::vector<std::vector<double>> labeledInput;
                std::stringstream inputStringstreamInput(line);
                while (inputStringstreamInput >> num) {
                    input.push_back(num);
                }
                labeledInput.push_back(input);
                labeledInput.push_back(expectedOutput);
                result.push_back(labeledInput);
            }
            myfile.close();    
        } else { 
            std::cout << "File not open." << "\n";    
        }
    }
    auto engine = std::default_random_engine{};
    std::shuffle(std::begin(result),std::end(result),engine);
    return result;    
}


