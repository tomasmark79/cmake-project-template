#ifndef __HELLOWORLD_H__
#define __HELLOWORLD_H__

constexpr const char *HelloWorldContent()
{
    return "Hello World!";
}

constexpr const char *MessageWorldContent()
{
    return "Message to World!";
}

constexpr const char *GoodByeWorldContent()
{
    return "Good Bye World!";
}

class HelloWorld
{
public:
    HelloWorld() = default;
    ~HelloWorld() = default;

    void sayHello(void);
    void sayMessage(void);
    void sayGoodBye(void);
};

#endif // __HELLOWORLD_H__