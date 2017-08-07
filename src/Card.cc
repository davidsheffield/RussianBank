#include "Card.h"


Card::Card(): rank_(0), suit_(0), deck_(false) {}


Card::Card(int rank, int suit, bool deck):
    rank_(rank), suit_(suit), deck_(deck) {}


Card::~Card(){}


int Card::getRank() const {
    return rank_;
}


int Card::getColor() const {
    return suit_ & 1;
}


int Card::getSuit() const {
    return suit_;
}


int Card::getDeck() const {
    return deck_;
}


std::string Card::getCard() const {
    using namespace std;
    string card_string = "";

    if (rank_ == 1)
        card_string = "A";
    else if (rank_ == 11)
        card_string = "J";
    else if (rank_ == 12)
        card_string = "Q";
    else if (rank_ == 13)
        card_string = "K";
    else
        card_string = to_string(rank_);

    if (suit_ == 0)
        card_string += "d";
    else if (suit_ == 1)
        card_string += "c";
    else if (suit_ == 2)
        card_string += "h";
    else
        card_string += "s";

    return card_string;
}


bool Card::isEmpty() const {
    return rank_ == 0;
}


bool Card::isPlayableTable(const Card other_card)
    const {
    if (((suit_ ^ other_card.getSuit()) & 1)
        && (rank_ + 1 == other_card.getRank()))
        return true;
    else
        return false;
}


bool Card::isPlayableOpponent(const Card other_card)
    const {
    if ((suit_ == other_card.getSuit())
        && ((rank_ + 1 == other_card.getRank())
            || (rank_ - 1 == other_card.getRank())))
        return true;
    else
        return false;
}


bool Card::isPlayableBank(const Card other_card)
    const {
    if ((suit_ == other_card.getSuit())
        && (rank_ - 1 == other_card.getRank()))
        return true;
    else
        return false;
}
