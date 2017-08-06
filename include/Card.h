#ifndef CARD_h
#define CARD_h

#include <string>

namespace RussianBank {
    class Card
    {
    public:
        Card(int, int, bool);
        ~Card();

        int getRank() const;
        int getColor() const;
        int getSuit() const;
        int getDeck() const;
        std::string getCard() const;
        bool isPlayableTable(const Card) const;
        bool isPlayableOpponent(const Card) const;
        bool isPlayableBank(const Card) const;

    private:
        const int rank_;
        const int suit_;
        const bool deck_;
    };
}

#endif
