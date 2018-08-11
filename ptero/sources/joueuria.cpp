#include "joueuria.hpp"
#include "map.hpp"
#include <vector>
#include <algorithm>
#include <time.h>

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
	v[0] = 1.0f;
	v[1] = 1.0f;
	for (vector<int>::iterator it = m->_obs.begin(); it != m->_obs.end(); it++){
		if(j->x < *it){
			v[0] = min((float)(*it-j->x)/10,1.0f);
			break;
		}
	}
	for (vector<int>::iterator it = m->_pteros.begin(); it != m->_pteros.end(); it++){
		if(j->x < *it){
			v[1] = min((float)(*it-j->x)/10,1.0f);
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
	m.addPtero(23);
	m.addPtero(40);
	m.addPtero(85);
	m.addPtero(120);
	bool dead = false;
	for (int iter = 0; iter < nb_iter_max; iter++) {
		if (dead) break;
		for (vector<int>::iterator it = m._obs.begin(); it != m. _obs.end(); it++){
			if( michel.x == *it and michel.y==0){
				dead = true;
			} 
		}
		if(michel.y == 1){
			for (vector<int>::iterator it = m._pteros.begin(); it != m. _pteros.end(); it++){
				if( michel.y == *it){
					dead = true;
				} 
			}
		}
		michel._dist = computeDist(&michel, &m);
		michel.simulate();
		m.process();
	}
	cout << michel.distanceReached() << endl;
	return (michel.distanceReached());
}





 
void sleep(unsigned int mseconds)
{
    clock_t goal = mseconds + clock();
    while (goal > clock());
}



double gameDisplay (Brain& brain) {
	int nb_iter_max = 100;
	Joueuria michel(brain);
	Map m;
	m.addObs(5);
	m.addObs(15);
	m.addObs(20);
	m.addObs(55);
	m.addObs(95);
	m.addPtero(12);
	m.addPtero(23);
	m.addPtero(40);
	m.addPtero(85);
	m.addPtero(120);
	string display = m.toString (&michel);
	bool dead = false;
	for (int iter = 0; iter < nb_iter_max; iter++) {
		display = m.toString (&michel);
		
		cout << display << endl;
		sleep (100000);

		if (dead) break;
		for (vector<int>::iterator it = m._obs.begin(); it != m. _obs.end(); it++){
			if( michel.x == *it and michel.y==0){
				dead = true;
			} 
		}
		if(michel.y == 1){
			for (vector<int>::iterator it = m._pteros.begin(); it != m. _pteros.end(); it++){
				if( michel.y == *it){
					dead = true;
				} 
			}
		}
		michel._dist = computeDist(&michel, &m);
		michel.simulate();
		m.process();
	}
	cout << michel.distanceReached() << endl;
	return (michel.distanceReached());
}