#include "map.hpp"
#include <vector>
#include <string>

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

String Map::toString(*Joueur j){
	String premiereLigne, deuxiemeLigne;
	if(j.y == 0){
		premiereLigne = " ";
		deuxiemeLigne = "o";
	} else {
		premiereLigne = "o";
		deuxiemeLigne = "_";
	}
	for(int i=j.x+1;i<min(m._longueur,j.x+10);i++){
		if(find(m._pteros.begin(), m._pteros.end(), i) != m._pteros.end()) {
			premiereLigne += "*";
		} else {
			premiereLigne += " ";
		}		
	}
	for(int i=j.x+1;i<min(m._longueur,j.x+10);i++){
		if(find(m._obs.begin(), m._obs.end(), i) != m._obs.end()) {
			deuxiemeLigne += "|";
		} else {
			deuxiemeLigne += "_";
		}		
	}
	return premiereLigne << "\n" << deuxiemeLigne << j.x << endl;
}