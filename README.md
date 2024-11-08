## CMake C++ Project Template

This project template was inspired by various projects encountered in the past. The goal is to keep it as simple as possible while using GTest for testing.

## Branches
- main - this cmake template
- blockchain - it is blockchain implementation with examples
- emojitools - utf8 emoji tools implementation

## Dependencies

- GTest is downloaded automatically via CMake's FetchContent.
- cmake
- git

## Platform Independence

Created and tested on Linux, but it may work in other environments.

## Usage

notice:
    If you want to use VSCode IDE and you already used commands bellow to configure and compile project, just remove build folder and reconfigure your project via CMake extension in VSCode.

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


https://github.com/user-attachments/assets/6a7eb9d0-1ff1-42e9-84ad-33b65b1ad55f



## Project Template Structure

**App**

```txt
./App:
App.cpp  App.hpp  CMakeLists.txt  FolderHelloWorld
```

**Library**

```txt
App/FolderHelloWorld/:
CMakeLists.txt  HelloWorld.cpp  HelloWorld.hpp
```

**Created Binaries**

```txt
./build:
```

**Top-Level CMake Configuration**

```txt
CMakeLists.txt
```

**Documentation**

```txt
./doc:
```

**Installation Directory**

```txt
./install: folder containing installed binaries
```

**License and README**

```txt
LICENCE
README.md
```

**Test Application**

```txt
./TestApp:
CMakeLists.txt  TestApp.cpp 
```

**Implemented Tests**

```txt
./TestApp/Tests:
Tests.cpp
```

---

© 2024 Tomas Mark
