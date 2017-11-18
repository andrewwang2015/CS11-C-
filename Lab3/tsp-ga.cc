#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <cstdlib>
#include <cassert>
#include "Point.hh"
#include "tsp-ga.hh"

using namespace std;

// Constructor that initializes order vector to be random
// shuffling of numbers from 0 to numPoints - 1. 
// Sets circuitLength to be dummyLength.
TSPGenome::TSPGenome(int numPoints)
{
	for (int i = 0; i < numPoints; i++)
	{
		this->order.push_back(i);
	}
	random_shuffle(order.begin(), order.end());
	this->circuitLength = this->DUMMY_LENGTH;
}

// Constructor that takes a preset ordering.
// Sets circuitLength to be dummyLength
TSPGenome::TSPGenome(const vector<int> &order)
{
	this->order = order;
	this->circuitLength = this->DUMMY_LENGTH;
}

// Accessor method to return circuit length
double TSPGenome::getCircuitLength() const
{
	return this->circuitLength;
}

// Accessor method to return order
vector<int> TSPGenome::getOrder() const
{
	return this->order;
}

// Calculates total distance of round trip of points as specified by order
void TSPGenome::computeCircuitLength(const vector<Point> &points){
  double length = 0.0;
  for (unsigned int i = 0; i < order.size()-1 ; i++){
    Point firstPoint = points[this->order[i]];
    Point nextPoint = points[this->order[i+1]];
    length += firstPoint.distanceTo(nextPoint);
  }
  length += points[this->order[0]].distanceTo(points[this->order[points.size()-1]]);
  this->circuitLength = length;
}

// Mutates genome/ordering by swapping two randomly-selected values
// in the order vector. 
void TSPGenome::mutate()
{
	int index1 = 0;
	int index2 = 0;
	do
	{
		index1 = rand() % this->order.size();
		index2 = rand() % this->order.size();

	} while (index1 == index2);
	assert(index1 != index2);
	swap(this->order[index1], this->order[index2]);
}

// Generates offspring for genetic algorithm
TSPGenome crosslink(const TSPGenome &g1, const TSPGenome &g2)
{
	assert(g1.getOrder().size() == g2.getOrder().size());
	set<int> visited;
	vector<int> newOrder;
	int i = rand() % g1.getOrder().size();
	for (int j = 0; j < i; j++)
	{
		newOrder.push_back(g1.getOrder()[j]);
		visited.insert(g1.getOrder()[j]);
	}

	for (int num : g2.getOrder())
	{
		if (!visited.count(num))
		{
			newOrder.push_back(num);
		}
	}
	assert(newOrder.size() == g1.getOrder().size());
	TSPGenome temp = TSPGenome(newOrder);
	return temp;
}

// Returns true if g1 has SHORTER circuit length than g2
bool isShorterPath(const TSPGenome &g1, const TSPGenome &g2)
{
	return g1.getCircuitLength() < g2.getCircuitLength();
}
// For finding a short path
TSPGenome findAShortPath(const vector<Point> &points,
	int populationSize, int numGenerations, int keepPopulation,
	int numMutations)
{
	vector<TSPGenome> initialPopulation;
	for (int i = 0; i < populationSize; i++)
	{
		initialPopulation.push_back(TSPGenome(points.size()));
	}
	for (int j = 0; j < numGenerations; j++)
	{
		for (int i = 0; i < populationSize; i++)
		{
			initialPopulation[i].computeCircuitLength(points);
		}

		sort(initialPopulation.begin(), initialPopulation.end(), isShorterPath);
		if (j % 10 == 0)
		{
			cout << "Generation " << j << ": shortest path is " 
			<< initialPopulation[0].getCircuitLength() << endl;
		}

		// Keep N fittest members, replace remaining members with new genomes produced
		// from fittest ones.

		for (int i = keepPopulation; i < populationSize; i++)
		{
			int temp1 = rand() % keepPopulation;
			int temp2 = rand() % keepPopulation;
			while (temp1 == temp2)
			{
				temp2 = rand() % keepPopulation;
			}
			initialPopulation[i] = crosslink(initialPopulation[temp1], initialPopulation[temp2]);
		}

		// Mutate the population
		for (int i = 0; i < numMutations; i++)
		{
			int randIndex = rand() % (populationSize - 1) + 1;
			initialPopulation[randIndex].mutate();
		}

	}
	return initialPopulation[0];   // The fittest 

}
