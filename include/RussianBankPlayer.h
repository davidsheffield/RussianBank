#ifndef RUSSIANBANKPLAYER_h
#define RUSSIANBANKPLAYER_h

#include <iostream>

#include "RussianBankField.h"


class RussianBankPlayer
{
public:
    RussianBankPlayer(RussianBankField);
    ~RussianBankPlayer();
    void startTurn();
    std::string move();
    RussianBankField getField() const;
    void setField(RussianBankField);
    bool isHandInHand() const;
    bool end() const;
private:
    bool finished_;
    bool hand_in_hand_;
    RussianBankField field_;
    std::string moveToBanks();
    std::string moveFromStock();
    std::string moveFromHand();
};

#endif
