#ifndef BRAIN_HPP
#define BRAIN_HPP

#include "neuralnetwork.hpp"
#include "individual.hpp"

typedef unsigned int uint;

class Brain : public Individual, public NeuralNetwork {
public:
    Brain (uint nb__input, uint nb_output, uint nb_synapses, uint deepness_max) : Individual(), NeuralNetwork(nb__input, nb_output, nb_synapses, deepness_max) {}

    /* genetic functions */
    virtual double computeFitness ()=0; //depends on the game
    void mutate();
    std::list<Individual*> crossWith(const Individual*) const;
};






#endif