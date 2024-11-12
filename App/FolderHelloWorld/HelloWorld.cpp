#include "HelloWorld.hpp"

#include <iostream>
#include <string>

// example class

void HelloWorld::sayHello()
{
    std::cout << HelloContent() << std::endl;
}

void HelloWorld::sayMessage()
{
    std::cout << MessageContent() << std::endl;
}

void HelloWorld::sayGoodBye()
{
    std::cout << GoodByeContent() << std::endl;
}
