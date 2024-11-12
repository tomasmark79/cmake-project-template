#ifndef __APP_H__
#define __APP_H__

#include <map>
#include <string>

class App
{
public:
    using p_fun = void (*)();
    App(int argc, char **argv, int retValue = 0);
    ~App() = default;

private:
    static std::map<std::string, p_fun> options;
    static std::string_view HEADER;
    static std::string_view USAGE;
    
};
#endif // __APP_H__