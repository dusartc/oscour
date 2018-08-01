#include "joueuria.hpp"
#include "map.hpp"
#include <vector>
#include <algorithm>
using namespace std;

Joueuria::Joueuria(NeuralNetwork& nn) : Joueur(), _neural_network(nn) {}

void Joueuria::simulate() {
	vector<float> out = _neural_network.outputs(_dist);
	if(momentum){
		sautavant();
		momentum = false;
	} else if(nextmove) {
		saute();
		nextmove = false;
	} else {
		if(out[0] > 0.5) {
			if(out[1] > 0.5){
				sautavant();
				momentum = true;
			} else {
				saute();
				nextmove = true;
			} 
		} else if(out[1] > 0.5){
			avance();
		}
	}
}

double Joueuria::distanceReached(){
	return (double) x;
}

std::vector<float> computeDist(Joueur *j, Map *m){
	std::vector<float> v(2);
	v.insert(0,1);
	v.insert(1,1);
	for (vector<float>::iterator it = m->_obs.begin(); it != m->_obs.end(); it++){
		if(j->x < *it){
			v.insert(0,min((*it-j->x)/10,1));
			break;
		}
	}
	for (vector<float>::iterator it = m->_pteros.begin(); it != m->_pteros.end(); it++){
		if(j->x < *it){
			v.insert(1,min((*it-j->x)/10,1));
			break;
		} 
	}
	return v;
}

double game (Brain& brain) {
	int nb_iter_max = 100;
	Joueuria michel(brain);
	Map m;
	m.addObs(5);
	m.addObs(15);
	m.addObs(20);
	m.addObs(55);
	m.addObs(95);
	m.addPtero(12);
	for (int iter = 0; iter < nb_iter_max; iter++) {
		for (vector<int>::iterator it = m._obs.begin(); it != m. _obs.end(); it++){
			if( michel.x == *it and michel.y==0){
				break;
			} 
		}
		if(michel.y == 1){
			for (vector<int>::iterator it = m._pteros.begin(); it != m. _pteros.end(); it++){
				if( michel.y == *it){
					break;
				} 
			}
		}
		if(michel.x == m._longueur) break;
		michel._dist = computeDist(&michel, &m);
		michel.simulate();
		m.process();
	}
	cout << michel.distanceReached() << endl;
	return (michel.distanceReached());
}