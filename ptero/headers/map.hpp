#ifndef MAP_HPP
#define MAP_HPP

#include <vector>
#include <string>
#include "joueur.hpp"

class Map {
	public:
		int _longueur;
		std::vector<int> _obs;
		std::vector<int> _pteros;

		Map();
		void addObs(int x);
		void addPtero(int x);
		void process();
		std::string toString(Joueur *j);
};

#endif
