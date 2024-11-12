#include "HelloWorld.hpp"

#include <iostream>
#include <string>

void HelloWorld::sayHello()
{
    std::cout << HelloWorldContent() << std::endl;
}

void HelloWorld::sayMessage()
{
    std::cout << MessageWorldContent() << std::endl;
}

void HelloWorld::sayGoodBye()
{
    std::cout << GoodByeWorldContent() << std::endl;
}
