#include "units.h"
#include <stdexcept>
#include <set>
using namespace std;

/**
 * Constructor for UValue. Takes in a value and a unit.
 */
UValue::UValue(double value, string units) {
    this->value = value;
    this->units = units;
}
UValue::~UValue() {
    // No dynamically allocated resources
}

/**
 * Getter method for value
 * @return value
 */
double UValue::get_value() const {
    return value;
}

/**
 * Getter method for units
 * @return units
 */
string UValue::get_units() const {
    return units;
}

/**
 * Adds a conversion to collection of past conversions. 
 * Throws invalid_argument exception if conversion already exists.
 * @param from_units:   unit to convert from
 * @param multiplier:   actual value to convert
 * @param to_units:     unit to convert to
 */
void UnitConverter::add_conversion(const string &from_units, const double multiplier, const string &to_units) {
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
 * Converts from one UValue to another. Wrapper function for convert_to that takes 
 * three arguments.
 * @param input: The UValue to convert    
 * @param to_units: The unit to convert to.
 * @return the converted UValue.
 */
UValue UnitConverter::convert_to(const UValue &input, const string &to_units) const {
    return convert_to(input, to_units, set<string> {});
}

/**
 * Converts from one UValue to another.
 * Throws invalid_argument exception if conversion information does not exist.
 * @param input: The UValue to convert    
 * @param to_units: The unit to convert to.
 * @param seen_units: Set of units already seen. This prevents infinite recursion.
 * @return the converted UValue.
 */
UValue UnitConverter::convert_to(const UValue &input, const string &to_units, set<string> seen_units) const {
    string input_units = input.get_units();
    double input_value = input.get_value();

    seen_units.insert(input_units);


    // Search for conversion info.
    for (const Conversion &c: conversions) {
        if (c.from_units == input_units && c.to_units == to_units) {
            return UValue(input_value * c.multiplier, to_units);
        } else {
            // If we cannot convert directly, then we do indirect conversion by 
            // switching units
            if (c.from_units == input_units && !seen_units.count(c.to_units)) {
                // Convert input to c.to_units 
                UValue input_convert = UValue(input_value * c.multiplier, c.to_units);

                // We need try, catch block to prevent dead ends.
                try {
                    return convert_to(input_convert, to_units, seen_units);                   
                } catch (invalid_argument e) {
                    // Ignore exception to move onto next conversion
                }

            }
        }
    }

    // If it reaches this point, then we know that no conversion info exists.
    string error_msg = "Don't know how to convert from " + input_units + " to " + to_units;
    throw invalid_argument(error_msg);
}
