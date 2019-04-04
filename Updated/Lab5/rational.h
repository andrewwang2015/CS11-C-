#ifndef RATIONAL_H
#define RATIONAL_H

#include <iostream>

/**
 * Class represents rational numbers, represented as numerator/denominator
 */
class Rational {
    int numerator;   /**< The numerator of the rational. */
    int denominator; /**< The denominator of the rational. */

public:
    Rational(int n = 0, int d = 1);

    int num() const;
    int denom() const;
    Rational reciprocal() const;
    void reduce();
    /** Compound assignment operator overloads */
    Rational& operator+=(const Rational &rhs);
    Rational& operator-=(const Rational &rhs);
    Rational& operator*=(const Rational &rhs);
    Rational& operator/=(const Rational &rhs);

    /** Comparison assignment operator overloads */
    bool operator==(const Rational &rhs) const;
    bool operator!=(const Rational &rhs) const;

private: 
    int gcd(int a, int b) const;
};

/** Non member functions */

/** Binary arithmetic operator overloads */
Rational operator+(const Rational &r1, const Rational &r2);
Rational operator-(const Rational &r1, const Rational &r2);
Rational operator*(const Rational &r1, const Rational &r2);
Rational operator/(const Rational &r1, const Rational &r2);

std::ostream& operator<<(std::ostream &os, const Rational &r); 

#endif 
