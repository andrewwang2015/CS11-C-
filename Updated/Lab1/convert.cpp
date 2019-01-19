#include "units.h"
#include <iostream>

using namespace std;
/**
 * Main method that allows user to convert from one UValue to another.
 * @return n/a
 */
int main() {
    string from_units;
    double from_value;
    cout << "Enter value with units: ";
    cin >> from_value >> from_units;
    UValue from_U(from_value, from_units);

    string to_units;
    cout << "Convert to units: ";
    cin >> to_units;

    UValue converted_U = convert_to(from_U, to_units);

    if (converted_U.get_units() == to_units) {
        // Successful conversion
        cout << "Converted to: " << converted_U.get_value() << " " << to_units << endl;
    } else {
        // Failed to convert
        cout << "Couldn't convert to " << to_units << "!" << endl;
    }
    return 0;
}