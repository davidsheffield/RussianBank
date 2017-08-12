#ifndef RUSSIANBANKNEURALNETWORK_h
#define RUSSIANBANKNEURALNETWORK_h

#include <boost/python.hpp>
#include <cmath>
#include <iostream>
#include <vector>

#include "RussianBankField.h"

#define kINPUTS 294
#define kOUTPUTS 106


class RussianBankNeuralNetwork
{
public:
    RussianBankNeuralNetwork(const boost::python::list&);
    ~RussianBankNeuralNetwork();
    void setInput(const RussianBankField, const int, const bool);
    void feedforward();
    boost::python::list getOutput() const;
    int getMove() const;
private:
    uint num_layers_;
    std::vector<int> num_layer_neurons_;
    std::vector<std::vector<double>> weights_;
    std::vector<std::vector<double>> layers_;
};

#endif
