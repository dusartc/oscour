#include <iostream>
#include <vector>
#include "joueur.h"

class Map {
	public:
		Joueur j;
		int longueur;
		std::vector<int> obs;

		Map();
		void addJoueur(Joueur j);
		void addObs(int x);
		void end();
};
