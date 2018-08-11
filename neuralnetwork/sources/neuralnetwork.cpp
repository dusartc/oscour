#include "neuralnetwork.hpp"

#include <random>
#include <iostream>

using namespace std;

//////////////////
// CONSTRUCTORS //
//////////////////
NeuralNode::NeuralNode (uint nb__input, uint nb_synapses, uint deepness, uint deepness_max) {
	/* we want to make a tree that is tear shaped : the closer it is to the maximum deepness, the more leafs it has */
	uint nb_branches = (nb_synapses*deepness)/deepness_max;

	for (uint branch = 0; branch < nb_branches; branch++) {
		_branches.push_back (NeuralNode (nb__input, nb_synapses, deepness-1, deepness_max));
		_branches_synapses.push_back ((float) rand()/RAND_MAX);
	}
	for (uint leaf = 0; leaf < nb_synapses - nb_branches; leaf++) {
		_leaves.push_back (rand()%nb__input);
		_leaves_synapses.push_back ((float) rand()/RAND_MAX);
	}
}

NeuralNetwork::NeuralNetwork (uint nb__input, uint nb_output, uint nb_synapses, uint deepness_max){
	_nb_output = nb_output;
	_nb__input = nb__input;
	for (uint tree = 0; tree < nb_output; tree++) {
		_trees.push_back (NeuralNode (nb__input, nb_synapses, deepness_max, deepness_max));
	}
}

NeuralNode::NeuralNode (const NeuralNode& neuron) {
	list<NeuralNode>::const_iterator itnode = neuron._branches.begin();
	std::list<float>::const_iterator itsyna = neuron._branches_synapses.begin();
	for (uint branch = 0; branch < neuron._branches.size(); branch++) {
		_branches.push_back (NeuralNode(*itnode));
		_branches_synapses.push_back (*itsyna);
		itnode++;
		itsyna++;
	}
	list<uint>::const_iterator itleaf = neuron._leaves.begin();
	itsyna = neuron._leaves_synapses.begin();
	for (uint leaf = 0; leaf < neuron._leaves.size(); leaf++) {
		_leaves.push_back (*itleaf);
		_leaves_synapses.push_back (*itsyna);
		itleaf++;
		itsyna++;
	}
}

//////////////////////
// NEURAL RESPONSES //
//////////////////////

float  f (float x) {
	/* neuron output in function of its inputs : here heavyside function */
	return (max(min(x, (float)1), (float)0));
}

float df (float x) {
	/* derivativ of f */
	return ((x<1)*(x>0));
}

