#ifndef INDIVTEST_HPP
#define INDIVTEST_HPP

#include <vector>
#include <random>
#include <ctime>
#include <iostream>
#include "individual.hpp"
using namespace std;
#define NNN 1000000


/* This is an instanciation of individuals in a trivial case to test the general
algorithm structure.

Individuals are vectors of {0,1}^NNN and fitness is the number of 1 in it.

The algorithm should go toward (1,...,1)    */

class Indivtest : public Individual {
private:
	vector<bool> _coor;

public:
	//constructor
	Indivtest ();
	Indivtest (const Indivtest& george) : Individual(george), _coor(george._coor){}

	// Genetic algorithm methods
	void mutate();
	std::list<Individual*> crossWith(const Individual*) const;
	double computeFitness ();

	bool operator[](unsigned int i);
};

ostream &operator<<(ostream &out, Indivtest &bob);


#endif
