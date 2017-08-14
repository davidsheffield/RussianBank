#include "neuralnetwork/include/NeuralNetwork.h"

using namespace std;


NeuralNetwork::NeuralNetwork(const vector<int> num_hidden_neurons) {
    num_layers_ = 2 + num_hidden_neurons.size();
    num_layer_neurons_.push_back(kINPUTS);
    for (vector<int>::const_iterator it=num_hidden_neurons.begin();
         it!=num_hidden_neurons.end(); ++it) {
        num_layer_neurons_.push_back(*it);
    }
    num_layer_neurons_.push_back(kOUTPUTS);

    // Loop over layers
    for (uint i=1; i<num_layers_; ++i) {
        Matrix weights;
        // Loop over layer's neurons
        for (int j=0; j<num_layer_neurons_[i]; ++j) {
            vector<double> w;
            // Loop over last layer's neurons
            for (int k=0; k<num_layer_neurons_[i-1]+1; ++k) {
                w.push_back(0.0);
            }
            weights.push_back(w);
        }
        weights_.push_back(weights);
    }
}


NeuralNetwork::NeuralNetwork(const boost::python::list &num_hidden_neurons) {
    num_layers_ = 2 + len(num_hidden_neurons);
    num_layer_neurons_.push_back(kINPUTS);
    for (int i=0; i<len(num_hidden_neurons); ++i) {
        num_layer_neurons_.push_back(boost::python::extract<int>(
                                         num_hidden_neurons[i]));
    }
    num_layer_neurons_.push_back(kOUTPUTS);

    // Loop over layers
    for (uint i=1; i<num_layers_; ++i) {
        Matrix weights;
        // Loop over layer's neurons
        for (int j=0; j<num_layer_neurons_[i]; ++j) {
            vector<double> w;
            // Loop over last layer's neurons
            for (int k=0; k<num_layer_neurons_[i-1]+1; ++k) {
                w.push_back(0.0);
            }
            weights.push_back(w);
        }
        weights_.push_back(weights);
    }
}


NeuralNetwork::~NeuralNetwork() {}


void NeuralNetwork::setRandomWeights() {
    default_random_engine generator(time(0));
    uniform_real_distribution<double> distribution(-1.0, 1.0);
    // Loop over layers
    for (uint i=1; i<num_layers_; ++i) {
        // Loop over layer's neurons
        for (int j=0; j<num_layer_neurons_[i]; ++j) {
            // Loop over last layer's neurons
            for (int k=0; k<num_layer_neurons_[i-1]+1; ++k) {
                weights_[i-1][j][k] = distribution(generator);
            }
        }
    }
    return;
}


int NeuralNetwork::setWeights(const WeightsContainer weights) {
    if (weights_.size() != weights.size())
        return 1;
    for (uint i=0; i<weights_.size(); ++i) {
        if (weights_[i].size() != weights[i].size())
            return 1;
        for (uint j=0; j<weights_[i].size(); ++j) {
            if (weights_[i][j].size() != weights[i][j].size())
                return 1;
        }
    }
    weights_ = weights;
    return 0;
}


int NeuralNetwork::setWeightsList(const boost::python::list &weights) {
    if (weights_.size() != static_cast<uint>(len(weights)))
        return 1;
    WeightsContainer v1;
    for (uint i=0; i<weights_.size(); ++i) {
        boost::python::list l2
            = boost::python::extract<boost::python::list>(weights[i]);
        if (weights_[i].size() != static_cast<uint>(len(l2)))
            return 1;
        Matrix v2;
        for (uint j=0; j<weights_[i].size(); ++j) {
            boost::python::list l3
                = boost::python::extract<boost::python::list>(l2[j]);
            if (weights_[i][j].size() != static_cast<uint>(len(l3)))
                return 1;
            vector<double> v3;
            for (int k=0; k<len(l3); ++k) {
                v3.push_back(boost::python::extract<double>(l3[k]));
            }
            v2.push_back(v3);
        }
        v1.push_back(v2);
    }
    weights_ = v1;
    return 0;
}


WeightsContainer NeuralNetwork::getWeights() const {
    return weights_;
}


boost::python::list NeuralNetwork::getWeightsList() const {
    boost::python::list l1;
    for (WeightsContainer::const_iterator it=weights_.begin();
         it!=weights_.end(); ++it) {
        boost::python::list l2;
        for (Matrix::const_iterator itt=it->begin();
             itt!=it->end(); ++itt) {
            boost::python::object get_iter = boost::python::iterator<vector<double>>();
            boost::python::object iter = get_iter(&*itt);
            boost::python::list l3(iter);
            l2.append(l3);
        }
        l1.append(l2);
    }
    return l1;
}


void NeuralNetwork::setInput(const Field field,
                                        const int player,
                                        const bool hand_in_hand) {
    layers_.clear();
    vector<double> layer;
    layer.push_back(1.0);
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
    return;
}


void NeuralNetwork::feedforward() {
    // Loop over layers
    for (uint i=1; i<num_layers_; ++i) {
        vector<double> layer;
        if (i < num_layers_ - 1)
            layer.push_back(1.0);
        // Loop over layer's neurons
        for (int j=0; j<num_layer_neurons_[i]; ++j) {
            double value = 0.0;
            // Loop over last layer's neurons
            for (int k=0; k<num_layer_neurons_[i-1]+1; ++k) {
                value += layers_[i-1][k] * weights_[i-1][j][k];
            }
            layer.push_back(tanh(value));
        }
        layers_.push_back(layer);
    }
    return;
}


boost::python::list NeuralNetwork::getOutput() const {
    // Convert vector to Python list
    boost::python::object get_iter = boost::python::iterator<vector<double>>();
    boost::python::object iter = get_iter(&layers_.back());
    boost::python::list l(iter);
    return l;
}


int NeuralNetwork::getMove() const {
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
