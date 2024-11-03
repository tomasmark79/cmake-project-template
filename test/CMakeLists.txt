cmake_minimum_required(VERSION 3.5)

project(project_tests)

# Set policy CMP0135 to NEW
if(POLICY CMP0135)
    cmake_policy(SET CMP0135 NEW)
endif()

find_package(GTest QUIET)
# If GTest is not found, fetch it from the internet
if(NOT GTest_FOUND)
    include(FetchContent)
    FetchContent_Declare(
      googletest
      URL https://github.com/google/googletest/releases/download/v1.15.2/googletest-1.15.2.tar.gz
      DOWNLOAD_EXTRACT_TIMESTAMP true
    )
    FetchContent_MakeAvailable(googletest)
    
endif()

#add_subdirectory(lib/googletest)

# add the source files
set(SOURCE_FILES test.cpp src/project_tests.cpp)

# add the executable
add_executable(project_tests ${SOURCE_FILES})

# google header
include_directories(${GTEST_INCLUDE_DIRS})

# module headers
include_directories(${FOLDERDIVISION_HEADERS_DIR})
include_directories(${FOLDERHELLO_HEADERS_DIR})

# link modules, ... and googletest
target_link_libraries(
    project_tests
    gtest
    ModuleDivision
    ModuleHelloWorld
)

# Add the test
add_test(NAME project_tests COMMAND project_tests)

# install the executable
install(TARGETS project_tests DESTINATION ${THIS_INSTALL_BIN_DIR})