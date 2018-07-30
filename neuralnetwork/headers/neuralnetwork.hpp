#ifndef NEURALNETWORK_HPP
#define NEURALNETWORK_HPP

#include <vector>
#include <list>

typedef unsigned int uint;


class NeuralNode {
	/* represents a neuron  connected to other neurons */
public:
	std::list<NeuralNode> _branches;
	std::list<float>      _branches_synapses;
	std::list<uint>       _leaves;
	std::list<float>      _leaves_synapses;

	/* constructors */
	NeuralNode (uint nb__input, uint nb_synapses, uint deepness, uint deepness_max);
	NeuralNode (const NeuralNode&);

	/* output computation */
	float neuronValue (std::vector<float>& inputs);

	/* tree ranging */
	uint numberOfNeurons ();
	std::list<NeuralNode>::iterator findNode (uint node_number);

	/* genetic function */
	void mutate (float mutation_chance, uint nb__input);
};


class NeuralNetwork {
	/* neural network coded as trees : one tree for each output and each tree leaves are inputs */
public:
	uint _nb__input;
	uint _nb_output;
	std::vector <NeuralNode> _trees;

	NeuralNetwork (uint nb__input, uint nb_output, uint nb_synapses, uint deepness_max);

	std::vector<float> outputs (std::vector<float>& inputs);
};












#endif