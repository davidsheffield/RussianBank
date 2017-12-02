#ifndef CORE_COREMODULE_h
#define CORE_COREMODULE_h

#include <boost/python.hpp>

#include "core/include/Card.h"
#include "core/include/Field.h"
#include "core/include/Player.h"


BOOST_PYTHON_MODULE(core_module)
{
    boost::python::class_<Field>("Field", boost::python::init<int>())
        .def("get_banks", &Field::getBanks)
        .def("get_tableau", &Field::getTableau)
        .def("get_hidden_stocks", &Field::getHiddenStocks)
        .def("get_exposed_stocks", &Field::getExposedStocks)
        .def("get_hands", &Field::getHands)
        .def("get_wastes", &Field::getWastes)
        .def("move_card", &Field::moveCard)
        .def("move_card_int", &Field::moveCardInt)
        .def("move_card_force", &Field::moveCardForce)
        .def("expose_stock_card", &Field::exposeStockCard)
        .def("hide_stock_card", &Field::hideStockCard)
        .def("discard", &Field::discard)
        .def("big_Josh", &Field::bigJosh)
        .def("pop_card", &Field::popCardSafe)
        .def("push_card", &Field::pushCardSafe)
        .def("playable_to_bank", &Field::playableToBank)
        .def("playable_to_player", &Field::playableToPlayer)
        .def("playable_to_tableau", &Field::playableToTableau)
        .def("__eq__", &Field::operator==)
        .def("__ne__", &Field::operator!=)
        ;
    boost::python::class_<Card>("Card")
        .def(boost::python::init<int, int, bool>())
        .def("get_rank", &Card::getRank)
        .def("get_color", &Card::getColor)
        .def("get_suit", &Card::getSuit)
        .def("get_deck", &Card::getDeck)
        .def("get_card", &Card::getCard)
        .def("is_empty", &Card::isEmpty)
        .def("not_empty", &Card::notEmpty)
        .def("is_same", &Card::isSame)
        .def("not_same", &Card::notSame)
        .def("__eq__", &Card::operator==)
        .def("__ne__", &Card::operator!=)
        .def("__repr__", &Card::getCard)
        ;
    boost::python::class_<Stack>("Stack");
    boost::python::class_<Player>("Player", boost::python::init<Field>())
        .def("start_turn", &Player::startTurn)
        .def("move", &Player::move)
        .def("get_field", &Player::getField)
        .def("set_field", &Player::setField)
        .def("is_hand_in_hand", &Player::isHandInHand)
        .def("end", &Player::end)
        ;
}

#endif
