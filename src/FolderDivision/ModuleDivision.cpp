#include "ModuleDivision.hpp"

DivisionResult Division::divide()
{
    if (fraction.denominator == 0L)
        throw DivisionByZero();

    DivisionResult result = DivisionResult{
        fraction.numerator / fraction.denominator,
        fraction.numerator % fraction.denominator};

    return result;
}
