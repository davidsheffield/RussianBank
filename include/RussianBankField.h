#ifndef RUSSIANBANKFIELD_h
#define RUSSIANBANKFIELD_h

#include <iostream>

#include "Card.h"

class RussianBankField
{
public:
    RussianBankField(double num);
    void setNumber(double n);
    double getNumber() const;
    void cardTest();
private:
    double num_;
};


#include <boost/python.hpp>
using namespace boost::python;

BOOST_PYTHON_MODULE(russianbankfield)
{
    class_<RussianBankField>("RussianBankField", init<double>())
        .def("setNumber", &RussianBankField::setNumber)
        .def("getNumber", &RussianBankField::getNumber)
        .def("cardTest", &RussianBankField::cardTest)
        ;
}

#endif
