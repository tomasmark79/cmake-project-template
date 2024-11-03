cmake_minimum_required(VERSION 3.28)
# on root CMakeLists.txt

project(cmake-project-template)

# set the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -O3")

# install prefix
set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR}/install)

# install directories
set(THIS_INSTALL_INCLUDE_DIR ${CMAKE_INSTALL_PREFIX}/include)
set(THIS_INSTALL_BIN_DIR ${CMAKE_INSTALL_PREFIX}/bin)
set(THIS_INSTALL_LIB_DIR ${CMAKE_INSTALL_PREFIX}/lib)

# headers
set(PROJECT_HEADERS_DIR ${PROJECT_SOURCE_DIR}/src)
set(FOLDERDIVISION_HEADERS_DIR ${PROJECT_SOURCE_DIR}/src/FolderDivision)
set(FOLDERHELLO_HEADERS_DIR ${PROJECT_SOURCE_DIR}/src/FolderHelloWorld)

# add the include directories
include_directories(${THIS_INSTALL_INCLUDE_DIR})

# add the src and test directories 
add_subdirectory(src)
add_subdirectory(test)


