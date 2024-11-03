cmake_minimum_required(VERSION 3.28)

# set the Application name
project(cmake-project-application)

# add libraries
add_subdirectory(FolderHelloWorld)

# add the executable
set(SOURCE_FILES App.cpp)

# add the executable
add_executable(cmake-project-application ${SOURCE_FILES})

# headers of libraries
include_directories(${FOLDERHELLO_HEADERS_DIR})

# link libraries
target_link_libraries(cmake-project-application ModuleHelloWorld)

# install the executable
install(TARGETS cmake-project-application DESTINATION ${THIS_INSTALL_BIN_DIR})
