#ifndef __HELLOWORLD_H__
#define __HELLOWORLD_H__

constexpr const char *HelloContent()
{
    return "Hello World!";
}

constexpr const char *MessageContent()
{
    return "Message to World!";
}

constexpr const char *GoodByeContent()
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