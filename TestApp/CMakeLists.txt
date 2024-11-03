cmake_minimum_required(VERSION 3.28)
project(cmake-project-tests)

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

# add the source files
set(SOURCE_FILES TestApp.cpp Tests/Tests.cpp)

# add the executable
add_executable(cmake-project-tests ${SOURCE_FILES})

# google header
include_directories(${GTEST_INCLUDE_DIRS})

# libraries headers
include_directories(${FOLDERHELLO_HEADERS_DIR})

# link modules, ... and googletest
target_link_libraries(
    cmake-project-tests
    gtest
    HelloWorld
)

# Add the test
add_test(NAME cmake-project-tests COMMAND cmake-project-tests)

# Uncheck if you need to install the test
install(TARGETS cmake-project-tests DESTINATION ${THIS_INSTALL_BIN_DIR})