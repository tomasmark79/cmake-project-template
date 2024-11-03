
## CMake C++ Project Template

Copyright (c) 2024 Tomas Mark

This template project was inspired by a vast number of projects encountered in the past. The goal is to keep it as simple as possible, using GTest.

## usage

```bash
git clone https://github.com/tomasmark79/cmake-project-template/tree/main
cd cmake-project-template
mkdir build
cd build
cmake ..
make install
```

## structure of project

App

```txt
./App:
App.cpp  App.hpp  CMakeLists.txt  FolderHelloWorld
```

Library

```txt
App/FolderHelloWorld/:
CMakeLists.txt  HelloWorld.cpp  HelloWorld.hpp
```

Created Binaries

```txt
./build:
```

TopMost CMake configuration

```txt
CMakeLists.txt
```

Future Documentation

```txt
./doc:
```

Folder for installation

```txt
./install: folder where you will find installed binaries
```

License and this file you are reading

```txt
LICENCE
README.md
```

Test App

```txt
./TestApp:
CMakeLists.txt  TestApp.cpp 

Implemented tests

./TestApp/Tests:
Tests.cpp
```

