#include "units.h"
#include <iostream>
#include <fstream>
#include <stdexcept>

using namespace std;

/**
 * Initializes a UnitConverter object with predefined conversions from a file.
 * @param filename name of file which contains conversion information.
 * @return UnitConverter object with predefined conversions
 */
UnitConverter init_converter(const string& filename) {
    UnitConverter unit_converter;

    // Load file 
    ifstream ifs{filename};

    // Ensure file was opened successfully
    if (!ifs) {
        string error_msg = "Failed to open " + filename;
        throw invalid_argument(error_msg);
    }

    // Read data until we hit EOF 
    while (ifs) {
        // Each line is of form (from-units, multiplier, to-units)
        string from_units;
        double multiplier;
        string to_units;
        ifs >> from_units >> multiplier >> to_units;
        unit_converter.add_conversion(from_units, multiplier, to_units);
    }
    return unit_converter;
}
/**
 * Main method that allows user to convert from one UValue to another.
 * @return n/a
 */
int main() {
    UnitConverter u = init_converter("conversions.txt");

    // Get user input for conversion
    string from_units;
    double from_value;
    cout << "Enter value with units: ";
    cin >> from_value >> from_units;
    UValue from_U(from_value, from_units);

    string to_units;
    cout << "Convert to units: ";
    cin >> to_units;
    try {
        UValue converted_U = u.convert_to(from_U, to_units);      
        // Successful conversion
        cout << "Converted to: " << converted_U.get_value() << " " << to_units << endl;
    } catch (invalid_argument e) {
        cout << "Couldn't convert to " << to_units << "!" << endl;
        cout << e.what() << endl;
    }
    return 0;
}
