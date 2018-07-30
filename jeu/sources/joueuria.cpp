#include "joueuria.hpp"
#include <vector>

Joueuria::Joueuria() : Joueur() {}

void Joueuria::simulate() {
	vector<float> out = _network.outputs(_dist);
	if(out[0] > 0.5) {
		saute();
	} else if(out[1] > 0.5){
		avance();
	}// else {
	//	stop(); //se fait auto
	//}
}

double Joueuria::getFitness(){
	return (double) x;
}
