#include "neuralnetwork.hpp"

#include <random>

using namespace std;

//////////////////
// CONSTRUCTORS //
//////////////////
NeuralNode::NeuralNode (uint nb__input, uint nb_synapses, uint deepness, uint deepness_max) {
	/* we want to make a tree that is tear shaped : the closer it is to the maximum deepness, the more leafs it has */
	uint nb_branches = (nb_synapses*deepness)/deepness_max;

	for (uint branch = 0; branch < nb_branches; branch++) {
		_branches.push_back (NeuralNode (nb__input, nb_synapses, deepness-1, deepness_max));
		_branches_synapses.push_back ((uint) (rand()/RAND_MAX));
	}
	for (uint leaf = 0; leaf < nb_synapses - nb_branches; leaf++) {
		_leaves.push_back (rand()%nb__input);
		_leaves_synapses.push_back ((uint) (rand()/RAND_MAX));
	}
}

NeuralNetwork::NeuralNetwork (uint nb__input, uint nb_output, uint nb_synapses, uint deepness_max){
	for (uint tree = 0; tree < nb_output; tree++) {
		_trees.push_back (NeuralNode (nb__input, nb_synapses, deepness_max, deepness_max));
	}
}



//////////////////////
// NEURAL RESPONSES //
//////////////////////

float f(float value) {
	/* neuron output in function of its inputs : here heavyside function */
	return (min(max(value, (float)1), (float)0));
}

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
		value += (*itleaf)->neuronValue(inputs) * (*itsyna);
		itleaf++;
		itsyna++;
	}
	return f(value);
}

vector<float> NeuralNetwork::outputs (vector<float>& inputs) {
    vector<float> outputs(_nb_output);
    for (uint o = 0; o < _nb_output; o++) outputs[o] = _trees[o].neuronValue(inputs);
    return (outputs);
}