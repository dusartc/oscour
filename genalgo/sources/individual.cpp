#include "individual.hpp"
#include <list>
#include <iostream>

double Individual::getFitness () const {
	return _fitness;
}

Individual::~Individual(){}


void Individual::setFitness() {
	if (_fitness_set_flag==false) {
		_fitness = computeFitness();
		_fitness_set_flag = true;
	}
}
//
// list_individual_ptr mating (const list_individual_ptr& parents){
// 	const void* father_material;
// 	list_individual_ptr::const_iterator it= parents.begin();
// 	unsigned int i;
// 	for ( i=0  ; i<parents.size()-1 ; i++ ){
// 		(*it)->father(father_material);
// 		it++;
// 	}
// 	return ((*it)->mother(father_material));
// }


bool operator< (const Individual& i1, const Individual& i2) {return (i1.getFitness()<i2.getFitness());}
bool operator> (const Individual& i1, const Individual& i2) {return (i2<i1);}
bool operator<= (const Individual& i1, const Individual& i2) {return !(i2<i1);}
bool operator>= (const Individual& i1, const Individual& i2) {return !(i1<i2);}
