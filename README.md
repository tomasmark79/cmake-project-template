
## CMake C++ Project Template

This template project was inspired by a vast number of projects encountered in the past. The goal is to keep it as simple as possible, using GTest.

## dependencies

```
GTest is downloaded automaticaly via CMake FetchContent
```

```
cmake
```

```
git
```

## platform independent

Created and tested on Linux, but may to work on any environment.

## usage

```bash
git clone https://github.com/tomasmark79/cmake-project-template.git
cd cmake-project-template
mkdir build
cd build
cmake ..
make install
cd ../install/
ls -la
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
```

Implemented Tests

```txt
./TestApp/Tests:
Tests.cpp
```

---

Copyright (c) 2024 Tomas Mark