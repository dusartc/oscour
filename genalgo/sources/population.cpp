#include <list>
#include <iostream>
#include <iterator>
#include <random>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include "population.hpp"

using namespace std;

/////////////////////////////
// POPULATION CONSTRUCTION //
/////////////////////////////
/*building by steps*/
Population::Population () {
	_nb_individuals = 0;
	_nb_children = 0;
	_nb_elites = 0;
	_nb_survivors_parents = 0;
	_nb_survivors_children = 0;
	_nb_concurrents = 0;
	_num_generation = 1;
}

void Population::initParameters (uint nb_children, uint nb_mutants,
						uint nb_survivors_children, uint nb_elites, uint nb_concurrents) {
	if (_num_generation!=1) cout<<"init function called after initialization\n";
	_nb_children = nb_children;
	_nb_mutants = nb_mutants;
	_nb_elites = nb_elites;
	_nb_survivors_children = nb_survivors_children;
	_nb_survivors_parents = _nb_individuals - nb_survivors_children - nb_elites;
	_nb_concurrents = nb_concurrents;
}

void Population::initIndividuals (list_individual_ptr& individuals) {
	if (_num_generation!=1) cout<<"init function called after initialization\n";
	sortByFitness(individuals);
	_individuals = individuals;
	_nb_individuals = individuals.size();
	_nb_survivors_parents = _nb_individuals - _nb_survivors_children - _nb_elites;
}

/*copy another population
Population::Population (const Population& pop) {
	_nb_individuals = pop._nb_individuals;
	_nb_children = pop._nb_children;
	_nb_elites = pop._nb_elites;
	_nb_survivors_parents = pop._nb_survivors_parents;
	_nb_survivors_children = pop._nb_survivors_children;
	_nb_concurrents = pop._nb_concurrents;
	_num_generation = pop._num_generation;
	_individuals = copyIndividuals(pop._individuals);
} no longer possible */

/*destructor*/
Population::~Population(){
	//we destruct every individual
	uint _;
	for (_=0;_<_nb_individuals;_++) {
		Individual* dead = _individuals.front();
		_individuals.pop_front();
		delete dead;
	}
}

/////////////
// GETTERS //
/////////////
/*get to a specific individual*/
Individual* Population::operator[] (uint index) {
	if (index >= _nb_individuals) {
		std::cout<<"Population[i] : i out of range\n";
		return(NULL);
	}
	else {
		list_individual_ptr::iterator it=_individuals.begin();
		uint i=0;
		while ( i < index ){
			++it;
			i++;
		}
		return(*it);
	}
}
/*get the best individual*/
Individual* Population::getBestIndividual(){
	return (*this)[0];
}

double Population::averageFitness(){
	double fitness_sum=0;
	list_individual_ptr::iterator it;
	for(it=_individuals.begin(); it!=_individuals.end(); it++) fitness_sum+= (*it)->getFitness();
	return (fitness_sum / _nb_individuals);
}

/*print the fitness of each individual in the terminal*/
void fitnessMonitor(const list_individual_ptr& indivs){
	list_individual_ptr::const_iterator it;
	for(it=indivs.begin(); it!=indivs.end(); it++) std::cout << ((*it)->getFitness())<< ' ';
	std::cout<<'\n';
}

void fitnessMonitor(const Population& pop){
	fitnessMonitor(pop._individuals);
}


///////////////////////
// FITNESS SELECTION //
///////////////////////
/*external functions*/
void sortByFitness( list_individual_ptr& indivs ){
	// asks each individual to set its fitness then sorts them by decreasing fitness
	list_individual_ptr::iterator it;
	for(it=indivs.begin(); it!=indivs.end(); it++) (*it)->setFitness();
	indivs.sort(cmp);
}

//comparison betwenn elements of list_individual_ptr used by merge
bool cmp(Individual* &ind1, Individual* &ind2) {return((*ind1)>(*ind2));}

vector<uint> tournament( uint nb_indivs, uint couple_size, uint nb_couples, uint nb_concurrents){
	vector<uint> winners(nb_couples*couple_size);
	vector<uint> tournament(nb_indivs);
	uint i, w, wc, best; // wc = winner couple, w = winner
	/* we find the winners of simulated tournaments
	to that end we shuffle the integers between 0 and the number of individuals
	then we isolate the _nb_concurrents first (they will be the concurrents)
	then we take the first of this set. Because the list is sorted, it
	corresponds to the best individual among the concurrents.
	Member of the same couple are selected in different portion of the same
	shuffled vector so that they come from different sets of individuals.
	However, the vector is reinitialized between couples so a same individual can
	be a multiple couples.
	we repeat this operation until we have all our winners.*/
	// random seeding
	for ( wc=0 ; wc<nb_couples ; wc++) {
		// initialize a range vector
		for (i=0 ; i<nb_indivs ; i++) tournament[i]=i;
		//shuffles it
		random_shuffle(tournament.begin(),tournament.end());
		for ( w=0 ; w<couple_size ; w++) {
			best = w*nb_concurrents;
			for (i=w*nb_concurrents ; i<(w+1)*nb_concurrents ; i++) {
				if (tournament[i]<tournament[best]) best = i;
			}
			// winners from the same couple are next to one another in the table returned
			winners[wc*couple_size+w]=tournament[best];
		}
	}
	return(winners);
}

