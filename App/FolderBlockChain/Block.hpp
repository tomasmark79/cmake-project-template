#ifndef __BLOCK_H__
#define __BLOCK_H__

#include <string>
#include <vector>
#include <ctime>
#include "Transaction.hpp"

class Block
{
public:
    std::string m_PrevHash;                  // Hash of the previous block
    std::string m_BlockHash;                 // Hash of the current block
    std::vector<Transaction> m_Transactions; // List of transactions in this block
    std::time_t m_Timestamp;                 // Timestamp for when this block was created
    int m_Nonce;                             // Nonce used for mining
    int m_Difficulty;                        // The difficulty level for mining this block

    // Constructor to initialize a block with transactions, previous hash, and difficulty
    Block(std::vector<Transaction> transactions, std::string prevHash, int difficulty);

    // Method to mine the block by finding a nonce that satisfies the difficulty
    std::string mineBlock();

    // Method to generate the hash of the block's contents
    std::string generateHash() const;

    // Utility method to perform SHA-256 hashing
    std::string sha256(const std::string str) const;
};

#endif // __BLOCK_H__