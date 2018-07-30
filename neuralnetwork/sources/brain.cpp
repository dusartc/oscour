#include "brain.hpp"
#include <math.h>

using namespace std;


////////////////////////////
// MAIN GENETIC FUNCTIONS //
////////////////////////////


void Brain::mutate() {
	/* we want a mutation chance small enough to change ln (number of nodes) vertices */
	uint total_number = 0;
	for (uint o = 0; o < _nb_output; o++) {
		total_number += _trees[o].numberOfNeurons();
	}
	float mutation_chance = log(total_number)/total_number;
	for (uint o = 0; o < _nb_output; o++) {
		_trees[o].mutate(mutation_chance, _nb__input);
	}
}


		
		
list<Individual*> Brain::crossWith(const Individual* father) const {
	// get the father into a useful form
	const Brain* pap = dynamic_cast<const Brain*>(father);
	if (!father) { exit(1); }
	Brain* child1 = new Brain(*pap );
	Brain* child2 = new Brain(*this);
	list_individual_ptr children;
	//then we cross
	for (uint o = 0; o < _nb_output; o++) {
		/* choose a crossing point in each tree */
		uint node_cross1 = rand()%(child1->_trees[o].numberOfNeurons());
		uint node_cross2 = rand()%(child2->_trees[o].numberOfNeurons());
		/* find and invert those two nodes */
		list<NeuralNode>::iterator itnode1 = child1->_trees[o].findNode(node_cross1);
		list<NeuralNode>::iterator itnode2 = child2->_trees[o].findNode(node_cross2);
		iter_swap (itnode1, itnode2);
	}
	children.push_back(child1);
	children.push_back(child2);
	return(children);

}

