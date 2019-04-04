#include "units.h"
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
 * Converts from one UValue to another.
 * @param input: The UValue to convert    
 * @param to_units: The unit to convert to.
 * @return the converted UValue.
 */
UValue convert_to(UValue input, string to_units) {

    string input_units = input.get_units();
    double input_value = input.get_value();

    if (input_units == "lb" && to_units == "kg") {
        return UValue{LB_IN_KG * input_value, to_units};
    } else if (input_units == "gal" && to_units == "L") {
        return UValue{GAL_IN_L * input_value, to_units};
    } else if (input_units == "mi" && to_units == "km") {
        return UValue{MI_IN_KM * input_value, to_units};
    } else {
        // If we don't know how to convert, just return the input
        return input;
    }
}