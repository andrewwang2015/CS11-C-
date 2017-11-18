#include "Point.hh"
#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

// Calculates total distance of round trip of points as specified by order
double circuitLength(const vector<Point> &points, const vector<int> &order){
  double length = 0.0;
  for (unsigned int i = 0; i < order.size()-1 ; i++){
    Point firstPoint = points[order[i]];
    Point nextPoint = points[order[i+1]];
    length += firstPoint.distanceTo(nextPoint);
  }
  length += points[order[0]].distanceTo(points[order[points.size()-1]]);
  return length;
}

// Brute forces combinations of paths to find overall shortest path and 
// length. Returns the optimal order.
vector<int> findShortestPath(const vector <Point> &points){
  vector<int> order;

  double minLength = INT_MAX;
  for (unsigned int i = 0; i < points.size(); i++){
    order.push_back(i);
  }
  vector<int> shortestOrder = order;
  do{
    double currentLength = circuitLength(points, order);
    if (currentLength < minLength){
      minLength = currentLength;
      shortestOrder = order;
    }
  } while (next_permutation(order.begin(), order.end()));
  return shortestOrder;

}

int main(){
  vector<Point> allPoints;
  int numPoints;
  cout << "How many points? ";
  cin >> numPoints;
  if (numPoints == 0) {
    return 0;
  }
  for (int i = 0; i < numPoints; i++){
    double x, y, z;
    cout << "Point " << i << ": " ;
    cin >> x >> y >> z;
    Point tempPoint = Point(x, y, z);
    allPoints.push_back(tempPoint);
  }
  vector<int> bestOrder = findShortestPath(allPoints);
  double minLength = circuitLength(allPoints, bestOrder);
  cout << "Best order: [";
  for (unsigned int i = 0 ; i < bestOrder.size()-1; i++){
    cout << bestOrder[i] << " ";
  }
  cout << bestOrder[bestOrder.size()-1] << "]" << endl;
  cout << "Shortest distance: " << minLength << endl;
  return 0;
}