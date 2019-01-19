#include "rational.h"
#include <iostream>
#include <stdexcept>
#include <cmath>

#define MIN(a, b) ((a < b) ? a : b)
#define MAX(a, b) ((a > b) ? a : b) 

using namespace std;

/**
 * Constructor for Rational class. Throws invalid argument 
 * exception if input denominator is 0.
 * @param n numerator 
 * @param d denominator 
 */
Rational::Rational(int n, int d) {
    if (d == 0) {
        throw invalid_argument("Denominator cannot be 0.");
    } else if (d < 0) {
        /** Invert sign so denominator is always positive */
        d *= -1;
        n *= -1;
    }
    this->numerator = n;
    this->denominator = d;
}

/**
 * Destructor for Rational class. There are no 
 * dynamically allocated resources so nothing is done.
 */
Rational::~Rational() {}

/**
 * Getter method that returns the numerator
 * @return the numerator
 */
int Rational::num() const{
    return numerator;
}

/** 
 * Getter method that returns the denominator
 * @return the denominator
 */
int Rational::denom() const {
    return denominator;
}

/**
 * Returns a Rational object containing the reciprocal
 * of the number. Does not mutate the original object.
 * @return   the reciprocal of the input
 */
Rational Rational::reciprocal() const {
    return Rational(this->denom(), this->num());
}

/**
 * Reduces a rational number such that the GCD of the numerator
 * and denonminator is 1. Mutates the original object.
 */
void Rational::reduce() {
    /**
     * If numerator is 0, modify number to be 0/1.
     */
    if (numerator == 0) {
        denominator = 1;
        return;
    }
    int factor = gcd(numerator, denominator);
    numerator = numerator/factor;
    denominator = denominator/factor;
}
/**
 * Returns the greatest common divisor of two numbers 
 * @param  a the first number
 * @param  b the second number
 * @return   the greatest common divisor 
 */
int Rational::gcd(int a, int b) const {
    if (a == 0 || b == 0) {
        throw invalid_argument("GCD only takes non-zero args.");
    }
    /** Take absolute value of inputs. */
    a = abs(a);
    b = abs(b);
    int smaller = MIN(a,b);
    int bigger = MAX(a, b);
    for (int i = smaller; i > 0; i--) {
        if (smaller % i == 0 && bigger % i == 0) {
            return i;
        }
    }
    return 1;
}

/**
 * Operator overload for += of a Rational
 * @param rhs rational to add to this
 * @return reference to the current rational after addition
 */
Rational& Rational::operator+=(const Rational &rhs) {
    /** 
     * 1) Get common denominators for both rationals 
     * 2) Add numerators together 
     * 3) Reduce
     */
    
    /** Make copies of variables in case of self assigmnent */
    int num = rhs.num();
    int den = rhs.denom();
    numerator *= den;
    numerator += num * denominator;
    denominator *= den;
    reduce();
    return *this;
}

/**
 * Operator overload for -= of a Rational
 * @param rhs rational to subtract from this
 * @return reference to the current rational after subtraction
 */
Rational& Rational::operator-=(const Rational &rhs) {
    int num = rhs.num();
    int den = rhs.denom();
    numerator *= den;
    numerator -= num * denominator;
    denominator *= den;
    reduce();
    return *this;
}

/**
 * Operator overload for *= of a Rational
 * @param rhs rational to multiply this by
 * @return reference to the current rational after multiplication
 */
Rational& Rational::operator*=(const Rational &rhs) {

    numerator *= rhs.numerator;
    denominator *= rhs.denominator;
    reduce();

    return *this;
}

/**
 * Operator overload for /= of a Rational
 * @param rhs rational to divide this by
 * @return reference to the current rational after division
 */
Rational& Rational::operator/=(const Rational &rhs) {
    Rational recip = rhs.reciprocal();
    (*this) *= recip;
    
    return *this;
}

/**
 * Comparison overload for == of a Rational
 * @param rhs rational to compare this to
 * @return true if the two Rationals are equal else false
 */
bool Rational::operator==(const Rational &rhs) {
    /** Make copy because we want to reduce before comparison */
    Rational rhs_c = rhs;
    rhs_c.reduce();
    this->reduce();
    return this->num() == rhs_c.num() && 
        this->denom() == rhs_c.denom();
}

/**
 * Comparison overload for != of a Rational
 * @param rhs rational to compare this to
 * @return true if the two Rationals are NOT equal else false
 */
bool Rational::operator!=(const Rational &rhs) {
    return !(*this == rhs);
}


/**
 * Operator overload for addition of two rationals.
 * @param r rational 1
 * @param r1 rational 2
 * @return the sum of the two rationals
 */
Rational operator+(const Rational &r, const Rational &r1) {
    return Rational{r} += r1;
}

/**
 * Operator overload for subtraction of two rationals.
 * @param r rational 1
 * @param r1 rational 2
 * @return the difference of the two rationals
 */
Rational operator-(const Rational &r, const Rational &r1) {
    return Rational{r} -= r1;
}

/**
 * Operator overload for multiplication of two rationals.
 * @param r rational 1
 * @param r1 rational 2
 * @return the product of the two rationals
 */
Rational operator*(const Rational &r, const Rational &r1) {
    return Rational{r} *= r1;
}

/**
 * Operator overload for division of two rationals.
 * @param r rational 1
 * @param r1 rational 2
 * @return the quotient of the two rationals
 */
Rational operator/(const Rational &r, const Rational &r1) {
    return Rational{r} /= r1;
}

/**
 * Overload of stream-output
 * @param os the stream 
 * @stream r the rational to output 
 * return implementation of ostream specific for Rational
 */
ostream& operator<<(std::ostream &os, const Rational &r) {
    /** If denominator is 1, simply output the numerator. */
    if (r.denom() == 1) {
        os << r.num();
    } else {
        os << r.num() << "/" << r.denom();
    }
    return os;
}
