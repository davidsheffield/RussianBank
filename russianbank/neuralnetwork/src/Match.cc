#include "neuralnetwork/include/Match.h"


Match::Match(NeuralNetwork player0, NeuralNetwork player1, const int seed):
    players_{player0, player1},
    field_(Field(seed)),
    points_{0.0, 0.0},
    points_table_{3.0, // Expose stock card
            1.0, // Turn over waste
            1.0, // End turn
            // Move card from stock
            3.0, 3.0, 3.0, 3.0, 3.0, 3.0, 3.0, 3.0, 3.0, 3.0, 3.0, 3.0, 3.0,
            3.0, 3.0, 3.0, 3.0, 3.0,
            // Move card from hand
            2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0,
            2.0, 2.0, 2.0, 2.0, 2.0,
            // Move card from tableau
            2.0, 2.0, 10.0, 10.0, 10.0, 10.0, 10.0, 10.0, 10.0, 10.0, 1.0, 1.0,
            1.0, 1.0, 1.0, 1.0, 1.0,
            2.0, 2.0, 10.0, 10.0, 10.0, 10.0, 10.0, 10.0, 10.0, 10.0, 1.0, 1.0,
            1.0, 1.0, 1.0, 1.0, 1.0,
            2.0, 2.0, 10.0, 10.0, 10.0, 10.0, 10.0, 10.0, 10.0, 10.0, 1.0, 1.0,
            1.0, 1.0, 1.0, 1.0, 1.0,
            2.0, 2.0, 10.0, 10.0, 10.0, 10.0, 10.0, 10.0, 10.0, 10.0, 1.0, 1.0,
            1.0, 1.0, 1.0, 1.0, 1.0,
            2.0, 2.0, 10.0, 10.0, 10.0, 10.0, 10.0, 10.0, 10.0, 10.0, 1.0, 1.0,
            1.0, 1.0, 1.0, 1.0, 1.0,
            2.0, 2.0, 10.0, 10.0, 10.0, 10.0, 10.0, 10.0, 10.0, 10.0, 1.0, 1.0,
            1.0, 1.0, 1.0, 1.0, 1.0,
            2.0, 2.0, 10.0, 10.0, 10.0, 10.0, 10.0, 10.0, 10.0, 10.0, 1.0, 1.0,
            1.0, 1.0, 1.0, 1.0, 1.0,
            2.0, 2.0, 10.0, 10.0, 10.0, 10.0, 10.0, 10.0, 10.0, 10.0, 1.0, 1.0,
            1.0, 1.0, 1.0, 1.0, 1.0} {}


Match::~Match() {}


void Match::setMaxTurns(const uint turns) {
    max_turns_ = turns;
}


void Match::setMaxMoves(const uint moves) {
    max_moves_ = moves;
}


double Match::getPoints(const int player) const {
    return points_[player];
}


void Match::play() {
    uint turn = 0;
    int player = 0;
    bool hand_in_hand = false;
    int winner = 2;
    while (turn < max_turns_ && winner == 2) {
        uint move_counter = 0;
        while (move_counter < max_moves_ && winner == 2) {
            players_[player].setInput(field_, player, hand_in_hand);
            players_[player].feedforward();
            int move = players_[player].getMove();
            int response = field_.moveCardInt(move, player);
            if (response == 0)
                points_[player] += points_table_[move];
            else
                --points_[player];
            ++move_counter;
            if (move == 2)
                break;
            if (field_.getExposedStocksStack(player).size()
                + field_.getHiddenStocksStack(player).size()
                + field_.getHandsStack(player).size()
                + field_.getWastesStack(player).size() == 0)
                winner = player;
        }
        ++turn;
        player = 1 ^ player;
    }

    if (winner != 2) {
        int opponent = 1 ^ winner;
        double end_game_points = 30.0 + static_cast<double>(
            field_.getExposedStocksStack(opponent).size()
            + field_.getHiddenStocksStack(opponent).size()
            + field_.getHandsStack(opponent).size()
            + field_.getWastesStack(opponent).size());
        points_[winner] += end_game_points;
        points_[opponent] -= end_game_points;
    }
    return;
}
