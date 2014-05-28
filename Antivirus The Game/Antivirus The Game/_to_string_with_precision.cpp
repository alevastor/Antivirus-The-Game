#include "main.h"
#include <sstream>
#include <iomanip>

string to_string_with_precision(float a_value, int n)
{
    ostringstream out;
    out << setprecision(n) << a_value;
    return out.str();
}