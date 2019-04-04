#include "units.h"
#include <iostream>

using namespace std;

/**
 * Initializes a UnitConverter object with predefined conversions.
 * @return UnitConverter object with predefined conversions
 */
UnitConverter init_converter() {
    UnitConverter unit_converter;
    unit_converter.add_conversion("mi", FT_IN_MI, "ft");
    unit_converter.add_conversion("mi", KM_IN_MI, "km");
    unit_converter.add_conversion("ft", IN_IN_FT, "in");

    unit_converter.add_conversion("in", CM_IN_IN, "cm");
    unit_converter.add_conversion("lb", KG_IN_LB, "kg");
    unit_converter.add_conversion("stone", LB_IN_STONE, "lb");
    unit_converter.add_conversion("lb", OZ_IN_LB, "oz");

    unit_converter.add_conversion("kg", G_IN_KG, "g");
    unit_converter.add_conversion("gal", L_IN_GAL, "L");
    unit_converter.add_conversion("bushel", GAL_IN_BUSHEL, "gal");
    unit_converter.add_conversion("ft^3", GAL_IN_CUBIC_FT, "gal");

    unit_converter.add_conversion("L", ML_IN_L, "ml");

    return unit_converter;
}
/**
 * Main method that allows user to convert from one UValue to another.
 * @return n/a
 */
int main() {
    UnitConverter u = init_converter();

    // Get user input for conversion
    string from_units;
    double from_value;
    cout << "Enter value with units: ";
    cin >> from_value >> from_units;
    UValue from_U{from_value, from_units};

    string to_units;
    cout << "Convert to units: ";
    cin >> to_units;
    try {
        UValue converted_U = u.convert_to(from_U, to_units);      
        // Successful conversion
        cout << "Converted to: " << converted_U.get_value() << " " << 
            to_units << endl;
    } catch (invalid_argument &e) {
        cout << "Couldn't convert to " << to_units << "!" << endl;
        cout << e.what() << endl;
    }
    return 0;
}