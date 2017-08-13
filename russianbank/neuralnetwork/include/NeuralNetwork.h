#ifndef NEURALNETWORK_NEURALNETWORK_h
#define NEURALNETWORK_NEURALNETWORK_h

#include <boost/python.hpp>
#include <cmath>
#include <iostream>
#include <random>
#include <vector>

#include "core/include/Field.h"

#define kINPUTS 294
#define kOUTPUTS 175


class NeuralNetwork
{
public:
    NeuralNetwork(const boost::python::list&);
    ~NeuralNetwork();
    void setRandomWeights();
    boost::python::list getWeights() const;
    void setInput(const Field, const int, const bool);
    void feedforward();
    boost::python::list getOutput() const;
    int getMove() const;
private:
    uint num_layers_;
    std::vector<int> num_layer_neurons_;
    std::vector<std::vector<std::vector<double>>> weights_;
    std::vector<std::vector<double>> layers_;
};


BOOST_PYTHON_MODULE(network)
{
    boost::python::class_<NeuralNetwork>("NeuralNetwork",
                                         boost::python::init<boost::python::list&>())
        .def("setRandomWeights", &NeuralNetwork::setRandomWeights)
        .def("getWeights", &NeuralNetwork::getWeights)
        .def("setInput", &NeuralNetwork::setInput)
        .def("feedforward", &NeuralNetwork::feedforward)
        .def("getOutput", &NeuralNetwork::getOutput)
        .def("getMove", &NeuralNetwork::getMove)
        ;
    boost::python::class_<std::vector<double>>("vector_double");
}

#endif