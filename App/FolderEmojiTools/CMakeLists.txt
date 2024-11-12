cmake_minimum_required(VERSION 3.28)
# Copyright (c) 2024 Tomas Mark

# Library project name
project(EmojiTools)

# Set the source files
set(SOURCE_FILES
    EmojiTools.hpp
    EmojiTools.cpp
    EmojiWrapper.hpp
    EmojiWrapper.cpp
)

# Add the library as SHARED or STATIC 
add_library(EmojiTools SHARED STATIC ${SOURCE_FILES})

# Install the library
install(TARGETS EmojiTools DESTINATION ${THIS_INSTALL_LIB_DIR})

# Install the header files
install(FILES EmojiWrapper.hpp DESTINATION ${THIS_INSTALL_INCLUDE_DIR})
