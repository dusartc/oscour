#include "map.hpp"

Map::Map(){
	_longueur = 100;
}

void Map::addObs(int x) {
	_obs.push_back(x);
}
