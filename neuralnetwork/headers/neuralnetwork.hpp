#ifndef NEURALNETWORK_HPP
#define NEURALNETWORK_HPP

#include <vector>
#include <list>
#include <iostream>

typedef unsigned int uint;


class NeuralNode {
	/* represents a neuron  connected to other neurons */
public:
	std::list<NeuralNode> _branches;
	std::list<float>      _branches_synapses;
	std::list<uint>       _leaves;
	std::list<float>      _leaves_synapses;

	uint _key; //useful for quick search in hash table

	/* constructors */
	NeuralNode (uint nb__input, uint nb_synapses, uint deepness, uint deepness_max);
	NeuralNode (const NeuralNode&);

	/* output computation */
	float neuronValue (std::vector<float>& inputs);

	/* learning */
	float neuronValueHashTable (std::vector<float>& inputs, std::vector<float>& hash_table, uint& key);
	void  retropropagate       (std::vector<float>& inputs, std::vector<float>& hash_table, float error, float learning_coef);

	/* tree ranging */
	uint numberOfNeurons () const;
	uint numberOfNeuronsAndLeaves () const;
	std::list<NeuralNode>::iterator findNode (uint node_number);
	void display(std::ostream&, uint deepness) const; //as a function because we can't pass 2 arguments to <<


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

	void learn (std::vector<float>& inputs, std::vector<float>& outputs, float learning_coef);

	uint numberOfNeurons () const;
	uint numberOfNeuronsAndLeaves () const;

};

std::ostream& operator<<(std::ostream&, const NeuralNetwork&);










#endif