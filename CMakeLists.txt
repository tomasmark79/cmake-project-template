cmake_minimum_required(VERSION 3.28)
# Copyright (c) 2024 Tomas Mark

project(cmake-project-template)

# C++ Standard - setme
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -O3")

# install prefix - setme
set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR}/install)

# install subdirectories
set(THIS_INSTALL_INCLUDE_DIR ${CMAKE_INSTALL_PREFIX}/include)
set(THIS_INSTALL_BIN_DIR ${CMAKE_INSTALL_PREFIX}/bin)
set(THIS_INSTALL_LIB_DIR ${CMAKE_INSTALL_PREFIX}/lib)

# paths to the headers - addme
set(PROJECT_HEADERS_DIR ${PROJECT_SOURCE_DIR}/App)
set(FOLDERHELLO_HEADERS_DIR ${PROJECT_SOURCE_DIR}/App/FolderHelloWorld)
set(FOLDERBLOCKCHAIN_HEADERS_DIR ${PROJECT_SOURCE_DIR}/App/FolderBlockChain)
set(FOLDEREMOJITOOLS_HEADERS_DIR ${PROJECT_SOURCE_DIR}/App/FolderEmojiTools)
set(FOLDERCRCGEN_HEADERS_DIR ${PROJECT_SOURCE_DIR}/App/FolderCrcGen)

# include the headers - addme
include_directories(${THIS_INSTALL_INCLUDE_DIR})

# projects
add_subdirectory(App)
add_subdirectory(TestApp)


