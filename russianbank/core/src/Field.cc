#include "core/include/Field.h"

using namespace std;


Field::Field(const int seed) {
    deal(seed);
    for (int i=0; i<8; ++i) {
        for (int j=0; j<18; ++j) {
            if (i == j - 10)
                continue;
            move_table[i * 18 + j][0] = i + 12;
            move_table[i * 18 + j][1] = j + 2;
        }
    }
}


Field::~Field() {}


void Field::deal(const int seed) {
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


boost::python::list Field::stack_to_list(const Stack& stack) const {
    boost::python::object get_iter = boost::python::iterator<Stack>();
    boost::python::object iter = get_iter(stack);
    boost::python::list l(iter);
    return l;
}


Card Field::getBanks(const int i, const int j) const {
    return banks_[i][j];
}


boost::python::list Field::getTableau(const int i) const {
    return stack_to_list(tableau_[i]);
}


boost::python::list Field::getHiddenStocks(const int i) const {
    return stack_to_list(hidden_stocks_[i]);
}


boost::python::list Field::getExposedStocks(const int i) const {
    return stack_to_list(exposed_stocks_[i]);
}


boost::python::list Field::getHands(const int i) const {
    return stack_to_list(hands_[i]);
}


boost::python::list Field::getWastes(const int i) const {
    return stack_to_list(wastes_[i]);
}


Stack Field::getTableauStack(const int i) const {
    return tableau_[i];
}


Stack Field::getHiddenStocksStack(const int i) const {
    return hidden_stocks_[i];
}


Stack Field::getExposedStocksStack(const int i) const {
    return exposed_stocks_[i];
}


Stack Field::getHandsStack(const int i) const {
    return hands_[i];
}


Stack Field::getWastesStack(const int i) const {
    return wastes_[i];
}


Card Field::getStockCard(const int player) {
    if (exposed_stocks_[player].size() > 0)
        return exposed_stocks_[player].back();
    else
        return Card();
}


Card Field::getHiddenStockCard(const int player) {
    if (hidden_stocks_[player].size() > 0)
        return hidden_stocks_[player].back();
    else
        return Card();
}


Card Field::getHandCard(const int player) {
    if (hands_[player].size() > 0)
        return hands_[player].back();
    else
        return Card();
}


Card Field::getWasteCard(const int player) {
    if (wastes_[player].size() > 0)
        return wastes_[player].back();
    else
        return Card();
}


Card Field::getTableauCard(const int position) {
    if (tableau_[position].size() > 0)
        return tableau_[position].back();
    else
        return Card();
}


Card Field::getTopCard(const int position, const int player) {
    if (position == 0)
        return getStockCard(player);
    else if (position == 1)
        return getHandCard(player);
    else if (position == 2)
        return getStockCard((player == 0) ? 1 : 0);
    else if (position == 3)
        return getWasteCard((player == 0) ? 1 : 0);
    else if (position >= 4 && position <= 7)
        return banks_[position % 4][0];
    else if (position >= 8 && position <=11)
        return banks_[position % 4][1];
    else if (position <= 19)
        return getTableauCard(position - 12);
    else if (position == 20)
        return getHiddenStockCard(player);
    else if (position == 21)
        return getWasteCard(player);
    else if (position == 22)
        return getHiddenStockCard((player == 0) ? 1 : 0);
    else
        return getHandCard((player == 0) ? 1 : 0);
}


void Field::popCard(const int position, const int player) {
    if (position == 0)
        exposed_stocks_[player].pop_back();
    else if (position == 1)
        hands_[player].pop_back();
    else if (position == 2)
        exposed_stocks_[(player == 0) ? 1 : 0].pop_back();
    else if (position == 3)
        hands_[(player == 0) ? 1 : 0].pop_back();
    else if (position <= 7)
        banks_[position % 4][0] = Card(banks_[position % 4][0].getRank() - 1,
                                       banks_[position % 4][0].getSuit(),
                                       banks_[position % 4][0].getDeck());
    else if (position <= 11)
        banks_[position % 4][1] = Card(banks_[position % 4][1].getRank() - 1,
                                       banks_[position % 4][1].getSuit(),
                                       banks_[position % 4][1].getDeck());
    else if (position <= 19)
        tableau_[position - 12].pop_back();
    else if (position == 20)
        hidden_stocks_[player].pop_back();
    else if (position == 21)
        wastes_[player].pop_back();
    else if (position == 22)
        hidden_stocks_[(player == 0) ? 1 : 0].pop_back();
    else
        hands_[(player == 0) ? 1 : 0].pop_back();
    return;
}


void Field::pushCard(const int position, const int player,
                                const Card card) {
    if (position == 0)
        exposed_stocks_[player].push_back(card);
    else if (position == 1)
        hands_[player].push_back(card);
    else if (position == 2)
        exposed_stocks_[(player == 0) ? 1 : 0].push_back(card);
    else if (position == 3)
        wastes_[(player == 0) ? 1 : 0].push_back(card);
    else if (position <= 7)
        banks_[position % 4][0] = card;
    else if (position <= 11)
        banks_[position % 4][1] = card;
    else if (position <= 19)
        tableau_[position - 12].push_back(card);
    else if (position == 20)
        hidden_stocks_[player].push_back(card);
    else if (position == 21)
        wastes_[player].push_back(card);
    else if (position == 22)
        hidden_stocks_[(player == 0) ? 1 : 0].push_back(card);
    else
        hands_[(player == 0) ? 1 : 0].push_back(card);
}


int Field::moveCard(const int initial, const int final,
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

    if (final == 2) {
        if (playableToPlayer(initial_card, final_card)) {
            exposed_stocks_[(player == 0) ? 1 : 0].push_back(initial_card);
            popCard(initial, player);
            return 0;
        }
    } else if (final == 3) {
        if (playableToPlayer(initial_card, final_card)) {
            wastes_[(player == 0) ? 1 : 0].push_back(initial_card);
            popCard(initial, player);
            return 0;
        }
    } else if (final <= 7) {
        if (playableToBank(initial_card, final_card)) {
            banks_[final % 4][0] = initial_card;
            popCard(initial, player);
            return 0;
        }
    } else if (final <= 11) {
        if (playableToBank(initial_card, final_card)) {
            banks_[final % 4][1] = initial_card;
            popCard(initial, player);
            return 0;
        }
    } else {
        if (playableToTableau(initial_card, final_card)) {
            tableau_[final - 12].push_back(initial_card);
            popCard(initial, player);
            return 0;
        }
    }
    return 5;
}


int Field::moveCardInt(const int move, const int player) {
    if (move == 0)
        return exposeStockCard(player);
    if (move == 1) {
        if (hands_[player].size() == 0)
            return bigJosh(player);
        else
            return 0;
    }
    if (move == 2)
        return discard(player);
    if (move >= 3 && move <= 20)
        return moveCard(0, move - 1, player);
    if (move >= 21 && move <= 38)
        return moveCard(1, move - 19, player);
    if (move >= 39 && move <= 174) {
        return moveCard(move_table[move - 39][0], move_table[move - 39][1],
                        player);
    }
    return 1000;
}


int Field::moveCardForce(const int initial, const int final,
                                    const int player) {
    if (initial == final)
        return 1;
    if (initial < 0 || initial > 23 || final < 0 || final > 23)
        return 2;

    Card initial_card = getTopCard(initial, player);
    if (initial_card.isEmpty())
        return 4;

    Card final_card = getTopCard(final, player);

    pushCard(final, player, initial_card);
    popCard(initial, player);

    return 0;
}


int Field::exposeStockCard(const int player) {
    if (exposed_stocks_[player].size() > 0)
        return 1;
    if (hidden_stocks_[player].size() == 0)
        return 2;
    exposed_stocks_[player].push_back(hidden_stocks_[player].back());
    hidden_stocks_[player].pop_back();
    return 0;
}


int Field::hideStockCard(const int player) {
    if (exposed_stocks_[player].size() != 1)
        return 1;
    hidden_stocks_[player].push_back(exposed_stocks_[player].back());
    exposed_stocks_[player].pop_back();
    return 0;
}


int Field::discard(const int player) {
    if (hands_[player].size() == 0)
        return 1;
    wastes_[player].push_back(hands_[player].back());
    hands_[player].pop_back();
    return 0;
}


int Field::bigJosh(const int player) {
    if (hands_[player].size() != 0)
        return 1;
    if (wastes_[player].size() == 0)
        return 1;
    reverse(wastes_[player].begin(), wastes_[player].end());
    hands_[player] = wastes_[player];
    wastes_[player].clear();
    return 0;
}


int Field::popCardSafe(const int position, const int player) {
    if (position < 0 || position > 23)
        return 2;

    Card card = getTopCard(position, player);
    if (card.isEmpty())
        return 4;

    popCard(position, player);
    return 0;
}


int Field::pushCardSafe(const int position, const int player, const Card card) {
    if (position < 0 || position > 23)
        return 2;

    pushCard(position, player, card);
    return 0;
}


bool Field::playableToBank(const Card initial_card, const Card final_card)
    const {
    return (((initial_card.getSuit() == final_card.getSuit())
             && (initial_card.getRank() - 1 == final_card.getRank()))
            || (final_card.isEmpty() && initial_card.getRank() == 1));
}


bool Field::playableToPlayer(const Card initial_card, const Card final_card)
    const {
    return (final_card.notEmpty()
            && (initial_card.getSuit() == final_card.getSuit())
            && ((initial_card.getRank() + 1 == final_card.getRank())
                || (initial_card.getRank() - 1 == final_card.getRank())));
}


bool Field::playableToTableau(const Card initial_card, const Card final_card)
    const {
    return ((((initial_card.getSuit() ^ final_card.getSuit()) & 1)
             && (initial_card.getRank() + 1 == final_card.getRank()))
            || final_card.isEmpty());
}


bool Field::operator==(const Field &rhs) const {
    for (int i=0; i<4; ++i) {
        for (int j=0; j<2; ++j) {
            if (banks_[i][j] != getBanks(i, j))
                return false;
        }
    }
    for (int i=0; i<8; ++i) {
        if (tableau_[i] != getTableau(i))
            return false;
    }
    for (int i=0; i<2; ++i) {
        if ((hidden_stocks_[i] != getHiddenStocks(i))
            || (exposed_stocks_[i] != getExposedStocks(i))
            || (hands_[i] != getHands(i))
            || (wastes_[i] != getWastes(i)))
            return false;
    }
    return true;
}


bool Field::operator!=(const Field &rhs) const {
    return !(*this == rhs);
}
