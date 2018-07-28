#include "map.h"

Map::Map(){
	_longueur = 100;
}

void Map::addObs(int x) {
	_obs.push_back(x);
}

//bool Map::end() {
//	for (std::vector<int>::iterator it = _obs.begin(); it != _obs.end(); it++){
//		if( _j.x == *it ){
//			return true;
//		}
//	} 
//	return _j.x == _longueur;
//}
