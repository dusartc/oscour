#ifndef MAP_HPP
#define MAP_HPP

#include <iostream>
#include <vector>

class Map {
	public:
		int _longueur;
		std::vector<int> _obs;
		std::vector<int> _pteros;

		Map();
		void addObs(int x);
		void addPtero(int x);
		void process();
};

#endif
