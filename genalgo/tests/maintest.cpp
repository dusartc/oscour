#include <gtest/gtest.h>

#include "population.hpp"
#include "indivtest.hpp"

#define NB_INDIV 1000
#define NB_CHILDREN 1600
#define NB_MUTANTS 40
#define NB_SURV_CHILD 800
#define NB_ELITES 5
#define NB_BREEDER 2
#define NB_CONCUR 20

#define NB_GENS 10 //number of generation done in tests



///////////////////////////
// TRIVIAL PROBLEM TEST
///////////////////////////

TEST(TivialProblem, individualSubclass) {
	srand (time(NULL));
	Indivtest* indiv_test = new Indivtest;
	Indivtest* indiv_test_2 = new Indivtest;
	indiv_test->setFitness();
	EXPECT_EQ(-NNN, indiv_test->getFitness()) << "Individual Subclass for the trivial problem not working";
	indiv_test_2->mutate();
	indiv_test_2->setFitness();
	EXPECT_EQ(-NNN+1, indiv_test_2->getFitness()) << "Individual Subclass mutation (or fitness computation) not working";
	EXPECT_EQ(true, *indiv_test < *indiv_test_2) << "Comparison between individuals not working";
	list_individual_ptr children = indiv_test->crossWith(indiv_test_2);
	children.front()->setFitness();
	children.back()->setFitness();
	EXPECT_EQ(indiv_test->getFitness() + indiv_test_2->getFitness(), children.front()->getFitness() + children.back()->getFitness()) << "mother and father functions broken";
}

TEST(TivialProblem, polymorphism) {
	list_individual_ptr test;
	test.push_front(new Indivtest);
	test.front()->mutate();
	test.front()->setFitness();
	EXPECT_EQ(-NNN+1, test.front()->getFitness()) << "Saving a subclass* as an Individual* breaks fitness computation or mutation";
}

TEST(TivialProblem, population) {
	Population pop_test;
	list_individual_ptr init; //set of individuals that will initialize the population
	unsigned int i;
	for (i=0 ; i<NB_INDIV ; i++){init.push_front(new Indivtest);}
	pop_test.initParameters(NB_CHILDREN, NB_MUTANTS, NB_SURV_CHILD, NB_ELITES, NB_CONCUR);
	pop_test.initIndividuals(init);
	EXPECT_EQ(-NNN, pop_test[NB_INDIV%30]->getFitness()) << "building the population should compute fitness";
	vector<unsigned int> test = tournament(60, 4, 20, 10);
	ASSERT_EQ(80, test.size()) << "tournament function doesn t return the right number of individuals";
	pop_test.newGeneration();
	EXPECT_EQ( false , (pop_test.averageFitness()==-NNN) ) << "Population not evolving";
}



/////////////////////
// MAIN
/////////////////////

int main(int argc, char **argv) {
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
