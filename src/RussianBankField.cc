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
