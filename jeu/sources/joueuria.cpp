#include "joueuria.hpp"
#include "map.hpp"
#include <vector>
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
	std::vector<float> v;
	for (vector<int>::iterator it = m->_obs.begin(); it != m->_obs.end(); it++){
		if(j->x < *it){
			v.push_back(*it-j->x);
			break;
		} 
	}
	for (vector<int>::iterator it = m->_pteros.begin(); it != m->_pteros.end(); it++){
		if(j->x < *it){
			v.push_back(*it-j->x);
			break;
		} 
	}
	return v;
}

double game (Brain& brain) {
	Joueuria michel(brain);
	Map m;
	bool end = false;
	m.addObs(5);
	m.addObs(15);
	m.addObs(20);
	m.addObs(55);
	m.addObs(95);
	m.addPtero(12);
	while(!end){
		cout << m.toString(&michel);

		for (vector<int>::iterator it = m._obs.begin(); it != m. _obs.end(); it++){
			if( michel.x == *it and michel.y==0){
				end = true;
				cout << "rip" << endl;
			} 
		}
		if(michel.y == 1){
			for (vector<int>::iterator it = m._pteros.begin(); it != m. _pteros.end(); it++){
				if( michel.y == *it){
					end = true;
					cout << "rip" << endl;
				} 
			}
		}
		if(michel.x == m._longueur) end = true;
		michel._dist = computeDist(&michel, &m);
		michel.simulate();
		m.process();
	}
	return (michel.distanceReached());
}