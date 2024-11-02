cmake_minimum_required(VERSION 3.5)

# Set the project name
project(ModuleHelloWorld C CXX)

# Set the source files
set(SOURCE_FILES
    ModuleHelloWorld.hpp    
    ModuleHelloWorld.cpp
)

# Add the library as SHARED or STATIC 
add_library(ModuleHelloWorld SHARED STATIC ${SOURCE_FILES})

# Install the library
install(TARGETS ModuleHelloWorld DESTINATION ${THIS_INSTALL_LIB_DIR})

# Install the header files
install(FILES ModuleHelloWorld.hpp DESTINATION ${THIS_INSTALL_INCLUDE_DIR})
