#include "map.hpp"
#include <vector>

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
	
