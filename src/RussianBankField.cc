#include "RussianBankField.h"

using namespace RussianBank;


RussianBankField::RussianBankField() {
    using namespace std;
}


RussianBankField::~RussianBankField() {}


void RussianBankField::cardTest() {
    using namespace std;

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
