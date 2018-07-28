#ifndef INDIVIDUAL_HPP
#define INDIVIDUAL_HPP

#include <list>
#include <memory>
#include <vector>
#include <iostream>

class Individual {
private:
	/* FITNESS */
	double _fitness;
	bool _fitness_set_flag;

	// if the subclass has way to compute fitness faster during mutaion or crossover
	// for instance, it can set it with this function. It can also override a fitness
	// that was computed during an earlier generation (for when we do Pareto fitness)
	void setFitnessDirectly (double f);

protected:
	/* CONSTRUCTOR */
	Individual(): _fitness(0), _fitness_set_flag(false){}
	Individual(const Individual& bob): _fitness(bob._fitness), _fitness_set_flag(false){}

public:
	virtual ~Individual();

	/* SET AND READ FITNESS */
	double getFitness () const;
	// if fitness isn t set, it will compute it, save it as an attribute and change the flag
	void setFitness();
	// void setFitness ();
	// computes the numerical value of fitness. Depends of the Individual subclass
	virtual double computeFitness ()=0;

	// Genetic algorithm methods
	virtual std::list<Individual*> crossWith(const Individual*) const =0;
	virtual void mutate()=0;

	//
	// /* REPRODUCTION FUNCTIONS */
	// /*mutation*/
	// //makes a new individual and mutates it. Parents unchanged
	// virtual Individual* spawnAMutant () const =0;
	//
	// /*crossover*/
	// //function that sends all information needed for crossover in a buffer
	// virtual void father (const void*& father_material) const=0;
	// //makes copies of itself and then use father information to change them
	// virtual std::list<Individual*> mother (const void*& father_material) const=0;
};

typedef std::list<Individual*> list_individual_ptr;

/* NEW INDIVIDUALS BUILDING */
//function that makes crossover using member father and mother
list_individual_ptr mating (const list_individual_ptr& parents);

//Comparison of fitness
bool operator< (const Individual&, const Individual&);
bool operator> (const Individual&, const Individual&);
bool operator<= (const Individual&, const Individual&);
bool operator>= (const Individual&, const Individual&);

#endif
