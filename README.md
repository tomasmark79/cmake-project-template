# Emoji Tools 😉🪄🎯

```cpp
#include "Emoji.hpp" // wrapper class for EmojiParser namespace
#include <iostream>
#include <vector>

int main()
{
    // HOW TO USE EmojiWrapper

    Emoji /*💋*/ emojiWrapper;

    // get emoji by codepoints

    // char32_t emojiCodePoint[1] = {0x1F600}; // 😀
    std::cout << "get 😀 = "
              << emojiWrapper.getEmojiStringCharByCodePoint((char32_t *)U"\U0001F600", 1)
              << std::endl;

    std::cout << "get 😶‍🌫️ = "
              << emojiWrapper.getEmojiStringCharByCodePoint((char32_t *)U"\U0001F636\U0000200D\U0001F32B\U0000FE0F", 4)
              << std::endl;

    // get all emojis from group or subgroup

    std::cout << "get all from Flags = "
              << emojiWrapper.getAllEmojiesFromGroup("Flags").substr(0, 32)
              << std::endl;

    std::cout << "get all from face-smiling = "
              << emojiWrapper.getAllEmojiesFromSubGroup("country-flag").substr(0, 32)
              << std::endl;

    // get random emoji from group or subgroup

    std::cout << emojiWrapper.getRandomEmojiFromGroup("Smileys & Emotion") << std::endl;
    std::cout << emojiWrapper.getRandomEmojiFromSubGroup("face-smiling") << std::endl;

    // get list of names of emoji groups and subgroups

    std::vector<std::string> emojiGroups = emojiWrapper.getEmojiGroups();
    std::cout << "Emoji groups: " << emojiGroups.size() << std::endl;
    std::vector<std::string> emojiSubGroups = emojiWrapper.getEmojiSubGroups();
    std::cout << "Emoji sub-groups: " << emojiSubGroups.size() << std::endl;

    // get number of items in a emoji group or subgroup

    std::cout << "Number of items in group Smileys & Emotion = "
              << emojiWrapper.getSizeOfGroupItems("Smileys & Emotion")
              << std::endl;

    std::cout << "Number of items in subgroup face-smiling = "
              << emojiWrapper.getSizeOfSubGroupItems("face-smiling")
              << std::endl;

    // get string emoji by index from group or subgroup

    std::cout << "get emoji by index 5 from group Smileys & Emotion = "
              << emojiWrapper.getEmojiStringByIndexFromGroup("Smileys & Emotion", 5)
              << std::endl;

    std::cout << "get emoji by index 5 from subgroup face-smiling = "
              << emojiWrapper.getEmojiStringByIndexFromSubGroup("face-smiling", 5)
              << std::endl;

    // get emoji group and subgroup description

    std::cout << "get group description Smileys & Emotion = "
              << std::endl
              << emojiWrapper.getEmojiGroupDescription("Smileys & Emotion")
              << std::endl;

    std::cout << "get subgroup description face-smiling = "
              << std::endl
              << emojiWrapper.getEmojiSubGroupDescription("face-smiling")
              << std::endl;

    return 0;
}

// MIT License
//
// Copyright (c) 2024 Tomas Mark
```

Project EmojiTools is configured by the CMake Project Template Below.

## CMake C++ Project Template

This project template was inspired by various projects encountered in the past. The goal is to keep it as simple as possible while using GTest for testing.

## Branches
- main - this cmake template
- blockchain - it is blockchain implementation with examples

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
