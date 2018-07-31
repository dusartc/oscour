#ifndef BRAIN_HPP
#define BRAIN_HPP

#include <functional>

#include "neuralnetwork.hpp"
#include "individual.hpp"

typedef unsigned int uint;

class Brain : public Individual, public NeuralNetwork {
public:
    std::function <double()> _game;

    Brain (std::function <double()> game, uint nb__input, uint nb_output, uint nb_synapses, uint deepness_max) : Individual(), NeuralNetwork(nb__input, nb_output, nb_synapses, deepness_max), _game(game) {}
    /* genetic functions */
    virtual double computeFitness (); //depends on the game
    void mutate();
    std::list<Individual*> crossWith(const Individual*) const;

    void mutateNeuron (NeuralNode& neuron, float mutation_chance);
    void crossTrees (NeuralNode& neuron);
};






#endif