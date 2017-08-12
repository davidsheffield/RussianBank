#include "RussianBankNeuralNetwork.h"

using namespace std;


RussianBankNeuralNetwork::RussianBankNeuralNetwork(
    const boost::python::list &num_hidden_neurons) {
    num_layers_ = 2 + len(num_hidden_neurons);
    num_layer_neurons_.push_back(kINPUTS);
    for (int i=0; i<len(num_hidden_neurons); ++i) {
        num_layer_neurons_.push_back(boost::python::extract<int>(
                                         num_hidden_neurons[i]));
    }
    num_layer_neurons_.push_back(kOUTPUTS);

    for (uint i=0; i<num_layers_; ++i) {
        vector<double> weights;
        for (int j=0; j<num_layer_neurons_[i]+1; ++j) {
            weights.push_back(0.0);
        }
        weights_.push_back(weights);
    }
}


RussianBankNeuralNetwork::~RussianBankNeuralNetwork() {}


void RussianBankNeuralNetwork::setInput(const RussianBankField field,
                                        const int player,
                                        const bool hand_in_hand) {
    layers_.clear();
    vector<double> layer;
    for (int i=0; i<4; ++i) {
        for (int j=0; j<2; ++j) {
            layer.push_back(static_cast<double>(field.getBanks(i, j).getRank()));
            if (field.getBanks(i, j).getRank() == 0)
                layer.push_back(-1.0);
            else
                layer.push_back(static_cast<double>(
                                    field.getBanks(i, j).getSuit()));
        }
    }
    for (int i=0; i<8; ++i) {
        Stack stack = field.getTableauStack(i);
        for (Stack::iterator it=stack.end(); it!=stack.begin(); --it) {
            layer.push_back(static_cast<double>(it->getRank()));
            layer.push_back(static_cast<double>(it->getSuit()));
        }
        for (uint j=0; j<12-stack.size(); ++j) {
            layer.push_back(0.0);
            layer.push_back(-1.0);
        }
    }
    for (int i=0; i<2; ++i) {
        int which_player = (i == 0) ? player : 1 ^ player;

        Stack stack = field.getExposedStocksStack(which_player);
        for (Stack::iterator it=stack.end(); it!=stack.begin(); --it) {
            layer.push_back(static_cast<double>(it->getRank()));
            layer.push_back(static_cast<double>(it->getSuit()));
        }
        for (uint j=0; j<20-stack.size(); ++j) {
            layer.push_back(0.0);
            layer.push_back(-1.0);
        }
        stack = field.getWastesStack(which_player);
        if (stack.size() > 0) {
            Card card = stack.back();
            layer.push_back(static_cast<double>(card.getRank()));
            layer.push_back(static_cast<double>(card.getSuit()));
        } else {
            layer.push_back(0.0);
            layer.push_back(-1.0);
        }
    }
    if (hand_in_hand) {
        Stack stack = field.getHandsStack(player);
        if (stack.size() > 0) {
            Card card = stack.back();
            layer.push_back(static_cast<double>(card.getRank()));
            layer.push_back(static_cast<double>(card.getSuit()));
        }
    } else {
        layer.push_back(0.0);
        layer.push_back(-1.0);
    }
    layers_.push_back(layer);
    cout << "layer dimension " << layer.size() << endl;
    return;
}


void RussianBankNeuralNetwork::feedforward() {
    // Loop over layers
    for (uint i=0; i<num_layers_-1; ++i) {
        vector<double> layer;
        if (i < num_layers_ - 2)
            layer.push_back(1.0);
        // Loop over layer's neurons
        for (int j=0; j<num_layer_neurons_[i+1]; ++j) {
            double value = 0.0;
            // Loop over last layer's neurons
            for (int k=0; k<num_layer_neurons_[i]+1; ++k) {
                value += layers_[i][k] * weights_[i][k];
            }
            layer.push_back(tanh(value));
        }
        layers_.push_back(layer);
    }
    return;
}


boost::python::list RussianBankNeuralNetwork::getOutput() const {
    // Convert vector to Python list
    boost::python::object get_iter = boost::python::iterator<vector<double>>();
    boost::python::object iter = get_iter(&layers_.back());
    boost::python::list l(iter);
    return l;
}

int RussianBankNeuralNetwork::getMove() const {
    int move = -1;
    if (layers_.size() != num_layers_)
        return move;
    vector<double> output = layers_.back();
    int counter = 0;
    double maximum_value = -9999.0;
    for (vector<double>::iterator it=output.begin(); it!=output.end(); ++it) {
        if (*it > maximum_value) {
            maximum_value = *it;
            move = counter;
        }
        ++counter;
    }
    return move;
}
