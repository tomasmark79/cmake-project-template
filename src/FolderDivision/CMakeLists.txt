cmake_minimum_required(VERSION 3.5)

# Set the project name
project(ModuleDivision C CXX)

# Set the source files
set(SOURCE_FILES
    ModuleDivision.hpp    
    ModuleDivision.cpp
)

# Add the library as SHARED or STATIC 
add_library(ModuleDivision SHARED STATIC ${SOURCE_FILES})

# Install the library
install(TARGETS ModuleDivision DESTINATION ${THIS_INSTALL_LIB_DIR})

# Install the header files
install(FILES ModuleDivision.hpp DESTINATION ${THIS_INSTALL_INCLUDE_DIR})
