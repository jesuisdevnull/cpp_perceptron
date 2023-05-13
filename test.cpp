#include <vector>
#include <iostream>
#include "vector-operations/vector-operations.hpp"
#include "neuron/neuron.cpp"

int main() {
    std::vector<double> a {1,2.2,10,2};
    std::vector<double> b {10,10,10,1};
    double c = dot_product(a,b);
    std::cout << c << "\n";
    Neuron neuron = Neuron(a,-134);
    std::cout << neuron.predict(b) << "\n";
}
