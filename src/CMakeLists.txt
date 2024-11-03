cmake_minimum_required(VERSION 3.28)

# Set the project name
project(project C CXX)

# Add the library
add_subdirectory(FolderDivision)
add_subdirectory(FolderHelloWorld)

# Add the executable
set(SOURCE_FILES project.cpp)

# Add the executable
add_executable(project ${SOURCE_FILES})

# headers of modules
include_directories(${FOLDERDIVISION_HEADERS_DIR})
include_directories(${FOLDERHELLO_HEADERS_DIR})

# Link the library
target_link_libraries(project ModuleDivision)
target_link_libraries(project ModuleHelloWorld)

# Install the executable
install(TARGETS project DESTINATION ${THIS_INSTALL_BIN_DIR})
