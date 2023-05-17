#include "./utils.hpp"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <stdexcept>

std::vector<std::vector<double>> read_file(std::string filepath) {
    std::ifstream myfile;
    std::vector<std::vector<double>> result;
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

        result.push_back(expectedOutput);

        while (getline(myfile, line)) {
            std::cout << line << "\n";
            std::vector<double> input;
            std::stringstream inputStringstreamInput(line);
            while (inputStringstreamInput >> num) {
                input.push_back(num);
            }
            result.push_back(input);
        }

        myfile.close();    
    } else { 
        std::cout << "File not open." << "\n";    
    }
    return result;
}


