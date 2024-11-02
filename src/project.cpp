#include "project.hpp"

#include "ModuleDivision.hpp"
#include "ModuleHelloWorld.hpp"

#include <iostream>

int main(int argc, char *argv[], char *env[])
{
    HelloWorld hw;
    hw.sayHello();

    std::cout << HEADER;
    
    Fraction f;

    if (argc != 3)
    {
        std::cout << USAGE;
        return 1;
    }

    f.numerator = atoll(argv[1]);
    f.denominator = atoll(argv[2]);

    Division d = Division(f);

    try
    {
        DivisionResult r = d.divide();

        std::cout << "Division  = " << f.numerator << " / " << f.denominator << " = " << r.division << "\n";
        std::cout << "Remainder = " << f.numerator << " % " << f.denominator << " = " << r.remainder << "\n";
    }
    catch (DivisionByZero)
    {
        std::cout << "Divided by zero!\n";
    }

    return 0;
}
