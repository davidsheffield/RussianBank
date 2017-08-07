#ifndef RUSSIANBANKFIELD_h
#define RUSSIANBANKFIELD_h

#include <iostream>

#include "Card.h"

class RussianBankField
{
public:
    RussianBankField();
    ~RussianBankField();
    void cardTest();
private:
    RussianBank::Card banks_[4][2];
    RussianBank::Stack tableau_[8];
    RussianBank::Stack hidden_stocks_[2];
    RussianBank::Stack exposed_stocks_[2];
    RussianBank::Stack hands_[2];
    RussianBank::Stack wastes_[2];
};


#include <boost/python.hpp>
using namespace boost::python;

BOOST_PYTHON_MODULE(russianbankfield)
{
    class_<RussianBankField>("RussianBankField")
        .def("cardTest", &RussianBankField::cardTest)
        ;
}

#endif
