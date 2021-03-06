#include "population.hpp"
#include "brain.hpp"
#include "joueuria.hpp"
#include <iostream>

#include <random>
#include <ctime>

using namespace std;

#define NB_INDIV 100
#define NB_CHILDREN 160
#define NB_MUTANTS 40
#define NB_SURV_CHILD 80
#define NB_ELITES 1
#define NB_BREEDER 2
#define NB_CONCUR 2

#define NB_GEN 30

#define NB__INPUT 2
#define NB_OUTPUT 2
#define NB_SYNAPSE 2
#define DEEPNESS_MAX 2

int main () {
	srand(time(NULL));
    Population pop;
	list_individual_ptr init; //set of individuals that will initialize the population
	unsigned int i;
	for (i=0; i<NB_INDIV; i++) {
		init.push_front(new Brain(game, NB__INPUT, NB_OUTPUT, NB_SYNAPSE, DEEPNESS_MAX));
	}
    pop.initParameters(NB_CHILDREN, NB_MUTANTS, NB_SURV_CHILD, NB_ELITES, NB_CONCUR);
	pop.initIndividuals(init);
	cout<< "starting evolution" << endl;
	for (i=0; i<NB_GEN; i++) {
		pop.newGeneration();
		cout<< "generation numero : " << i << endl;
	}
	Brain michel = *dynamic_cast<const Brain*>(pop[0]);
	gameDisplay (michel);
	cout << "best brain :\n" << michel << "with " << michel.numberOfNeuronsAndLeaves() << " total network size\n";
}