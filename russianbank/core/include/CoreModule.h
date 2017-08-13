#ifndef CORE_COREMODULE_h
#define CORE_COREMODULE_h

#include <boost/python.hpp>

#include "core/include/Card.h"
#include "core/include/RussianBankField.h"
#include "core/include/RussianBankPlayer.h"


BOOST_PYTHON_MODULE(core_module)
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
        .def("moveCardInt", &RussianBankField::moveCardInt)
        .def("moveCardForce", &RussianBankField::moveCardForce)
        .def("exposeStockCard", &RussianBankField::exposeStockCard)
        .def("hideStockCard", &RussianBankField::hideStockCard)
        .def("discard", &RussianBankField::discard)
        .def("bigJosh", &RussianBankField::bigJosh)
        .def("popCard", &RussianBankField::popCardSafe)
        .def("pushCard", &RussianBankField::pushCardSafe)
        .def("__eq__", &RussianBankField::operator==)
        .def("__ne__", &RussianBankField::operator!=)
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
        .def("isSame", &Card::isSame)
        .def("notSame", &Card::notSame)
        .def("__eq__", &Card::operator==)
        .def("__ne__", &Card::operator!=)
        .def("__repr__", &Card::getCard)
        ;
    boost::python::class_<Stack>("Stack");
    boost::python::class_<RussianBankPlayer>("RussianBankPlayer",
                                             boost::python::init<RussianBankField>())
        .def("startTurn", &RussianBankPlayer::startTurn)
        .def("move", &RussianBankPlayer::move)
        .def("getField", &RussianBankPlayer::getField)
        .def("setField", &RussianBankPlayer::setField)
        .def("isHandInHand", &RussianBankPlayer::isHandInHand)
        .def("end", &RussianBankPlayer::end)
        ;
}

#endif