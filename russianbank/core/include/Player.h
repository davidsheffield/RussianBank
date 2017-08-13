#ifndef CORE_PLAYER_h
#define CORE_PLAYER_h

#include <iostream>

#include "core/include/Field.h"


class Player
{
public:
    Player(Field);
    ~Player();
    void startTurn();
    std::string move();
    Field getField() const;
    void setField(Field);
    bool isHandInHand() const;
    bool end() const;
private:
    bool finished_;
    bool hand_in_hand_;
    Field field_;
    std::string moveToBanks();
    std::string moveFromStock();
    std::string moveFromHand();
};

#endif
