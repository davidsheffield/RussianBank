#include "neuralnetwork/include/Evolve.h"

using namespace std;


Evolve::Evolve() {
    num_nets_ = 8;
    vector<int> neurons;
    neurons.push_back(1000);
    for (int i=0; i<num_nets_; ++i) {
        NeuralNetwork net(neurons);
        net.setRandomWeights();
        nets_.push_back(pair<NeuralNetwork, double>(net, 0.0));
    }
}


Evolve::~Evolve() {}


void Evolve::playMatches() {
    srand(time(NULL));
    int seed = rand();
    for (int i=0; i<num_nets_; ++i) {
        int opponent = i + 2;
        if (opponent >= num_nets_)
            opponent -= num_nets_;
        cout << "Match " << i << " vs " << opponent << endl;
        Match match(nets_[i].first, nets_[opponent].first, seed+i);
        match.play();
        nets_[i].second += match.getPoints(0);
        nets_[opponent].second += match.getPoints(1);
    }
    // for (int i=0; i<num_nets_; ++i) {
    //     cout << i << " " << nets_[i].second << endl;
    // }
    return;
}


void Evolve::breed() {
    sort(nets_.begin(), nets_.end(), sortNets);
    for (Nets::const_iterator it=nets_.begin(); it!=nets_.end(); ++it) {
        cout << it->second << endl;
    }
    nets_.erase(nets_.begin() + num_keep_, nets_.end());

    vector<vector<vector<vector<double>>>> parent_weights;
    for (int i=0; i<num_keep_; ++i) {
        nets_[i].second = 0.0;
        parent_weights.push_back(nets_[i].first.getWeights());
    }

    default_random_engine generator(time(0));
    vector<int> neurons;
    neurons.push_back(1000);
    for (int i=0; i<num_nets_-num_keep_; ++i) {
        NeuralNetwork net(neurons);
        vector<vector<vector<double>>> weights;
        for (uint j=0; j<parent_weights[0].size(); ++j) {
            uniform_int_distribution<int> distribution(0, parent_weights[0][j].size() - 1);
            int cutoff = distribution(generator);
            vector<vector<double>> w;
            w.insert(w.begin(), parent_weights[0][j].begin(),
                     parent_weights[0][j].begin() + cutoff);
            w.insert(w.end(), parent_weights[1][j].begin() + cutoff,
                      parent_weights[1][j].end());
            weights.push_back(w);
        }
        net.setWeights(weights);
        nets_.push_back(pair<NeuralNetwork, double>(net, 0.0));
    }

    return;
}


bool Evolve::sortNets(const pair<NeuralNetwork, double> i,
                      const pair<NeuralNetwork, double> j) {
    return i.second > j.second;
}
