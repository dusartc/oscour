#include "map.h"

Map::Map(){
	_longueur = 1000;
}

Map::addJoueur(Joueur j){
	_j = j;
}

Map::addObs(int x){
	_obs.push_back[x];
}

Map::end() {
	for (std::vector<int>::iterator it = _obs.begin(); it != _obs.end(); it++){
		if( _j.x == *it ){
			return true
		}
	} return false
}
