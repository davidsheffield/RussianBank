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
    shuffle(decks[0].begin(), decks[0].end(), default_random_engine(seed));
    shuffle(decks[1].begin(), decks[1].end(), default_random_engine(seed+1));

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


Card RussianBankField::getStockCard(const int player) {
    if (exposed_stocks_[player].size() > 0)
        return exposed_stocks_[player].back();
    else if (hidden_stocks_[player].size() > 0)
        return hidden_stocks_[player].back();
    else
        return Card();
}


Card RussianBankField::getHandCard(const int player) {
    if (hands_[player].size() > 0)
        return hands_[player].back();
    else
        return Card();
}


Card RussianBankField::getTableauCard(const int position) {
    if (tableau_[position].size() > 0)
        return tableau_[position].back();
    else
        return Card();
}


Card RussianBankField::getTopCard(const int position, const int player) {
    if (position == 0)
        return getStockCard(player);
    else if (position == 1)
        return getHandCard(player);
    else if (position == 2)
        return getStockCard((player == 0) ? 1 : 0);
    else if (position == 3)
        return getHandCard((player == 0) ? 1 : 0);
    else if (position >= 4 && position <= 7)
        return banks_[position % 4][0];
    else if (position >= 8 && position <=11)
        return banks_[position % 4][1];
    else
        return getTableauCard(position - 12);
}


int RussianBankField::moveCard(const int initial, const int final,
                               const int player) {
    if (initial == final)
        return 1;
    if (initial < 0 || initial > 19 || final < 0 || final > 19)
        return 2;
    if (initial >= 2 && initial <= 11)
        return 3;
    if (final <= 1)
        return 3;

    Card initial_card = getTopCard(initial, player);
    if (initial_card.isEmpty())
        return 4;

    Card final_card = getTopCard(final, player);

    if (final <= 3) { // 0 and 1 already excluded
        if ((initial_card.getSuit() == final_card.getSuit())
            && ((initial_card.getRank() + 1 == final_card.getRank())
                || (initial_card.getRank() - 1 == final_card.getRank()))) {
            return 0;
        }
    } else if (final <= 11) {
        if ((initial_card.getSuit() == final_card.getSuit())
            && (initial_card.getRank() - 1 == final_card.getRank())) {
            return 0;
        }
    } else {
        if (((initial_card.getSuit() ^ final_card.getSuit()) & 1)
            && (initial_card.getRank() + 1 == final_card.getRank())) {
            return 0;
        }
    }
    return 5;
}
