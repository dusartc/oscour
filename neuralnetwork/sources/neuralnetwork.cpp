#include "neuralnetwork.hpp"

using namespace std;

float NeuralNode::neuronValue (vector<float>& inputs) {
    float value = 0;
    list<NeuralNode>::iterator itnode = _branches.begin();
    std::list<float>::iterator itsyna = _branches_synapses.begin();
    for (uint s = 0; s < _branches.size(); s++) {
        value += (*itnode).neuronValue(inputs) * (*itsyna);
        itnode++;
        itsyna++;
    }
    list<uint>::iterator itleaf = _leaves.begin();
    itsyna = _leaves_synapses.begin();
    for (uint s = 0; s < _leaves.size(); s++) {
        value += (*itleaf).neuronValue(inputs) * (*itsyna);
        itleaf++;
        itsyna++;
    }
    return value;
}




vector<float> NeuralNetwork::outputs (vector<float>& inputs) {
    vector<float> outputs(_nb_output);
    for (uint o = 0; o < _nb_output; o++) outputs[o] = _trees[o].neuronValue(inputs);
    return (outputs);
}