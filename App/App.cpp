#include "App.hpp"

#include "Blockchain.hpp"
#include "HelloWorld.hpp"
#include "Wallet.hpp"

#include "EmojiWrapper.hpp"

#include "CrcGen.hpp"

#include <iostream>

int main(int argc, char *argv[], char *env[])
{
    std::cout << HEADER;
    
    HelloWorld hw;
    hw.sayHello();

    // BlockChain library
    Blockchain myBlockchain;
    std::vector<Wallet *> wallets;

    Wallet tomas("Tomas");
    Wallet lucia("Lucia");
    Wallet radek("Radek");
    Wallet venca("Venca");

    tomas.m_Balance = 100;
    lucia.m_Balance = 100;
    radek.m_Balance = 100;
    venca.m_Balance = 100;

    wallets.push_back(&tomas);
    wallets.push_back(&lucia);
    wallets.push_back(&radek);
    wallets.push_back(&venca);

    for (int i = 0; i < 10; i++)
    {
        Transaction tx1 = tomas.sendFunds(lucia, 10);
        myBlockchain.createTransaction(tx1);

        Transaction tx2 = lucia.sendFunds(radek, 10);
        myBlockchain.createTransaction(tx2);

        Transaction tx3 = radek.sendFunds(venca, 10);
        myBlockchain.createTransaction(tx3);

        Transaction tx4 = venca.sendFunds(tomas, 10);
        myBlockchain.createTransaction(tx4);

        myBlockchain.minePendingTransactions();
    }

    myBlockchain.notifyWallets(wallets);

    if (myBlockchain.isChainValid())
    {
        std::cout << "Blockchain is valid.\n";
    }
    else
    {
        std::cout << "Blockchain is not valid!\n";
    }

    myBlockchain.printChain();

    for (const auto &wallet : wallets)
    {
        // wallet->printWalletData();
        std::cout << "Wallet " << wallet->m_Id << " has balance: " << wallet->m_Balance << std::endl;
    }


    // Emoji wrapper
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
