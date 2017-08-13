#include "core/include/Player.h"

using namespace std;


Player::Player(Field field):
    finished_(false), hand_in_hand_(false), field_(field) {}


Player::~Player() {}


void Player::startTurn() {
    finished_ = false;
    return;
}


string Player::move() {
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


string Player::moveToBanks() {
    for (int i=0; i<4; ++i) {
        for (int j=0; j<2; ++j) {
            int wanted_rank = field_.getBanks(i, j).getRank() + 1;
            if (field_.getExposedStocksStack(1).size() > 0) {
                Card card = field_.getExposedStocksStack(1).back();
                if ((card.getRank() == 1) && field_.getBanks(i, j).isEmpty()) {
                    field_.moveCard(0, 4 + i + 4 * j, 1);
                    return "0 to " + to_string(4 + i + 4 * j);
                } else if ((field_.getBanks(i, j).getSuit() == card.getSuit())
                           && (wanted_rank == card.getRank())) {
                    field_.moveCard(0, 4 + i + 4 * j, 1);
                    return "0 to " + to_string(4 + i + 4 * j);
                }
            }
            if (hand_in_hand_ && (field_.getHandsStack(1).size() > 0)) {
                Card card = field_.getHandsStack(1).back();
                if ((card.getRank() == 1) && field_.getBanks(i, j).isEmpty()) {
                    field_.moveCard(1, 4 + i + 4 * j, 1);
                    return "1 to " + to_string(4 + i + 4 * j);
                } else if ((field_.getBanks(i, j).getSuit() == card.getSuit())
                           && (wanted_rank == card.getRank())) {
                    field_.moveCard(1, 4 + i + 4 * j, 1);
                    return "1 to " + to_string(4 + i + 4 * j);
                }
            }
        }
    }
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


string Player::moveFromStock() {
    if (field_.getExposedStocksStack(1).size() == 0) {
        field_.exposeStockCard(1);
        return "0";
    }
    cout << endl;
    cout << endl;
    cout << endl;
    cout << "1" << endl;
    Card stock_card = field_.getExposedStocksStack(1).back();
    // Move stock card to stack in tableau
    for (int i=0; i<8; ++i) {
        if (field_.getTableauStack(i).size() > 0) {
            Card tableau_card = field_.getTableauStack(i).back();
            if (stock_card.getRank() + 1 == tableau_card.getRank()
                && stock_card.getColor() != tableau_card.getColor()) {
                field_.moveCard(0, 12 + i, 1);
                return "0 to " + to_string(12 + i);
            }
        }
    }
    // Move stock card to space in tableau
    for (int i=0; i<8; ++i) {
        if (field_.getTableauStack(i).size() == 0) {
                field_.moveCard(0, 12 + i, 1);
                return "0 to " + to_string(12 + i);
        }
    }
    return "";
}


string Player::moveFromHand() {
    if (field_.getHandsStack(1).size() == 0) {
        if (field_.getWastesStack(1).size() > 0) {
            field_.bigJosh(1);
            return "Big Josh";
        }
    } else {
        if (!hand_in_hand_) {
            hand_in_hand_ = true;
            return "1";
        } else {
            field_.discard(1);
            finished_ = true;
            hand_in_hand_ = false;
            return "end";
        }
    }
    return "";
}


Field Player::getField() const {
    return field_;
}


void Player::setField(Field field) {
    field_ = field;
    return;
}


bool Player::isHandInHand() const {
    return hand_in_hand_;
}


bool Player::end() const {
    return finished_;
}
