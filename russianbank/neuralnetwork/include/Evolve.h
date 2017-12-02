#ifndef NEURALNETWORK_EVOLVE_h
#define NEURALNETWORK_EVOLVE_h

#include <algorithm>
#include <boost/python.hpp>
#include <iostream>
#include <random>
#include <utility>
#include <vector>

#include "neuralnetwork/include/Match.h"
#include "neuralnetwork/include/NeuralNetwork.h"


typedef std::vector<std::pair<NeuralNetwork, double>> Nets;


class Evolve
{
public:
    Evolve();
    Evolve(const boost::python::list&);
    ~Evolve();
    void playMatches();
    void breed();
    std::vector<NeuralNetwork> getNeuralNetworks() const;
    boost::python::list getNeuralNetworksList() const;
    std::vector<double> getPoints() const;
    boost::python::list getPointsList() const;
    void sortNeuralNetworks();
private:
    int num_nets_;
    Nets nets_;
    int num_keep_ = 2;
    static bool sortNets(const std::pair<NeuralNetwork, double>,
                         const std::pair<NeuralNetwork, double>);
};


BOOST_PYTHON_MODULE(evolve)
{
    boost::python::class_<Evolve>("Evolve")
        .def(boost::python::init<boost::python::list&>())
        .def("play_matches", &Evolve::playMatches)
        .def("breed", &Evolve::breed)
        .def("get_neural_networks", &Evolve::getNeuralNetworksList)
        .def("get_points", &Evolve::getPointsList)
        .def("sort", &Evolve::sortNeuralNetworks)
        ;
}

#endif
