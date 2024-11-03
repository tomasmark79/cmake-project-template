#include "project.hpp"

#include "ModuleHelloWorld.hpp"

#include <iostream>

int main(int argc, char *argv[], char *env[])
{
    std::cout << HEADER;

    HelloWorld hw;
    hw.sayHello();

    return 0;
}
