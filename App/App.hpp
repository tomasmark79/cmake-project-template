#ifndef __APP_H__
#define __APP_H__

#include <map>
#include <string>
#include <string_view>


class App
{
public:
    using p_fun = void (*)();

    App() = default;
    ~App() = default;
    
    App(const App &) = delete;
    App &operator=(const App &) = delete;
    
    App(App &&) = delete;
    App &operator=(App &&) = delete;
    
    static int AppInit(int argc, char **argv);

private:
    static std::map<std::string, p_fun> options;
    static std::string_view HEADER;
    static std::string_view USAGE;
    
};

#endif // __APP_H__