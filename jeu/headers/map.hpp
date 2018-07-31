#ifndef MAP_HPP
#define MAP_HPP

#include <iostream>
#include <vector>
#include <string>

class Map {
	public:
		int _longueur;
		std::vector<int> _obs;
		std::vector<int> _pteros;

		Map();
		void addObs(int x);
		void addPtero(int x);
		void process();
		String toString(*Joueur j);
};

#endif
