#include "Point.hh"
#include <cmath>
#include <iostream>

using namespace std;

// Uses Heron's Formula to calculate area given three points
double computeArea(Point &a, Point &b, Point&c){
  double sideLength1 = a.distanceTo(b);
  double sideLength2 = b.distanceTo(c);
  double sideLength3 = c.distanceTo(a);
  double semiperimeter = (sideLength1 + sideLength2 + sideLength3) / 2.0;
  double area = sqrt(semiperimeter * (semiperimeter - sideLength1) * 
    (semiperimeter - sideLength2) * (semiperimeter - sideLength3));
  return area;
}

int main(){
  double x, y, z;
  cout << "Point 1: ";
  cin >> x >> y >> z;

  Point point1(x,y,z);

  cout << "Point 2: ";
  cin >> x >> y >> z;

  Point point2(x,y,z);

  cout << "Point 3: ";
  cin >> x >> y >> z;

  Point point3(x,y,z);

  cout << "Area is: " << computeArea(point1, point2, point3) << endl;

}