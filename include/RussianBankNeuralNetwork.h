#ifndef RUSSIANBANKNEURALNETWORK_h
#define RUSSIANBANKNEURALNETWORK_h

#include <boost/python.hpp>
#include <cmath>
#include <iostream>
#include <vector>

#define kINPUTS 146
#define kOUTPUTS 106
class RussianBankNeuralNetwork
{
public:
    RussianBankNeuralNetwork(const boost::python::list&);
    ~RussianBankNeuralNetwork();
    boost::python::list getOutput(const boost::python::list&);
private:
    int num_layers_;
    std::vector<int> num_layer_neurons_;
    std::vector<std::vector<double>> weights_;
    std::vector<std::vector<double>> layers_;
};

#endif
