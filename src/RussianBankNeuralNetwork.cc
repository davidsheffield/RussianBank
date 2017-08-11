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

    for (int i=0; i<num_layers_; ++i) {
        vector<double> weights;
        for (int j=0; j<num_layer_neurons_[i]+1; ++j) {
            weights.push_back(0.0);
        }
        weights_.push_back(weights);
    }
}


RussianBankNeuralNetwork::~RussianBankNeuralNetwork() {}


boost::python::list
RussianBankNeuralNetwork::getOutput(const boost::python::list &input) {
    if (len(input) != kINPUTS)
        return input;
    vector<double> layer;
    layer.push_back(1.0);
    for (int i=0; i<len(input); ++i) {
        layer.push_back(boost::python::extract<double>(input[i]));
    }
    layers_.push_back(layer);

    // Loop over layers
    for (int i=0; i<num_layers_-1; ++i) {
        layer.clear();
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

    // Convert vector to Python list
    boost::python::object get_iter = boost::python::iterator<vector<double>>();
    boost::python::object iter = get_iter(&layers_.back());
    boost::python::list l(iter);
    return l;
}
