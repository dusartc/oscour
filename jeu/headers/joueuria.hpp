#ifndef JOUEURIA_HPP
#define JOUEURIA_HPP

#include "brain.hpp"
#include "joueur.hpp"
#include <vector>

class Joueuria : public Joueur {
	public:
		std::vector<float> _dist;
		NeuralNetwork& _neural_network;

		void simulate();
		double distanceReached();

		Joueuria(NeuralNetwork&);
};

double game (Brain& brain);

#endif
