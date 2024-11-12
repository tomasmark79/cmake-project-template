#include <iostream>

#include "App.hpp"

// folders
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



std::map<std::string, App::p_fun> App::options = {
    {"--option1", []()
     { hw.sayHello(); }},
    {"--option2", []()
     { hw.sayMessage(); }},
    {"--option3", []()
     { hw.sayGoodBye(); }},

};

App::App(int argc, char **argv, int retValue)
{
    try
    {
        // no argument
        if (argc == 1)
        {
            std::cout << App::HEADER << std::endl;
            retValue = 0;
            return;
        }

        // go through all received arguments
        for (int argvIndex = 1; argvIndex < argc; ++argvIndex)
        {
            if ( (argv[argvIndex][0] != '-') || (argv[argvIndex][1] != '-') )
            {
                throw std::runtime_error("!");
            }
            else
            {
                for (auto &option : options)
                {
                    if (argv[argvIndex] == option.first)
                    {
                        option.second();
                    }
                }
            }
        }
    }
    catch (std::exception &e)
    {
        std::cout << App::USAGE << std::endl;
        retValue = 0;
        return;
    }
}

int main(int argc, char **argv)
{
    int retValue = 0;
    App(argc, argv, retValue);
    return retValue;
}
