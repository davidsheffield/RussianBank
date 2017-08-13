#ifndef CORE_RUSSIANBANKFIELD_h
#define CORE_RUSSIANBANKFIELD_h

#include <algorithm>
#include <boost/python.hpp>
#include <iostream>
#include <random>

#include "core/include/Card.h"

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
    Stack getTableauStack(const int) const;
    Stack getHiddenStocksStack(const int) const;
    Stack getExposedStocksStack(const int) const;
    Stack getHandsStack(const int) const;
    Stack getWastesStack(const int) const;
    int moveCard(const int, const int, const int);
    int moveCardInt(const int, const int);
    int moveCardForce(const int, const int, const int);
    int exposeStockCard(const int);
    int hideStockCard(const int);
    int discard(const int);
    int bigJosh(const int);
    int popCardSafe(const int, const int);
    int pushCardSafe(const int, const int, const Card);
    bool operator==(const RussianBankField&) const;
    bool operator!=(const RussianBankField&) const;
private:
    Card banks_[4][2];
    Stack tableau_[8];
    Stack hidden_stocks_[2];
    Stack exposed_stocks_[2];
    Stack hands_[2];
    Stack wastes_[2];
    int move_table[136][2];

    void deal(const int);
    boost::python::list stack_to_list(const Stack&) const;
    Card getTopCard(const int, const int);
    Card getStockCard(const int);
    Card getHiddenStockCard(const int);
    Card getHandCard(const int);
    Card getWasteCard(const int);
    Card getTableauCard(const int);
    void popCard(const int, const int);
    void pushCard(const int, const int, const Card);
};

#endif
