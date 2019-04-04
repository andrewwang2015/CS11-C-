#ifndef UVALUE_H
#define UVALUE_H

#include <string>
#include <set>
#include <vector>

using std::string;
/**
 * Class represents a "united-value" or a "value-with-units". 
 */
class UValue {
    double value;   /**< The actual value. */
    string units; /**< The units (i.e. "kg", "mi", etc.). */

public:
    UValue(double value, const string &unit);
    ~UValue();

    double get_value() const;
    string get_units() const;
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
        string from_units;
        double multiplier;
        string to_units;
    };

    /** Record the collection of conversions the object knows about */
    std::vector<Conversion> conversions; 


public:
    void add_conversion(const string &from_units, 
        const double multiplier, const string &to_units);
    UValue convert_to(const UValue &input, 
        const string &to_units) const;
    UValue convert_to(const UValue &input, const string &to_units, 
        std::set<string> seen) const;
};
#endif
