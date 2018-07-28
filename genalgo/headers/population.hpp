#ifndef POPULATION_HPP
#define POPULATION_HPP

#include <list>
#include <string>
#include "individual.hpp"

using uint = unsigned int;

#define MUTATE_CHANCE 0.01

class Population {
private:
	/* PARAMETERS */
	/*total number of individuals*/
	//number of individuals at the beginning of a generation
	uint _nb_individuals;
	uint _nb_children; //number of children made each generation

	uint _nb_mutants; //number of children that will be mutated

	/*selection*/
	//number of elites (best parents) that are automatically selected for the next generation
	uint _nb_elites;
	//number of parents(except elites) that will be selected for the next generation
	uint _nb_survivors_parents;
	//number of children that will be selected for the next generation
	uint _nb_survivors_children;
	//number of individuals that will fight to be procreate
	uint _nb_concurrents;

	/*other*/
	uint _num_generation; //self explanatory

	/* INDIVIDUALS */
	list_individual_ptr _individuals;

	/* BUILDING PARTS OF THE NEW GENERATION */
	/*selection of survivors that pass from a generation to the following*/
	//find the elites and puts them in a separated list
	list_individual_ptr findElites ();
	//erase all the individuals except a few selected by tournament
	void survival ();

	/*children making functions*/
	//selects the individuals on whom the two following functions will be based
	//these individuals are COPIES and will be modified directly
	list_individual_ptr selectParents(std::string) const;
	//selects couples of parents and cross them
	list_individual_ptr makeChildren () const;

	//make a mutation on a percent of this popultion;
	void mutateSomeChildren (list_individual_ptr&);



public:
	/* CONSTRUCTION */
	//by steps
	Population ();
	void initParameters (uint, uint, uint, uint, uint);
	void initIndividuals (list_individual_ptr&);

	//destructor that erase every individual of the population
	~Population();

	/* GETTERS */
	uint numGen() { return _num_generation; }
	Individual* getBestIndividual();
	// operator [i] that access to Individual nb i
	Individual* operator[] (uint);

	double averageFitness();
	//returns every fitness
	friend void fitnessMonitor(const Population&);

	/* GENETIC ALGORITHM MAIN FUNCTION */
	// The function we call in a loop. It creates children then selects a
	// new population
	void newGeneration ();

};


/* FITNESS SELECTION */
//sets the fitness of each individual then sort them by fitness
void sortByFitness (list_individual_ptr&);

//comparison > between two Individual*
bool cmp(Individual* &, Individual* &);

/* Selects a number of index by simulating tournaments in a sorted list of
individuals which size is the 1st parameter.
winners are clustered in couples (number = 2nd param, size = 3rd param)
individuals in the same couple comes from a different set of individual, but
the same individual can be in multiple couples.
Each simulated tournament takes place between the same number of individuals
(4th param) so ensure that couple size * number of concurents is less than the
size of the list. */
std::vector<uint> tournament(uint, uint, uint, uint);


/* INDIVIDUALS DESTRUCTION */
//will destruct every individuals of the list except a selected few (2nd param)
void grimReaper(list_individual_ptr&, uint);

/* GETTERS */
void fitnessMonitor(const list_individual_ptr&);

void fitnessMonitor(const Population&);

#endif
