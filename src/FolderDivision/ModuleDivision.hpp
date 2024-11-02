#ifndef __MODULEDIVISION_H__
#define __MODULEDIVISION_H__

constexpr const char *DBZ_MESSAGE = "Division by zero is not allowed!";

#include <stdexcept>
#include <iostream>

class DivisionByZero : public std::exception
{
public:
    virtual const char *what() const throw()
    {
        return DBZ_MESSAGE;
    }
};

struct Fraction
{
    long long numerator;
    long long denominator;
};

struct DivisionResult
{
    long long division;
    long long remainder;

    friend bool operator==(const DivisionResult &lhs, const DivisionResult &rhs)
    {
        return lhs.division == rhs.division ? lhs.remainder < rhs.remainder : lhs.division < rhs.division;
    }
};

class Division
{
public:
    explicit Division(Fraction fraction)
    {
        this->fraction = fraction;
    }

    ~Division() {
    };

    DivisionResult divide();

protected:
    Fraction fraction;
    DivisionResult result;
};

#endif // __MODULEDIVISION_H__