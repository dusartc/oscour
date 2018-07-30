#ifndef JOUEURIA_HPP
#define JOUEURIA_HPP

#include "neuralnetwork.hpp"
#include "joueur.hpp"
#include <vector>

class Joueuria : public Joueur {
	public:
		NeuralNetwork _network;
		std::vector<float> _dist;

		void simulate();
		double getFitness();

		Joueuria();
};

#endif
