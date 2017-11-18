#include <iostream>
#include <vector>
#include <algorithm>
#include "Point.hh"
#include "tsp-ga.hh"
#include <ctime>
#include <cstdlib>

using namespace std;

int main(int argc, char **argv)
{
	if (argc != 5)
	{
		cout << "usage: ./tsp-ga population generations keep mutate" << endl;
		exit(1);
	}
	int population = atoi(argv[1]);
	int generations = atoi(argv[2]);
	float keep = atof(argv[3]);
	float mutate = atof(argv[4]);

	srand(time(nullptr));

	vector<Point> allPoints;
	int numPoints;
	cout << "How many points? ";
    cin >> numPoints;
    if (numPoints == 0) {
    	return 0;
    }
    for (int i = 0; i < numPoints; i++)
    {
    	double x,y,z;
    	cout << "Point " << i << ": ";
    	cin >> x >> y >> z;
    	Point tempPoint = Point(x,y,z);
    	allPoints.push_back(tempPoint);
    }
    TSPGenome best = findAShortPath(allPoints, population,
    	generations, int(keep * population), 
    	int (mutate * population));
    vector<int> bestOrder = best.getOrder();
    best.computeCircuitLength(allPoints);
   	double minLength = best.getCircuitLength();
    cout << "Best order: [";
    for (unsigned int i = 0 ; i < bestOrder.size()-1; i++){
    	cout << bestOrder[i] << " ";
    }
    cout << bestOrder[bestOrder.size()-1] << "]" << endl;
    cout << "Shortest distance: " << minLength << endl;
	return 0;
}


