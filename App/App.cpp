#include <iostream>

#include "App.hpp"

// folders definition
#include "HelloWorld.hpp"
HelloWorld hw;

std::string_view App::HEADER = "Cmake Project Template 0.0.1 - Copyright (c) 2024 Tomas Mark";
std::string_view App::USAGE = R"(
Usage: AppName [arg1] [arg2]

Option:
--option1 (Description option1)
--option2 (Description option2)
--option3 (Description option3)
)";

// arguments asoociated with functions
std::map<std::string, App::p_fun> App::options = {
    {"--option1", []()
     { hw.sayHello(); }},
    {"--option2", []()
     { hw.sayMessage(); }},
    {"--option3", []()
     { hw.sayGoodBye(); }},

};

int App::AppInit(int argc, char **argv)
{
    int successfullyProcessedOptions = 0;
    try
    {
        // no argument cause return
        if (argc == 1)
        {
            std::cout << App::HEADER << std::endl;
            return 0;
        }

        // go through all received arguments
        for (int argvIndex = 1; argvIndex < argc; ++argvIndex)
        {

            if ((argv[argvIndex][0] != '-') || (argv[argvIndex][1] != '-'))
            {
                throw std::runtime_error("!");
            }

            for (auto &option : options)
            {
                if (argv[argvIndex] == option.first)
                {
                    option.second();
                    successfullyProcessedOptions++;
                }
            }
        }
    }
    catch (std::exception &e)
    {
        std::cout << App::USAGE << std::endl;
        return 0;
    }

    return (successfullyProcessedOptions > 0) ? 1 : 0;
}

int main(int argc, char **argv)
{
    int retValue = App::AppInit(argc, argv);
    std::cout << "App finished with return value: " << retValue << std::endl;
    return retValue;
}
