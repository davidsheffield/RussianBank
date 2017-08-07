#include "RussianBankField.h"

using namespace std;


RussianBankField::RussianBankField(const int seed) {
    deal(seed);
}


RussianBankField::~RussianBankField() {}


void RussianBankField::deal(const int seed) {
    // Populate decks
    Stack decks[2];
    for (int i=0; i<2; ++i) {
        for (int j=0; j<4; ++j) {
            for (int k=1; k<=13; ++k) {
                decks[i].push_back(Card(k, j, i));
            }
        }
    }

    // Shuffle
    srand(seed);
    random_shuffle(decks[0].begin(), decks[0].end());
    random_shuffle(decks[1].begin(), decks[1].end());

    for (int i=0; i<2; ++i) {
        // Deal tableau
        for (int j=0; j<4; ++j) {
            tableau_[j+4*i].push_back(decks[i][j]);
        }

        // Deal stack
        move(decks[i].begin()+4, decks[i].begin()+16,
             back_inserter(hidden_stocks_[i]));

        // Deal hand
        move(decks[i].begin()+16, decks[i].end(), back_inserter(hands_[i]));
    }

    return;
}


boost::python::list RussianBankField::stack_to_list(const Stack& stack) const {
    boost::python::object get_iter = boost::python::iterator<Stack>();
    boost::python::object iter = get_iter(stack);
    boost::python::list l(iter);
    return l;
}


Card RussianBankField::getBanks(const int i, const int j) const {
    return banks_[i][j];
}


boost::python::list RussianBankField::getTableau(const int i) const {
    return stack_to_list(tableau_[i]);
}


boost::python::list RussianBankField::getHiddenStocks(const int i) const {
    return stack_to_list(hidden_stocks_[i]);
}


boost::python::list RussianBankField::getExposedStocks(const int i) const {
    return stack_to_list(exposed_stocks_[i]);
}


boost::python::list RussianBankField::getHands(const int i) const {
    return stack_to_list(hands_[i]);
}


boost::python::list RussianBankField::getWastes(const int i) const {
    return stack_to_list(wastes_[i]);
}
