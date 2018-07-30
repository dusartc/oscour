#ifndef MAP_HPP
#define MAP_HPP

#include <iostream>
#include <vector>

class Map {
	public:
		int _longueur;
		std::vector<int> _obs;

		Map();
		void addObs(int x);
		bool end();
};

#endif
