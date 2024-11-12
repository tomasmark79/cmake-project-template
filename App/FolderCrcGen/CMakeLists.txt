cmake_minimum_required(VERSION 3.28)
# Copyright (c) 2024 Tomas Mark

# Library project name
project(CrcGen)

# Set the source files
set(SOURCE_FILES
    CrcGen.hpp    
    CrcGen.cpp
)

# Add the library as SHARED or STATIC 
add_library(CrcGen SHARED STATIC ${SOURCE_FILES})

# Install the library
install(TARGETS CrcGen DESTINATION ${THIS_INSTALL_LIB_DIR})

# Install the header files
install(FILES CrcGen.hpp DESTINATION ${THIS_INSTALL_INCLUDE_DIR})
