#ifndef UVALUE_H
#define UVALUE_H

#include <string>
#include <set>
#include <vector>
/**
 * Class represents a "united-value" or a "value-with-units". 
 */
class UValue {
    double value;   /**< The actual value. */
    std::string units; /**< The units (i.e. "kg", "mi", etc.). */

public:
    UValue(double value, std::string unit);
    ~UValue();

    double get_value() const;
    std::string get_units() const;
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

    /** Record the collection of conversions the object knows about */
    std::vector<Conversion> conversions; 


public:
    void add_conversion(const std::string &from_units, const double multiplier, const std::string &to_units);
    UValue convert_to(const UValue &input, const std::string &to_units) const;
    UValue convert_to(const UValue &input, const std::string &to_units, std::set<std::string> seen) const;
};
#endif
