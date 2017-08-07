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
    void cardTest();
private:
    RussianBank::Card banks_[4][2];
    RussianBank::Stack tableau_[8];
    RussianBank::Stack hidden_stocks_[2];
    RussianBank::Stack exposed_stocks_[2];
    RussianBank::Stack hands_[2];
    RussianBank::Stack wastes_[2];

    void deal(const int);
};


#include <boost/python.hpp>
using namespace boost::python;

BOOST_PYTHON_MODULE(russianbank)
{
    class_<RussianBankField>("RussianBankField", init<int>())
        .def("cardTest", &RussianBankField::cardTest)
        ;
    class_<RussianBank::Card>("Card")
        .def(init<int, int, bool>())
        .def("getRank", &RussianBank::Card::getRank)
        .def("getColor", &RussianBank::Card::getColor)
        .def("getSuit", &RussianBank::Card::getSuit)
        .def("getDeck", &RussianBank::Card::getDeck)
        .def("getCard", &RussianBank::Card::getCard)
        ;
}

#endif