void grimReaper(list_individual_ptr& indivs, uint nb_survivors){
	//find the indexes of the survivors
	uint nb_indivs = indivs.size();
	vector<uint> indexes = tournament(nb_indivs,nb_survivors,1,nb_indivs/nb_survivors);
	uint i_index, i_indiv=0;
	list_individual_ptr::const_iterator it = indivs.begin();
	bool in_survivors;
	for ( i_indiv = 0 ; i_indiv < nb_indivs ; i_indiv++){
		in_survivors = false;
		for ( i_index=0 ; i_index < nb_survivors ; i_index++)
				if (indexes[i_index]==i_indiv) //the current individual s index is among the selected
						in_survivors = true;
		if (in_survivors) it++; //we skip to the next individual
		else {
			delete (*it); //we delete the current individual
			it = indivs.erase(it); // erase it from the list and go to the next
		}
	}
}

/*internal function*/
list_individual_ptr Population::selectParents(string reprod_type) const {
	//find the indexes of the selected parents (depending on the type of reproduction)
	vector<uint> indexes;
	if (reprod_type.compare("crossover")==0) indexes = tournament(_nb_individuals,2,_nb_children/2,_nb_concurrents);
	//find the corresponding parents
	list_individual_ptr parents;
	uint i_index, i_indiv;
	list_individual_ptr::const_iterator it;
	for(i_index=0;i_index<indexes.size();i_index++){
		it = _individuals.begin();
		for(i_indiv=0; i_indiv < indexes[i_index]; i_indiv++) it++;
		parents.push_back((*it));
	}
	return(parents);
}

//////////////////////////////////////////
// BUILDING PARTS OF THE NEW GENERATION //
//////////////////////////////////////////

/*finding survivors*/
/*selecting elites*/
list_individual_ptr Population::findElites() {
	list_individual_ptr elites;
	Individual* elite;
	uint _;
	// the individuals are sorted by decreasing fitness so the elits are the first.
	// We erase them from the population so that they can t be selected again
	for ( _=0 ; _<_nb_elites ; _++ ){
		elite = _individuals.front();
		_individuals.pop_front();
		elites.push_back(elite); //we keep the order between elites so they are sorted
	}
	return (elites);
}
/*selecting other survivors by tournaments among the remaining individuals*/
void Population::survival() {
	grimReaper(_individuals, _nb_survivors_parents);
}

/* making children */
void Population::mutateSomeChildren (list_individual_ptr& children) {
	list_individual_ptr::iterator it;
	//for each member of the list, there is a chance of mutation
	vector<uint> mutants = tournament(_nb_children, _nb_mutants, 1, _nb_children/_nb_mutants);
	uint indchild=0;
	for (it = children.begin();it != children.end(); it++) {
		for (uint indmutant=0; indmutant < _nb_mutants; indmutant++)
			if (indchild == mutants[indmutant]) (*it)->mutate();
		indchild++;
	}
}

list_individual_ptr Population::makeChildren () const{
	/* will need some tweaks if we want it to work with reproduction that takes
	more than 2 parents */
	list_individual_ptr children, family;
	list_individual_ptr parents = selectParents("crossover");
	uint i;
	list_individual_ptr::const_iterator it;
	for (i=0 ; i < _nb_children/2 ; i++){ //2 or the number of breeders
		list_individual_ptr couple;
		it = parents.begin();
		advance(it,2); //2 or the number of breeders
		couple.splice(couple.begin(), parents, parents.begin(), it); //get 2 parents
		it = couple.begin();
		it++;
		family = couple.front()->crossWith(*it);
		children.splice(children.begin(),family); //puts all the member of family in children
	}
	return (children);
}

/////////////////////////////////////
// GENETIC ALGORITHM MAIN FUNCTION //
/////////////////////////////////////
void Population::newGeneration(){
	_num_generation++;
	/* making children */
	list_individual_ptr children = makeChildren();
	mutateSomeChildren (children);
	sortByFitness(children); //we get a list of children sorted by fitness
	/* selecting survivors */
	list_individual_ptr elites = findElites(); //already sorted
	survival(); // _individuals will be a few individuals sorted by fitness
	grimReaper(children, _nb_survivors_children); // still sorted
	/* assembling */
	_individuals.merge(elites, cmp);
	_individuals.merge(children, cmp); // _individuals is sorted
}
