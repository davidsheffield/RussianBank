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


typedef std::vector<std::vector<std::vector<double>>> WeightsContainer;
typedef std::vector<std::vector<double>> Matrix;

class NeuralNetwork
{
public:
    NeuralNetwork(const std::vector<int>);
    NeuralNetwork(const boost::python::list&);
    ~NeuralNetwork();
    void setRandomWeights();
    int setWeights(const WeightsContainer);
    int setWeightsList(const boost::python::list&);
    WeightsContainer getWeights() const;
    boost::python::list getWeightsList() const;
    void setInput(const Field, const int, const bool);
    void feedforward();
    boost::python::list getOutput() const;
    int getMove() const;
private:
    uint num_layers_;
    std::vector<int> num_layer_neurons_;
    WeightsContainer weights_;
    Matrix layers_;
};


BOOST_PYTHON_MODULE(network)
{
    boost::python::class_<NeuralNetwork>("NeuralNetwork",
                                         boost::python::init<boost::python::list&>())
        .def("setRandomWeights", &NeuralNetwork::setRandomWeights)
        .def("setWeights", &NeuralNetwork::setWeightsList)
        .def("getWeights", &NeuralNetwork::getWeightsList)
        .def("setInput", &NeuralNetwork::setInput)
        .def("feedforward", &NeuralNetwork::feedforward)
        .def("getOutput", &NeuralNetwork::getOutput)
        .def("getMove", &NeuralNetwork::getMove)
        ;
    boost::python::class_<std::vector<double>>("vector_double");
}

#endif
