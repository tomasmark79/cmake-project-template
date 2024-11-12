#include <stdio.h>
#include <iostream>
#include <filesystem>
#include <sstream>
#include <algorithm>
#include <regex>
#include <random>

#include "emoji-test.hpp" // Unicode defition of emojis converted to source code
#include "EmojiTools.hpp"

char8_t *Utf8Parser::encodeUtf8(char32_t emojiCodePoint, char8_t *buffer8)
{
    constexpr auto byte = [](char32_t x)
    {
        assert(x <= 0x100); // 256
        return static_cast<char8_t>(x);
    };

    char32_t continuation = 0b1000'0000; // 128
    if (emojiCodePoint >= 65536)
    {
        *buffer8++ = byte(0b1111'0000 | (emojiCodePoint >> 18));
        *buffer8++ = byte(continuation | ((emojiCodePoint >> 12) & 0b0011'1111));
        *buffer8++ = byte(continuation | ((emojiCodePoint >> 6) & 0b0011'1111));
        *buffer8++ = byte(continuation | (emojiCodePoint & 0b0011'1111));
    }
    else if (emojiCodePoint >= 2048)
    {
        *buffer8++ = byte(0b1110'0000 | (emojiCodePoint >> 12));
        *buffer8++ = byte(continuation | ((emojiCodePoint >> 6) & 0b0011'1111));
        *buffer8++ = byte(continuation | (emojiCodePoint & 0b0011'1111));
    }
    else if (emojiCodePoint >= 128)
    {
        *buffer8++ = byte(0b1100'0000 | (emojiCodePoint >> 6));
        *buffer8++ = byte(continuation | (emojiCodePoint & 0b0011'1111));
    }
    else
    {
        *buffer8++ = byte(emojiCodePoint);
    }

    return buffer8;
}
char8_t *Utf8Parser::encodeUtf8Sequence(const char32_t *emojiCodePoints, size_t length, char8_t *buffer8)
{
    for (size_t i = 0; i < length; ++i)
    {
        buffer8 = encodeUtf8(emojiCodePoints[i], buffer8);
    }
    return buffer8;
}

EmojiBuilder::EmojiBuilder()
{
    std::ifstream is = loadEmojiAssetsFromFile();
    if (is)
    {
        constructEmojiPropertiesMap(m_emojiPropertiesMap, is);
    }
    else
    {
        std::istringstream ss = loadEmojiAssetsFromHardcodedHeader();
        constructEmojiPropertiesMap(m_emojiPropertiesMap, static_cast<std::istream &>(ss));
    }
}
void EmojiBuilder::constructEmojiPropertiesMap(std::map<int, EmojiPropertiesStructure> &epm, std::istream &file)
{
    int mapKey = 0;
    std::vector<char32_t> emojiCodePoints;
    std::string emojiGroup;
    std::string emojiSubGroup;
    std::string emojiUnicodeVersion;
    std::string emojiTailDescription;
    std::string emojiTextDescription;
    std::string line;
    std::string token;

    // TODO Robust error handling (artefacted file, etc.)
    while (std::getline(file, line))
    {
        if (line.empty())
        {
            continue;
        }
        else if (line[0] == '#' && (line.find("# subgroup:") == std::string::npos) && (line.find("# group:") == std::string::npos))
        {
            continue;
        }
        else if (line.find("# subgroup:") != std::string::npos)
        {

            emojiSubGroup = line.substr(12);
            // pr("\tSubgroup: ");pr(emojiSubGroup); br();
            continue;
        }
        else if (line.find("# group:") != std::string::npos)
        {
            emojiGroup = line.substr(9);
            // pr("Group: "); pr(emojiGroup); br();
            continue;
        }
        else if (
            (line[0] != '#') &&
            (line.find("#") != std::string::npos) &&
            (line.find("# subgroup:") == std::string::npos) &&
            (line.find("# group:") == std::string::npos))
        {

            std::string unicodeString = line.substr(0, line.find(";"));
            // pr("\t\t"); pr(unicodeString);

            std::istringstream iss(unicodeString);
            emojiCodePoints.clear();
            while (iss >> token)
            {
                token.erase(std::remove_if(token.begin(), token.end(), [](char c)
                                           { return !std::isxdigit(c); }),
                            token.end());

                uint32_t value;
                std::stringstream ss;
                ss << std::hex << token;
                ss >> value;
                emojiCodePoints.push_back(static_cast<char32_t>(value));
            }

            emojiTailDescription = line.substr(line.find("#") + 1);
            // pr("\t"); pr(emojiTailDescription); br();

            // regular expression for extract unicode version
            std::regex unicodeRegex(R"((E\d+\.\d+))");
            std::smatch unicodeMatch;
            if (std::regex_search(emojiTailDescription, unicodeMatch, unicodeRegex))
            {
                emojiUnicodeVersion = unicodeMatch[0];
                // pr("\t");pr("Unicode v.: "); pr(unicodeMatch[0]);
            }

            // extract emoji text description
            std::string::size_type unicodeVersionPos = emojiTailDescription.find(unicodeMatch[0]);
            if (unicodeVersionPos != std::string::npos)
            {
                emojiTextDescription = emojiTailDescription.substr(unicodeVersionPos + unicodeMatch[0].length() + 1, emojiTailDescription.size());
                // pr("\t");pr("Desc.: ");pr(emojiTextDescription);
            }

            // combine emoji character from code points
            char8_t buffer[32];
            // Utf8Tools::Utf8Parser utf8tools;
            char8_t *end = utf8parser.encodeUtf8Sequence(emojiCodePoints.data(), emojiCodePoints.size(), buffer);
            *end = '\0'; // Null-terminating the string
            // pr("\t"); pr("Emoji: "); pr(reinterpret_cast<char *>(buffer)); br();
        }

        // create copy of structure
        EmojiPropertiesStructure eps;
        eps.m_emojiCodePoints = emojiCodePoints;
        eps.m_emojiGroup = emojiGroup;
        eps.m_emojiSubGroup = emojiSubGroup;
        eps.m_emojiUnicodeVersion = emojiUnicodeVersion;
        eps.m_emojiTextDescription = emojiTextDescription;

        // insert eps to epm
        epm.insert(std::pair<int, EmojiPropertiesStructure>(mapKey++, eps));

        // ***
        this->m_isPopulated = true;
    }
}
std::istringstream EmojiBuilder::loadEmojiAssetsFromHardcodedHeader()
{
    std::istringstream ss(emojiTestFileContent);
    if (ss.str().empty())
    {

        exit(1);
    }
    return ss;
}
std::ifstream EmojiBuilder::loadEmojiAssetsFromFile()
{
    // std::string assetFilePath = std::filesystem::current_path().string() + "/assets/emoji-test.txt";
    std::string assetFilePath = "/home/tomas/dev/cpp/modules/EmojiTools/assets/emoji-test.txt-";
    std::ifstream is(assetFilePath);
    if (!is)
        std::cerr << "Emoji asset test file not found. Loading hardcoded definition." << std::endl;
    return is;
}
std::string EmojiBuilder::getEmojiStringCharByCodePoint(char32_t *emojiCodePoints, size_t length)
{
    if (m_isPopulated)
    {
        char8_t buffer[32];
        char8_t *end = utf8parser.encodeUtf8Sequence(emojiCodePoints, length, buffer);
        *end = '\0'; // Null-terminating the string
        return std::string(reinterpret_cast<char *>(buffer));
    }
    else
        return "";
}
char8_t EmojiBuilder::getEmojiChar8_tCharByCodePoint(char32_t *emojiCodePoints, size_t length)
{
    char8_t buffer[32];
    char8_t *end = utf8parser.encodeUtf8Sequence(emojiCodePoints, length, buffer);
    *end = '\0'; // Null-terminating the string
    // std::cout << reinterpret_cast<char *>(buffer);
    // TODO
    return *buffer;
}

std::string EmojiTransmitter::getEmojiStringCharByCodePoint(char32_t *emojiCodePoints, size_t length)
{
    return emojiBuilder.getEmojiStringCharByCodePoint(emojiCodePoints, length);
}
char8_t EmojiTransmitter::getEmojiChar8_tCharByCodePoint(char32_t *emojiCodePoints, size_t length)
{
    return emojiBuilder.getEmojiChar8_tCharByCodePoint(emojiCodePoints, length);
}
std::string EmojiTransmitter::getRandomEmojiFromGroup(std::string emojiGroup)
{
    if (emojiBuilder.m_isPopulated)
    {
        int count = 0;
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(1, getSizeOfGroupItems(emojiGroup) - 1);
        int randomIndex = dis(gen);

        for (auto &epm : emojiBuilder.m_emojiPropertiesMap)
        {
            if (epm.second.m_emojiGroup == emojiGroup)
            {
                if (count == randomIndex)
                {
                    return emojiBuilder.getEmojiStringCharByCodePoint(epm.second.m_emojiCodePoints.data(), epm.second.m_emojiCodePoints.size());
                }
                count++;
            }
        }
    }
    return "";
}
std::string EmojiTransmitter::getRandomEmojiFromSubGroup(std::string emojiSubGroup)
{
    if (emojiBuilder.m_isPopulated)
    {
        int count = 0;
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(1, getSizeOfSubGroupItems(emojiSubGroup) - 1);
        int randomIndex = dis(gen);

        for (auto &epm : emojiBuilder.m_emojiPropertiesMap)
        {
            if (epm.second.m_emojiSubGroup == emojiSubGroup)
            {
                if (count == randomIndex)
                {
                    return emojiBuilder.getEmojiStringCharByCodePoint(epm.second.m_emojiCodePoints.data(), epm.second.m_emojiCodePoints.size());
                }
                count++;
            }
        }
    }
    return "";
}
std::string EmojiTransmitter::getEmojiesFromGroup(std::string emojiGroup)
{
    if (emojiBuilder.m_isPopulated)
    {
        std::string emojis = "";
        for (auto &epm : emojiBuilder.m_emojiPropertiesMap)
        {
            if (epm.second.m_emojiGroup == emojiGroup)
            {
                emojis += emojiBuilder.getEmojiStringCharByCodePoint(epm.second.m_emojiCodePoints.data(), epm.second.m_emojiCodePoints.size());
            }
        }
        return emojis;
    }
    return "";
}
std::string EmojiTransmitter::getEmojiesFromSubGroup(std::string emojiSubGroup)
{
    if (emojiBuilder.m_isPopulated)
    {
        std::string emojis = "";
        for (auto &epm : emojiBuilder.m_emojiPropertiesMap)
        {
            if (epm.second.m_emojiSubGroup == emojiSubGroup)
            {
                emojis += emojiBuilder.getEmojiStringCharByCodePoint(epm.second.m_emojiCodePoints.data(), epm.second.m_emojiCodePoints.size());
            }
        }
        return emojis;
    }
    return "";
}
std::vector<std::string> EmojiTransmitter::getEmojiGroupsNames()
{
    if (emojiBuilder.m_isPopulated)
    {
        std::vector<std::string> vecGroups;

        for (auto &epm : emojiBuilder.m_emojiPropertiesMap)
        {
            if (std::find(vecGroups.begin(), vecGroups.end(), epm.second.m_emojiGroup) == vecGroups.end())
            {
                vecGroups.push_back(epm.second.m_emojiGroup); // Groups map source
            }
        }
        return vecGroups;
    }
    return {};
}
std::vector<std::string> EmojiTransmitter::getEmojiSubGroupsNames()
{
    if (emojiBuilder.m_isPopulated)
    {
        std::vector<std::string> vecSubGroups;

        for (auto &epm : emojiBuilder.m_emojiPropertiesMap)
        {
            if (std::find(vecSubGroups.begin(), vecSubGroups.end(), epm.second.m_emojiSubGroup) == vecSubGroups.end())
            {
                vecSubGroups.push_back(epm.second.m_emojiSubGroup); // SubGroups map source
            }
        }
        return vecSubGroups;
    }
    return {};
}
int EmojiTransmitter::getSizeOfGroupItems(std::string emojiGroup)
{
    if (emojiBuilder.m_isPopulated)
    {
        int count = 0;
        for (auto &epm : emojiBuilder.m_emojiPropertiesMap)
        {
            if (epm.second.m_emojiGroup == emojiGroup)
            {
                count++;
            }
        }
        return count;
    }
    return 0;
}
int EmojiTransmitter::getSizeOfSubGroupItems(std::string emojiSubGroup)
{
    if (emojiBuilder.m_isPopulated)
    {
        int count = 0;
        for (auto &epm : emojiBuilder.m_emojiPropertiesMap)
        {
            if (epm.second.m_emojiSubGroup == emojiSubGroup)
            {
                count++;
            }
        }
        return count;
    }
    return 0;
}
std::string EmojiTransmitter::getEmojiStringByIndexFromGroup(std::string emojiGroup, int index)
{
    if (emojiBuilder.m_isPopulated)
    {
        int count = 0;
        for (auto &epm : emojiBuilder.m_emojiPropertiesMap)
        {
            if (epm.second.m_emojiGroup == emojiGroup)
            {
                if (count == index)
                {
                    return emojiBuilder.getEmojiStringCharByCodePoint(epm.second.m_emojiCodePoints.data(), epm.second.m_emojiCodePoints.size());
                }
                count++;
            }
        }
    }
    return "";
}
std::string EmojiTransmitter::getEmojiStringByIndexFromSubGroup(std::string emojiSubGroup, int index)
{
    if (emojiBuilder.m_isPopulated)
    {
        int count = 0;
        for (auto &epm : emojiBuilder.m_emojiPropertiesMap)
        {
            if (epm.second.m_emojiSubGroup == emojiSubGroup)
            {
                if (count == index)
                {
                    return emojiBuilder.getEmojiStringCharByCodePoint(epm.second.m_emojiCodePoints.data(), epm.second.m_emojiCodePoints.size());
                }
                count++;
            }
        }
    }
    return "";
}
std::string EmojiTransmitter::getEmojiGroupDescription(std::string emojiGroup)
{
    std::stringstream ss;

    if (emojiBuilder.m_isPopulated)
    {
        for (auto &epm : emojiBuilder.m_emojiPropertiesMap)
        {
            if (epm.second.m_emojiGroup == emojiGroup)
            {
                ss << "Emoji: "
                << getEmojiStringCharByCodePoint(epm.second.m_emojiCodePoints.data(), epm.second.m_emojiCodePoints.size())
                << "\t Group: "
                << epm.second.m_emojiGroup
                << " | Subgroup: "
                << epm.second.m_emojiSubGroup
                << " | Description: "
                << epm.second.m_emojiTextDescription
                << " | Unicode version: "
                << epm.second.m_emojiUnicodeVersion << std::endl;
            }
        }
    }
    return ss.str();
}
std::string EmojiTransmitter::getEmojiSubGroupDescription(std::string emojiSubGroup)
{
    std::stringstream ss;

    if (emojiBuilder.m_isPopulated)
    {
        for (auto &epm : emojiBuilder.m_emojiPropertiesMap)
        {
            if (epm.second.m_emojiSubGroup == emojiSubGroup)
            {
                ss << "Emoji: "
                << getEmojiStringCharByCodePoint(epm.second.m_emojiCodePoints.data(), epm.second.m_emojiCodePoints.size())
                << "\t Group: "
                << epm.second.m_emojiGroup
                << " | Subgroup: "
                << epm.second.m_emojiSubGroup
                << " | Description: "
                << epm.second.m_emojiTextDescription
                << " | Unicode version: "
                << epm.second.m_emojiUnicodeVersion << std::endl;
            }
        }
    }
    return ss.str();
}



void EmojiTransmitter::printEmojiGroup(std::string emojiGroup)
{
    if (emojiBuilder.m_isPopulated)
    {
        for (auto &epm : emojiBuilder.m_emojiPropertiesMap)
        {
            if (epm.second.m_emojiGroup == emojiGroup)
            {
                getEmojiChar8_tCharByCodePoint(epm.second.m_emojiCodePoints.data(), epm.second.m_emojiCodePoints.size());
            }
        }
    }
}

void EmojiTransmitter::printEmojiSubGroup(std::string emojiSubGroup)
{
    if (emojiBuilder.m_isPopulated)
    {
        for (auto &epm : emojiBuilder.m_emojiPropertiesMap)
        {
            if (epm.second.m_emojiSubGroup == emojiSubGroup)
            {
                getEmojiChar8_tCharByCodePoint(epm.second.m_emojiCodePoints.data(), epm.second.m_emojiCodePoints.size());
            }
        }
    }
}
void EmojiTransmitter::printGroupsText()
{
    if (emojiBuilder.m_isPopulated)
    {
        std::vector<std::string> groups;
        for (auto &epm : emojiBuilder.m_emojiPropertiesMap)
        {
            if (std::find(groups.begin(), groups.end(), epm.second.m_emojiGroup) == groups.end())
            {
                groups.push_back(epm.second.m_emojiGroup);
            }
        }

        for (auto &group : groups)
        {
            std::cout << "Group: ";
            std::cout << group << std::endl;
        }
    }
}
void EmojiTransmitter::printSubGroupsText()
{
    if (emojiBuilder.m_isPopulated)
    {
        std::vector<std::string> subgroups;
        for (auto &epm : emojiBuilder.m_emojiPropertiesMap)
        {
            if (std::find(subgroups.begin(), subgroups.end(), epm.second.m_emojiSubGroup) == subgroups.end())
            {
                subgroups.push_back(epm.second.m_emojiSubGroup);
            }
        }

        for (auto &subgroup : subgroups)
        {
            std::cout << "Subgroup: ";
            std::cout << subgroup << std::endl;
        }
    }
}