float NeuralNode::neuronValue (vector<float>& inputs) {
	float value = 0;
	list<NeuralNode>::iterator itnode = _branches.begin();
	std::list<float>::iterator itsyna = _branches_synapses.begin();
	for (uint branch = 0; branch < _branches.size(); branch++) {
		value += (*itnode).neuronValue(inputs) * (*itsyna);
		itnode++;
		itsyna++;
	}
	list<uint>::iterator itleaf = _leaves.begin();
	itsyna = _leaves_synapses.begin();
	for (uint leaf = 0; leaf < _leaves.size(); leaf++) {
		value += inputs[*itleaf] * (*itsyna);
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

//////////////
// LEARNING //
//////////////
void NeuralNetwork::learn (vector<float>& inputs, vector<float>& outputs, float learning_coef) {
	for (uint o = 0; o < _nb_output; o++) {
		vector<float> hash_table(_trees[o].numberOfNeurons());
		uint key = 0;
		float error = outputs[0] - _trees[o].neuronValueHashTable(inputs, hash_table, key);
		_trees[o].retropropagate (inputs, hash_table, error, learning_coef);
	}
}

float NeuralNode::neuronValueHashTable (vector<float>& inputs, vector<float>& hash_table, uint& key) {
	/* saves the value in a table */
	_key = key;
	key++; // so that every neuron has a different key
	float value = 0;
	list<NeuralNode>::iterator itnode = _branches.begin();
	std::list<float>::iterator itsyna = _branches_synapses.begin();
	for (uint branch = 0; branch < _branches.size(); branch++) {
		value += (*itnode).neuronValueHashTable(inputs, hash_table, key) * (*itsyna);
		itnode++;
		itsyna++;
	}
	list<uint>::iterator itleaf = _leaves.begin();
	itsyna = _leaves_synapses.begin();
	for (uint leaf = 0; leaf < _leaves.size(); leaf++) {
		value += inputs[*itleaf] * (*itsyna);
		itleaf++;
		itsyna++;
	}
	hash_table[_key] = value;
	return f(value);
}

void NeuralNode::retropropagate (vector<float>& inputs, vector<float>& hash_table, float error, float learning_coef) {
	/* retropropagate the error using the hash_table */
	list<NeuralNode>::iterator itnode = _branches.begin();
	std::list<float>::iterator itsyna = _branches_synapses.begin();
	for (uint branch = 0; branch < _branches.size(); branch++) {
		float value = hash_table[(*itnode)._key];
		(*itnode).retropropagate(inputs, hash_table, df(value)*(*itsyna)*error, learning_coef);
		*itsyna += learning_coef*error*f(value);
		itnode++;
		itsyna++;
	}
	list<uint>::iterator itleaf = _leaves.begin();
	itsyna = _leaves_synapses.begin();
	for (uint leaf = 0; leaf < _leaves.size(); leaf++) {
		*itsyna += learning_coef*error*f(inputs[*itleaf]);
		itleaf++;
		itsyna++;
	}
	
}



//////////////////
// TREE RANGING //
//////////////////

uint NeuralNode::numberOfNeurons () const {
	uint number = 1; //current neuron
	list<NeuralNode>::const_iterator itnode;
	for (itnode = _branches.begin(); itnode != _branches.end(); itnode++) {
		number += (*itnode).numberOfNeurons (); // size of deeper neurons
	}
	return number;
}

uint NeuralNode::numberOfNeuronsAndLeaves () const {
	uint number = 1 + _leaves.size(); //current neuron
	list<NeuralNode>::const_iterator itnode;
	for (itnode = _branches.begin(); itnode != _branches.end(); itnode++) {
		number += (*itnode).numberOfNeuronsAndLeaves (); // size of deeper neurons
	}
	return number;
}

uint NeuralNetwork::numberOfNeurons () const {
	uint number = 0; //current neuron
	list<NeuralNode>::const_iterator itnode;
	for (uint o =0; o < _nb_output; o++) {
		number += _trees[o].numberOfNeurons (); // size of this output tree
	}
	return number;
}

uint NeuralNetwork::numberOfNeuronsAndLeaves () const {
	uint number = 0; //current neuron
	list<NeuralNode>::const_iterator itnode;
	for (uint o =0; o < _nb_output; o++) {
		number += _trees[o].numberOfNeuronsAndLeaves (); // size of this output tree
	}
	return number;
}


list<NeuralNode>::iterator NeuralNode::findNode (uint node_number) {
	list<NeuralNode>::iterator itnode = _branches.begin();
	while (true) {
		if (node_number == 1) return (itnode);
		uint deeper_neurons = (*itnode).numberOfNeurons ();
		if (deeper_neurons < node_number) {
			node_number -= deeper_neurons;
			itnode++;
		}
		else return ((*itnode).findNode (node_number - 1)); //remove the current neuron
	}
}



void NeuralNode::display(std::ostream& out, uint deepness) const {
	// branches first
	list<NeuralNode>::const_iterator itnode = _branches.begin();
	std::list<float>::const_iterator itsyna = _branches_synapses.begin();
	for (uint branch = 0; branch < _branches.size(); branch++) {
		// display the synapse
		for (uint d=0; d<deepness; d++) out << "-----";
		out << "  " << *itsyna << "*neur\n";
		//display the neuron
		(*itnode).display(out, deepness+1);
		itnode++;
		itsyna++;
	}
	// then leaves
	list<uint>::const_iterator itleaf = _leaves.begin();
	itsyna = _leaves_synapses.begin();
	for (uint leaf = 0; leaf < _leaves.size(); leaf++) {
		for (uint d=0; d<deepness; d++) out << "-----";
		out << "  " << *itsyna << "*" << *itleaf << "\n";
		itleaf++;
		itsyna++;
	}
}

ostream& operator<<(ostream& out, const NeuralNetwork& network) {
	for (uint o=0; o<network._nb_output; o++) {
		out << "output nb : "<< o << " neur\n";
		network._trees[o].display(out, 0);
	}
	return (out);
}

///////////////////////
// GENETIC FUNCTIONS //
///////////////////////
void NeuralNode::mutate (float mutation_chance, uint nb__input){
	/* possiblity :
		- split a leaf or a node in two
		- change the synapses value
		- replace a leaf input by another input
	*/
	list<NeuralNode>::iterator itnode = _branches.begin();
	std::list<float>::iterator itsyna = _branches_synapses.begin();
	uint init_nb_branches = _branches.size(); //initial number of branches, can increase
	for (uint branch = 0; branch < init_nb_branches; branch++) {
		if (rand() > mutation_chance*RAND_MAX) {
			/* duplicate */
			_branches.push_back (NeuralNode(*itnode));
			*itsyna *= 0.5;
			_branches_synapses.push_back (*itsyna);
		}
		if (rand() > mutation_chance*RAND_MAX) {
			/* change synapse */
			*itsyna += -0.5 + (float)(rand()/RAND_MAX);
		}
		/* call mutation on further neurons */
		(*itnode).mutate (mutation_chance, nb__input);
		itnode++;
		itsyna++;
	}
	list<uint>::iterator itleaf = _leaves.begin();
	itsyna = _leaves_synapses.begin();
	uint init_nb_leaves = _leaves.size(); //initial number of leaves
	for (uint leaf = 0; leaf < init_nb_leaves; leaf++) {
		if (rand() > mutation_chance*RAND_MAX) {
			/* duplicate */
			_leaves.push_back (*itleaf);
			*itsyna *= 0.5;
			_leaves_synapses.push_back (*itsyna);
		}
		if (rand() > mutation_chance*RAND_MAX) {
			/* change synapse */
			*itsyna += -0.5 + (float)(rand()/RAND_MAX);
		}
		if (rand() > mutation_chance*RAND_MAX) {
			/* change input */
			_leaves.push_back (*itleaf);
			*itleaf = rand()%nb__input;
			_leaves_synapses.push_back (*itsyna);
		}
		itleaf++;
		itsyna++;
	}
}
