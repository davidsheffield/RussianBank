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


Evolve::Evolve(const boost::python::list& nets) {
    num_nets_ = 8;
    for (int i=0; i<len(nets); ++i) {
        nets_.push_back(pair<NeuralNetwork, double>(
                            boost::python::extract<NeuralNetwork>(nets[i]),
                            0.0));
    }
    vector<int> neurons;
    neurons.push_back(1000);
    for (int i=len(nets); i<num_nets_; ++i) {
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

    vector<WeightsContainer> parent_weights;
    for (int i=0; i<num_keep_; ++i) {
        nets_[i].second = 0.0;
        parent_weights.push_back(nets_[i].first.getWeights());
    }

    default_random_engine generator(time(0));
    vector<int> neurons;
    neurons.push_back(1000);
    for (int i=0; i<num_nets_-num_keep_; ++i) {
        NeuralNetwork net(neurons);
        WeightsContainer weights;
        for (uint j=0; j<parent_weights[0].size(); ++j) {
            uniform_int_distribution<int> distribution(0, parent_weights[0][j].size() - 1);
            int cutoff = distribution(generator);
            Matrix w;
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


vector<NeuralNetwork> Evolve::getNeuralNetworks() const {
    vector<NeuralNetwork> nets_vector;
    for (Nets::const_iterator it=nets_.begin(); it!=nets_.end(); ++it) {
        nets_vector.push_back(it->first);
    }
    return nets_vector;
}


boost::python::list Evolve::getNeuralNetworksList() const {
    boost::python::list nets_list;
    for (Nets::const_iterator it=nets_.begin(); it!=nets_.end(); ++it) {
        nets_list.append(it->first);
    }
    return nets_list;
}


vector<double> Evolve::getPoints() const {
    vector<double> points_vector;
    for (Nets::const_iterator it=nets_.begin(); it!=nets_.end(); ++it) {
        points_vector.push_back(it->second);
    }
    return points_vector;
}


boost::python::list Evolve::getPointsList() const {
    boost::python::list points_list;
    for (Nets::const_iterator it=nets_.begin(); it!=nets_.end(); ++it) {
        points_list.append(it->second);
    }
    return points_list;
}


void Evolve::sortNeuralNetworks() {
    sort(nets_.begin(), nets_.end(), sortNets);
    return;
}


bool Evolve::sortNets(const pair<NeuralNetwork, double> i,
                      const pair<NeuralNetwork, double> j) {
    return i.second > j.second;
}
