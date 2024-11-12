#pragma once
#include "EmojiTools.hpp"

// MUST STAY STABLE for others
//  _    _______  ___  ____________ ___________
// | |  | | ___ \/ _ \ | ___ \ ___ \  ___| ___ \
// | |  | | |_/ / /_\ \| |_/ / |_/ / |__ | |_/ /
// | |/\| |    /|  _  ||  __/|  __/|  __||    /
// \  /\  / |\ \| | | || |   | |   | |___| |\ \ 
//  \/  \/\_| \_\_| |_/\_|   \_|   \____/\_| \_|
//
class Emoji
{
private:
    EmojiTransmitter et;

public:
    Emoji() = default;
    ~Emoji() = default;

    // get emoji std::string character by codepoint or codepoints
    std::string getEmojiStringCharByCodePoint(char32_t *emojiCodePoints, size_t length)
    {
        return et.getEmojiStringCharByCodePoint(emojiCodePoints, length);
    }

    // get emoji char8_t character by codepoint or codepoints
    char8_t getEmojiChar8_tCharByCodePoint(char32_t *emojiCodePoints, size_t length)
    {
        return et.getEmojiChar8_tCharByCodePoint(emojiCodePoints, length);
    }

    // get random emoji contained in a group
    std::string getRandomEmojiFromGroup(const std::string emojiGroup)
    {
        return et.getRandomEmojiFromGroup(emojiGroup);
    }

    // get random emoji contained in a subgroup
    std::string getRandomEmojiFromSubGroup(const std::string emojiSubGroup)
    {
        return et.getRandomEmojiFromSubGroup(emojiSubGroup);
    }

    // get all emoji chars contained in a group
    std::string getAllEmojiesFromGroup(const std::string emojiGroup)
    {
        return et.getEmojiesFromGroup(emojiGroup);
    }

    // get all emoji chars contained in a subgroup
    std::string getAllEmojiesFromSubGroup(const std::string emojiSubGroup)
    {
        return et.getEmojiesFromSubGroup(emojiSubGroup);
    }

    // get the vector containing names of emoji groups
    // vector.size() to retrieve the number of groups
    std::vector<std::string> getEmojiGroups()
    {
        return et.getEmojiGroupsNames();
    }

    // get the vector containing names of emoji subgroups
    // vector.size() to retrieve the number of subgroups
    std::vector<std::string> getEmojiSubGroups()
    {
        return et.getEmojiSubGroupsNames();
    }

    // get number of items in a group
    int getSizeOfGroupItems(const std::string emojiGroup)
    {
        return et.getSizeOfGroupItems(emojiGroup);
    }

    // get number of items in a subgroup
    int getSizeOfSubGroupItems(const std::string emojiSubGroup)
    {
        return et.getSizeOfSubGroupItems(emojiSubGroup);
    }

    // get emoji std::string character by index from group
    std::string getEmojiStringByIndexFromGroup(const std::string emojiGroup, const int index)
    {
        return et.getEmojiStringByIndexFromGroup(emojiGroup, index);
    }

    // get emoji std::string character by index from subgroup
    std::string getEmojiStringByIndexFromSubGroup(const std::string emojiSubGroup, const int index)
    {
        return et.getEmojiStringByIndexFromSubGroup(emojiSubGroup, index);
    }

    // get emoji group description
    std::string getEmojiGroupDescription(const std::string emojiGroup)
    {
        return et.getEmojiGroupDescription(emojiGroup);
    }

    // get emoji subgroup description
    std::string getEmojiSubGroupDescription(const std::string emojiSubGroup)
    {
        return et.getEmojiSubGroupDescription(emojiSubGroup);
    }
};
