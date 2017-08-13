#ifndef NEURALNETWORK_RUSSIANBANKNEURALNETWORK_h
#define NEURALNETWORK_RUSSIANBANKNEURALNETWORK_h

#include <boost/python.hpp>
#include <cmath>
#include <iostream>
#include <random>
#include <vector>

#include "core/include/RussianBankField.h"

#define kINPUTS 294
#define kOUTPUTS 175


class RussianBankNeuralNetwork
{
public:
    RussianBankNeuralNetwork(const boost::python::list&);
    ~RussianBankNeuralNetwork();
    void setRandomWeights();
    boost::python::list getWeights() const;
    void setInput(const RussianBankField, const int, const bool);
    void feedforward();
    boost::python::list getOutput() const;
    int getMove() const;
private:
    uint num_layers_;
    std::vector<int> num_layer_neurons_;
    std::vector<std::vector<std::vector<double>>> weights_;
    std::vector<std::vector<double>> layers_;
};
#endif

BOOST_PYTHON_MODULE(network)
{
    boost::python::class_<RussianBankNeuralNetwork>("RussianBankNeuralNetwork",
                                                    boost::python::init<boost::python::list&>())
        .def("setRandomWeights", &RussianBankNeuralNetwork::setRandomWeights)
        .def("getWeights", &RussianBankNeuralNetwork::getWeights)
        .def("setInput", &RussianBankNeuralNetwork::setInput)
        .def("feedforward", &RussianBankNeuralNetwork::feedforward)
        .def("getOutput", &RussianBankNeuralNetwork::getOutput)
        .def("getMove", &RussianBankNeuralNetwork::getMove)
        ;
    boost::python::class_<std::vector<double>>("vector_double");
}
