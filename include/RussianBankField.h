#ifndef RUSSIANBANKFIELD_h
#define RUSSIANBANKFIELD_h

#include <algorithm>
#include <iostream>

#include "Card.h"

class RussianBankField
{
public:
    RussianBankField(const int);
    ~RussianBankField();
private:
    Card banks_[4][2];
    Stack tableau_[8];
    Stack hidden_stocks_[2];
    Stack exposed_stocks_[2];
    Stack hands_[2];
    Stack wastes_[2];

    void deal(const int);
};


#include <boost/python.hpp>
using namespace boost::python;

BOOST_PYTHON_MODULE(russianbank)
{
    class_<RussianBankField>("RussianBankField", init<int>());
    class_<Card>("Card")
        .def(init<int, int, bool>())
        .def("getRank", &Card::getRank)
        .def("getColor", &Card::getColor)
        .def("getSuit", &Card::getSuit)
        .def("getDeck", &Card::getDeck)
        .def("getCard", &Card::getCard)
        ;
}

#endif
