#include "units.h"
#include <stdexcept>
using namespace std;

/**
 * Constructor for UValue. Takes in a value and a unit.
 */
UValue::UValue(double value, string units) {
    this->value = value;
    this->units = units;
}


/**
 * Getter method for value
 * @return value
 */
double UValue::get_value() {
    return value;
}

/**
 * Getter method for units
 * @return units
 */
string UValue::get_units() {
    return units;
}

/**
 * Adds a conversion to collection of past conversions. 
 * Throws invalid_argument exception if conversion already exists.
 * @param from_units:   unit to convert from
 * @param multiplier:   actual value to convert
 * @param to_units:     unit to convert to
 */
void UnitConverter::add_conversion(string from_units, double multiplier, string to_units) {
    // First test if conversion exists. 
    for (Conversion c: conversions) {
        if (c.from_units == from_units && c.to_units == to_units) {
            string error_msg = "Already have a conversion from " + from_units + " to " + to_units;
            throw invalid_argument(error_msg);
        }
    }
    // If conversion does NOT exist, then we add it 
    conversions.push_back({from_units, multiplier, to_units});

    // If we know conversion one way, then we also know it the other way
    conversions.push_back({to_units, 1/multiplier, from_units});

}
/**
 * Converts from one UValue to another.
 * Throws invalid_argument exception if conversion information does not exist.
 * @param input: The UValue to convert    
 * @param to_units: The unit to convert to.
 * @return the converted UValue.
 */
UValue UnitConverter::convert_to(UValue input, string to_units) {
    string input_units = input.get_units();
    double input_value = input.get_value();

    // Search for conversion info.
    for (Conversion c: conversions) {
        if (c.from_units == input_units && c.to_units == to_units) {
            return UValue{input_value * c.multiplier, to_units};
        }
    }

    // If it reaches this point, then we know that no conversion info exists.
    string error_msg = "Don't know how to convert from " + input_units + " to " + to_units;
    throw invalid_argument(error_msg);
}