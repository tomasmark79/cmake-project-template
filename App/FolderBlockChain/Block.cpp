#include "Block.hpp"
#include <sstream>
#include <iomanip>
#include <openssl/sha.h>

// Constructor to initialize a Block with given transactions, previous hash, and difficulty level.
Block::Block(std::vector<Transaction> transactions, std::string prevHash, int difficulty)
{
    m_Transactions = transactions;
    m_PrevHash = prevHash;
    m_Timestamp = std::time(nullptr); 
    m_Difficulty = difficulty;
    m_Nonce = 0;
    m_BlockHash = mineBlock(); // Compute the block's hash
}

// Mining function to find a valid hash for the block based on the given difficulty
std::string Block::mineBlock()
{
    std::string target(m_Difficulty, '0');
    while (m_BlockHash.substr(0, m_Difficulty) != target)
    {
        m_Nonce++;
        m_BlockHash = generateHash();
    }
    return m_BlockHash;
}

// Generate the hash of the block
std::string Block::generateHash() const
{
    std::stringstream ss;
    ss << std::put_time(std::gmtime(&m_Timestamp), "%Y-%m-%dT%H:%M:%S"); // Add timestamp to the hash
    for (const auto &tx : m_Transactions)
    {
        ss << tx.m_Sender << tx.m_Receiver << tx.m_Amount;
    }
    ss << m_PrevHash << m_Nonce;
    return sha256(ss.str());
}

// Compute SHA-256 hash for a given string
std::string Block::sha256(const std::string str) const
{
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, str.c_str(), str.size());
    SHA256_Final(hash, &sha256);

    std::stringstream ss;
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++)
    {
        ss << std::hex << std::setw(2) << std::setfill('0') << (int)hash[i];
    }
    return ss.str();
}
