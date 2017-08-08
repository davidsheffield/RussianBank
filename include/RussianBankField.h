#ifndef RUSSIANBANKFIELD_h
#define RUSSIANBANKFIELD_h

#include <algorithm>
#include <boost/python.hpp>
#include <iostream>
#include <random>

#include "Card.h"

class RussianBankField
{
public:
    RussianBankField(const int);
    ~RussianBankField();
    Card getBanks(const int, const int) const;
    boost::python::list getTableau(const int) const;
    boost::python::list getHiddenStocks(const int) const;
    boost::python::list getExposedStocks(const int) const;
    boost::python::list getHands(const int) const;
    boost::python::list getWastes(const int) const;
    int moveCard(const int, const int, const int);
private:
    Card banks_[4][2];
    Stack tableau_[8];
    Stack hidden_stocks_[2];
    Stack exposed_stocks_[2];
    Stack hands_[2];
    Stack wastes_[2];

    void deal(const int);
    boost::python::list stack_to_list(const Stack&) const;
    Card getTopCard(const int, const int);
    Card getStockCard(const int);
    Card getHandCard(const int);
    Card getTableauCard(const int);
};


BOOST_PYTHON_MODULE(russianbank)
{
    boost::python::class_<RussianBankField>("RussianBankField",
                                            boost::python::init<int>())
        .def("getBanks", &RussianBankField::getBanks)
        .def("getTableau", &RussianBankField::getTableau)
        .def("getHiddenStocks", &RussianBankField::getHiddenStocks)
        .def("getExposedStocks", &RussianBankField::getExposedStocks)
        .def("getHands", &RussianBankField::getHands)
        .def("getWastes", &RussianBankField::getWastes)
        .def("moveCard", &RussianBankField::moveCard)
        ;
    boost::python::class_<Card>("Card")
        .def(boost::python::init<int, int, bool>())
        .def("getRank", &Card::getRank)
        .def("getColor", &Card::getColor)
        .def("getSuit", &Card::getSuit)
        .def("getDeck", &Card::getDeck)
        .def("getCard", &Card::getCard)
        .def("isEmpty", &Card::isEmpty)
        .def("notEmpty", &Card::notEmpty)
        ;
    boost::python::class_<Stack>("Stack");
}

#endif
