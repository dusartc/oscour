#include "indivtest.hpp"

Indivtest::Indivtest () : Individual() {
	_coor.resize(NNN,false);
	//random initialization
	//unsigned int i;
	//for (i=0;i<N;i++) _coor.push_back(rand()%2)  ;
}

bool Indivtest::operator[](unsigned int i) {
	if (i>NNN) cout<<"Indivtest[i]: i out of range";
	return(_coor[i]);
}

double Indivtest::computeFitness () {
	double fitness = 0;
	fitness -= _coor.size();
	unsigned int i;
	for (i=0;i<_coor.size();i++) fitness += _coor[i];
	return(fitness);
}

void Indivtest::mutate() {
	unsigned int mutation = rand()%NNN;
	if (_coor[mutation]) _coor[mutation]=false;
	else _coor[mutation]=true;
}

std::list<Individual*> Indivtest::crossWith(const Individual* pap) const {
	//first we convert the father back to a useful state
	const Indivtest* father = dynamic_cast<const Indivtest*>(pap);
	if (!father) { exit(1); }
	Indivtest* child1 = new Indivtest;
	Indivtest* child2 = new Indivtest;
	list_individual_ptr children;
	//then we cross
	unsigned int k = rand()%NNN+ 1 ; //rank of the crossing
	unsigned int i=0;
	for ( ;i<k ; i++) {
		child1->_coor[i] = father->_coor[i];
		child2->_coor[i] = _coor[i];
	}
	for ( ;i<NNN; i++) {
		child1->_coor[i] = _coor[i];
		child2->_coor[i] = father->_coor[i];
	}
	children.push_back(child1);
	children.push_back(child2);
	return(children);
}

ostream &operator<<(ostream &out, Indivtest &bob) {
	unsigned int i;
	for (i=0;i<NNN;i++) out<<bob[i];
	return(out);
}
