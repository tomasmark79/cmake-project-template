cmake_minimum_required(VERSION 3.28)
# Copyright (c) 2024 Tomas Mark

# Library project name
project(BlockChain)

# Set the source files
set(SOURCE_FILES
    Block.cpp
    Blockchain.cpp
    Transaction.cpp
    Wallet.cpp
)

# Add the library as SHARED or STATIC 
add_library(BlockChain SHARED STATIC ${SOURCE_FILES})

# Install the library
install(TARGETS BlockChain DESTINATION ${THIS_INSTALL_LIB_DIR})

# Link the library with OpenSSL
find_package(OpenSSL REQUIRED)
target_link_libraries(BlockChain PRIVATE OpenSSL::SSL OpenSSL::Crypto)

# Install the header files
install(FILES Blockchain.hpp DESTINATION ${THIS_INSTALL_INCLUDE_DIR})
install(FILES Wallet.hpp DESTINATION ${THIS_INSTALL_INCLUDE_DIR})
