
#ifndef UVALUE_H
#define UVALUE_H

const double FT_IN_MI = 5280;
const double KM_IN_MI = 1.6;
const double IN_IN_FT= 12;
const double CM_IN_IN = 2.54;

const double KG_IN_LB = 0.45;
const double LB_IN_STONE = 14;
const double OZ_IN_LB = 16;

const double G_IN_KG = 1000;
const double L_IN_GAL = 3.79;
const double GAL_IN_BUSHEL = 9.3;
const double GAL_IN_CUBIC_FT = 7.5;

const double ML_IN_L = 1000;


#include <string> 
#include <vector>
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

/**
 * Class keeps track of all conversion we know how to perform.
 */
class UnitConverter {
    /**
     * This struct represents information required for a conversion. Contains 
     * unit to convert from, the actual value, and the unit to convert to.
     */
    struct Conversion {
        std::string from_units;
        double multiplier;
        std::string to_units;
    };

    // Record the collection of conversions the object knows about
    std::vector<Conversion> conversions; 


public:
    void add_conversion(std::string from_units, double multiplier, std::string to_units);
    UValue convert_to(UValue input, std::string to_units);
};
#endif