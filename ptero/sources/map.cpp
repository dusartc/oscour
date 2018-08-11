#include "map.hpp"
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include "joueur.hpp"
using namespace std;

Map::Map(){
	_longueur = 100;
}

void Map::addObs(int x) {
	_obs.push_back(x);
}

void Map::addPtero(int x) {
	_pteros.push_back(x);
}

void Map::process() {
	std::vector<int>::iterator it;
	for(it = _pteros.begin(); it != _pteros.end(); it++){
		(*it)--;
	}
}

std::string Map::toString(Joueur *j){
	std::string premiereLigne, deuxiemeLigne;
	if(j->y == 0){
		premiereLigne = " ";
		deuxiemeLigne = "o";
	} else {
		premiereLigne = "o";
		deuxiemeLigne = "_";
	}
	for(int i=j->x+1;i<min(_longueur,j->x+10);i++){
		if(find(_pteros.begin(), _pteros.end(), i) != _pteros.end()) {
			premiereLigne += "*";
		} else {
			premiereLigne += " ";
		}		
	}
	for(int i=j->x+1;i<min(_longueur,j->x+10);i++){
		if(find(_obs.begin(), _obs.end(), i) != _obs.end()) {
			deuxiemeLigne += "|";
		} else {
			deuxiemeLigne += "_";
		}		
	}
	stringstream ss;
	ss << premiereLigne << "\n" << deuxiemeLigne << j->x << endl;
	return ss.str();
}