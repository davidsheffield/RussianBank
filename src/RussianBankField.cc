#include "RussianBankField.h"

using namespace RussianBank;
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

    for (uint i=0; i<decks[0].size(); ++i) {
        cout << decks[0][i].getCard() << " ";
    }
    cout << endl;
    for (int i=0; i<2; ++i) {
        // Deal tableau
        for (int j=0; j<4; ++j) {
            tableau_[j].push_back(decks[i][j]);
        }

        // Deal stack
        move(decks[i].begin()+4, decks[i].begin()+16,
             back_inserter(hidden_stocks_[i]));

        // Deal hand
        move(decks[i].begin()+16, decks[i].end(), back_inserter(hands_[i]));
    }

    return;
}


void RussianBankField::cardTest() {
    Card card1(1, 0, false);
    Card card2(2, 1, true);
    Card card3(3, 2, true);
    Card card4(11, 3, false);

    cout << "Rank  " << card1.getRank() << " " << card2.getRank() << " "
         << card3.getRank()  << " " << card4.getRank()  << endl;
    cout << "Suit  " << card1.getSuit() << " " << card2.getSuit() << " "
         << card3.getSuit()  << " " << card4.getSuit()  << endl;
    cout << "Color " << card1.getColor() << " " << card2.getColor() << " "
         << card3.getColor()  << " " << card4.getColor()  << endl;
    cout << "Deck  " << card1.getDeck() << " " << card2.getDeck() << " "
         << card3.getDeck()  << " " << card4.getDeck()  << endl;
    cout << "Card  " << card1.getCard() << " " << card2.getCard() << " "
         << card3.getCard() << " " << card4.getCard() << endl;
    cout << endl;
    cout << "Is playable on the table " << card1.isPlayableTable(card2) << " "
         << card2.isPlayableTable(card3) << " " << card3.isPlayableTable(card4)
         << " " << card4.isPlayableTable(card1) << endl;
    cout << "Is playable on the opponent " << card1.isPlayableOpponent(card2)
         << " " << card2.isPlayableOpponent(card3) << " "
         << card3.isPlayableOpponent(card4) << " "
         << card4.isPlayableOpponent(card1) << endl;
    cout << "Is playable on the bank " << card1.isPlayableBank(card2) << " "
         << card2.isPlayableBank(card3) << " " << card3.isPlayableBank(card4)
         << " " << card4.isPlayableBank(card1) << endl;
    return;
}
