cmake_minimum_required(VERSION 3.28)
# Copyright (c) 2024 Tomas Mark

# Library project name
project(HelloWorld)

# Set the source files
set(SOURCE_FILES
    HelloWorld.hpp    
    HelloWorld.cpp
)

# Add the library as SHARED or STATIC 
add_library(HelloWorld SHARED STATIC ${SOURCE_FILES})

# Install the library
install(TARGETS HelloWorld DESTINATION ${THIS_INSTALL_LIB_DIR})

# Install the header files
install(FILES HelloWorld.hpp DESTINATION ${THIS_INSTALL_INCLUDE_DIR})
