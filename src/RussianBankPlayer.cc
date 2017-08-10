#include "RussianBankPlayer.h"

using namespace std;


RussianBankPlayer::RussianBankPlayer(RussianBankField field):
    finished_(false), field_(field) {}


RussianBankPlayer::~RussianBankPlayer() {}


void RussianBankPlayer::startTurn() {
    finished_ = false;
    return;
}


string RussianBankPlayer::move() {
    string response = moveToBanks();
    if (response != "")
        return response;
    response = moveFromStock();
    if (response != "")
        return response;
    response = moveFromHand();
    if (response != "")
        return response;
    return "";
}


RussianBankField RussianBankPlayer::getField() const {
    return field_;
}


string RussianBankPlayer::moveToBanks() {
    for (int i=0; i<4; ++i) {
        for (int j=0; j<2; ++j) {
            int wanted_rank = field_.getBanks(i, j).getRank() + 1;
            for (int k=0; k<8; ++k) {
                if (field_.getTableauStack(k).size() == 0)
                    continue;
                Card card = field_.getTableauStack(k).back();
                if ((card.getRank() == 1) && field_.getBanks(i, j).isEmpty()) {
                    field_.moveCard(12 + k, 4 + i + 4 * j, 1);
                    return to_string(12 + k) + " to " + to_string(4 + i + 4 * j);
                } else if ((field_.getBanks(i, j).getSuit() == card.getSuit())
                    && (wanted_rank == card.getRank())) {
                    field_.moveCard(12 + k, 4 + i + 4 * j, 1);
                    return to_string(12 + k) + " to " + to_string(4 + i + 4 * j);
                }
            }
        }
    }
    return "";
}


string RussianBankPlayer::moveFromStock() {
    if (field_.getExposedStocksStack(1).size() == 0) {
        field_.exposeStockCard(1);
        return "0";
    }
    return "";
}


string RussianBankPlayer::moveFromHand() {
    if (field_.getHandsStack(1).size() == 0) {
        if (field_.getWastesStack(1).size() > 0) {
            field_.bigJosh(1);
            return "Big Josh";
        }
    } else {
        field_.discard(1);
        finished_ = true;
        return "end";
    }
    return "";
}


bool RussianBankPlayer::end() const {
    return finished_;
}
