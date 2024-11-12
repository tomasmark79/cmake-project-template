#ifndef __EMOJITOOLS_H__
#define __EMOJITOOLS_H__

#include <string>
#include <fstream>
#include <vector>
#include <map>
#include <assert.h>

#if __cplusplus < 202002L
using char8_t = char; // C++17 and older
#endif

#ifndef size_t
using size_t = decltype(sizeof(0));
#endif

class Utf8Parser
{
public:
    char8_t *encodeUtf8(char32_t emojiCodePoint, char8_t *buffer8);
    char8_t *encodeUtf8Sequence(const char32_t *emojiCodePoints, size_t length, char8_t *buffer8);
};

class EmojiBuilder
{
    struct EmojiPropertiesStructure
    {
        std::vector<char32_t> m_emojiCodePoints;
        std::string m_emojiGroup;
        std::string m_emojiSubGroup;
        std::string m_emojiUnicodeVersion;
        std::string m_emojiTextDescription;
    };

public:
    std::map<int, EmojiPropertiesStructure> m_emojiPropertiesMap;
    Utf8Parser utf8parser;

    EmojiBuilder();
    ~EmojiBuilder() {};

    // get emoji character by codepoint or codepoints
    std::string getEmojiStringCharByCodePoint(char32_t *emojiCodePoints, size_t length);
    char8_t getEmojiChar8_tCharByCodePoint(char32_t *emojiCodePoints, size_t length);

    bool m_isPopulated{false};

private:
    /// @brief Construct a new EmojiTools object
    /// @param epm std::map
    /// @param file std::ifstream
    void constructEmojiPropertiesMap(std::map<int, EmojiPropertiesStructure> &epm, std::istream &file);

    /// @brief load emoji asset file from hardcoded header file
    /// @return std::sstringstream if successful
    std::istringstream loadEmojiAssetsFromHardcodedHeader();

    /// @brief load emoji asset file from assets folder
    /// @return std::ifstream if successful else library exits
    std::ifstream loadEmojiAssetsFromFile();
};

class EmojiTransmitter
{
public:
    EmojiTransmitter() = default;

    EmojiBuilder emojiBuilder;

public:
    // get emoji character by codepoint or codepoints
    std::string getEmojiStringCharByCodePoint(char32_t *emojiCodePoints, size_t length);
    // get emoji char8_t character by codepoint or codepoints
    char8_t getEmojiChar8_tCharByCodePoint(char32_t *emojiCodePoints, size_t length);
    // get random emoji contained in a group
    std::string getRandomEmojiFromGroup(std::string emojiGroup);
    // get random emoji contained in a subgroup
    std::string getRandomEmojiFromSubGroup(std::string emojiSubGroup);
    // get all emoji chars contained in a group
    std::string getEmojiesFromGroup(std::string emojiGroup);
    // get all emoji chars contained in a subgroup
    std::string getEmojiesFromSubGroup(std::string emojiSubGroup);
    // get the vector containing names of emoji groups
    std::vector<std::string> getEmojiGroupsNames();
    // get the vector containing names of emoji subgroups
    std::vector<std::string> getEmojiSubGroupsNames();
    // get number of items in a group
    int getSizeOfGroupItems(std::string emojiGroup);
    // get number of items in a subgroup
    int getSizeOfSubGroupItems(std::string emojiSubGroup);
    // get emoji std::string character by index from group
    std::string getEmojiStringByIndexFromGroup(std::string emojiGroup, int index);
    // get emoji std::string character by index from subgroup
    std::string getEmojiStringByIndexFromSubGroup(std::string emojiSubGroup, int index);
    // get emoji group description
    std::string getEmojiGroupDescription(std::string emojiGroup);
    // get emoji subgroup description
    std::string getEmojiSubGroupDescription(std::string emojiSubGroup);

    // TODO

    // Get emoji by name
    // Get emoji by description
    // Get emoji by unicode version

    void printEmojiGroup(std::string emojiGroup);
    void printEmojiSubGroupWDescription(std::string emojiSubGroup);
    void printEmojiSubGroup(std::string emojiSubGroup);

    void printGroupsText();
    void printSubGroupsText();
    void printEmojiDescription(std::string emojiDescription);
};

// MIT License
//
// Copyright (c) 2024 Tomas Mark

#endif // __EMOJITOOLS_H__