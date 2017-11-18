#include "Point.hh"
#include <cmath>

// Default constructor:  initializes the point to (0, 0, 0).
Point::Point() {
  x_coord = 0;
  y_coord = 0;
  z_coord = 0;
}

// Initializes the point to (x, y, z).
Point::Point(double x, double y, double z) {
  x_coord = x;
  y_coord = y;
  z_coord = z;
}

// Destructor - Point allocates no dynamic resources.
Point::~Point() {
  // no-op
}

// Mutators:

void Point::setX(double val) {
  x_coord = val;
}

void Point::setY(double val) {
  y_coord = val;
}

void Point::setZ(double val) {
  z_coord = val;
}

// Accessors:

double Point::getX() const{
  return x_coord;
}

double Point::getY() const{
  return y_coord;
}

double Point::getZ() const{
  return z_coord;
}

// Returns distance between this point and another
double Point::distanceTo(const Point &other) const{
  double x_distance = other.getX() - this->getX();
  double y_distance = other.getY() - this->getY();
  double z_distance = other.getZ() - this->getZ();
  return sqrt(x_distance * x_distance + y_distance * y_distance + 
    z_distance * z_distance);
}