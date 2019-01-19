
#ifndef UVALUE_H
#define UVALUE_H

const double LB_IN_KG = 0.45;
const double GAL_IN_L = 3.79;
const double MI_IN_KM = 1.6;

#include <string> 
/* 
 * Class represents a "united-value" or a "value-with-units". 
 */
class UValue {
    // Actual value 
    double value;
    // The units (i.e. "kg", "mi", etc.)
    std::string units;

public:
    UValue(double value, std::string unit);
    ~UValue();

    double get_value();
    std::string get_units();
};

UValue convert_to(UValue input, std::string to_units);
#endif