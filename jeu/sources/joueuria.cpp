#include "joueuria.hpp"
#include <vector>
using namespace std;

Joueuria::Joueuria() : Joueur() {}

void Joueuria::simulate() {
	vector<float> out = _network.outputs(_dist);
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

double Joueuria::getFitness(){
	return (double) x;
}
