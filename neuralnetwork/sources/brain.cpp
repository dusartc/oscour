#include "brain.hpp"
#include <math>

using namespace std;

///////////////////////////////
// GENETIC FUNCTIONS HELPERS //
///////////////////////////////




void Brain::crossTrees (NeuralNode& neuron){

}



////////////////////////////
// MAIN GENETIC FUNCTIONS //
////////////////////////////


void Brain::mutate() {
	/* we want a mutation chance small enough to change ln (number of nodes and leaves) vertices */
	uint total_number = 0;
	for (uint o = 0; o < _nb_output; o++) {
		total_number += _trees[o].numberOfNeurons();
	}
	mutation_chance = ln(total_number)/total_number;
	for (uint o = 0; o < _nb_output; o++) {
		_trees[o].mutate(mutation_chance, _nb_input);
	}
}


		
		
list<Individual*> crossWith(const Individual*) const {

}

