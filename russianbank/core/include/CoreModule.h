#ifndef CORE_COREMODULE_h
#define CORE_COREMODULE_h

#include <boost/python.hpp>

#include "core/include/Card.h"
#include "core/include/Field.h"
#include "core/include/Player.h"


BOOST_PYTHON_MODULE(core_module)
{
    boost::python::class_<Field>("Field", boost::python::init<int>())
        .def("getBanks", &Field::getBanks)
        .def("getTableau", &Field::getTableau)
        .def("getHiddenStocks", &Field::getHiddenStocks)
        .def("getExposedStocks", &Field::getExposedStocks)
        .def("getHands", &Field::getHands)
        .def("getWastes", &Field::getWastes)
        .def("moveCard", &Field::moveCard)
        .def("moveCardInt", &Field::moveCardInt)
        .def("moveCardForce", &Field::moveCardForce)
        .def("exposeStockCard", &Field::exposeStockCard)
        .def("hideStockCard", &Field::hideStockCard)
        .def("discard", &Field::discard)
        .def("bigJosh", &Field::bigJosh)
        .def("popCard", &Field::popCardSafe)
        .def("pushCard", &Field::pushCardSafe)
        .def("__eq__", &Field::operator==)
        .def("__ne__", &Field::operator!=)
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
    boost::python::class_<Player>("Player", boost::python::init<Field>())
        .def("startTurn", &Player::startTurn)
        .def("move", &Player::move)
        .def("getField", &Player::getField)
        .def("setField", &Player::setField)
        .def("isHandInHand", &Player::isHandInHand)
        .def("end", &Player::end)
        ;
}

#endif
