#ifndef CARD_h
#define CARD_h

#include <string>
#include <vector>


class Card
{
public:
    Card();
    Card(int, int, bool);
    ~Card();

    int getRank() const;
    int getColor() const;
    int getSuit() const;
    int getDeck() const;
    std::string getCard() const;
    bool isEmpty() const;
    bool notEmpty() const;
    bool isPlayableTable(const Card) const;
    bool isPlayableOpponent(const Card) const;
    bool isPlayableBank(const Card) const;
    bool isSame(const Card&) const;
    bool notSame(const Card&) const;
    bool operator==(const Card&) const;
    bool operator!=(const Card&) const;
private:
    int rank_;
    int suit_;
    bool deck_;
};

typedef std::vector<Card> Stack;

#endif
