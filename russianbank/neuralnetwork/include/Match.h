#ifndef NEURALNETWORK_MATCH_h
#define NEURALNETWORK_MATCH_h

#include <boost/python.hpp>

#include "core/include/Field.h"
#include "neuralnetwork/include/NeuralNetwork.h"


class Match
{
public:
    Match(NeuralNetwork, NeuralNetwork, const int);
    ~Match();
    void setMaxTurns(const uint);
    void setMaxMoves(const uint);
    double getPoints(const int) const;
    void play();
private:
    NeuralNetwork players_[2];
    Field field_;
    double points_[2];
    double points_table_[175];
    uint max_turns_ = 100;
    uint max_moves_ = 100;
};


BOOST_PYTHON_MODULE(match)
{
    boost::python::class_<Match>("Match", boost::python::init<NeuralNetwork, NeuralNetwork, int>())
        .def("setMaxTurns", &Match::setMaxTurns)
        .def("setMaxMoves", &Match::setMaxMoves)
        .def("getPoints", &Match::getPoints)
        .def("play", &Match::play)
        ;
}

#endif
