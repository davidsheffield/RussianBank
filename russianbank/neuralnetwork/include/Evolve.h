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
    ~Evolve();
    void playMatches();
    void breed();
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
        .def("playMatches", &Evolve::playMatches)
        .def("breed", &Evolve::breed)
        ;
}

#endif
