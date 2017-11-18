// Class representing one solution to the TSP

#include <vector>
using namespace std;

class TSPGenome{

private:
	vector<int> order;
	double circuitLength;
	static const int DUMMY_LENGTH = 1e9;

public:
	// Constructors
	TSPGenome() {};
	TSPGenome(int numPoints);
	TSPGenome(const vector<int> &order);

	// Destructor
	~TSPGenome() {}

	// Accessor methods
	vector<int> getOrder() const;
	double getCircuitLength() const;

	// Mutator methods
	void computeCircuitLength(const vector<Point> &points);
	void mutate();
};

// Additional functions not part of TSPGenome
TSPGenome crosslink(const TSPGenome &g1, const TSPGenome &g2);

TSPGenome findAShortPath(const vector<Point> &points,
	int populationSize, int numGenerations, int keepPopulation,
	int numMutations);

bool isShorterPath(const TSPGenome &g1, const TSPGenome &g2);