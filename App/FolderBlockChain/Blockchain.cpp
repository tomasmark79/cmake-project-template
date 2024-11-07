#include "Blockchain.hpp"
#include "Wallet.hpp"
#include <iostream>

// Constructor to initialize a Blockchain with the Genesis Block
Blockchain::Blockchain()
{
    std::vector<Transaction> emptyTransactions;      // Empty list for genesis block
    m_Chain.emplace_back(emptyTransactions, "0", 2); // Genesis Block
}

// Create a transaction and add it to the list of pending transactions
void Blockchain::createTransaction(Transaction transaction)
{
    m_PendingTransactions.push_back(transaction);
}

// Mine pending transactions into a new block and add it to the blockchain
void Blockchain::minePendingTransactions()
{
    Block newBlock(m_PendingTransactions, m_Chain.back().m_BlockHash, 2);
    m_Chain.push_back(newBlock);
    m_PendingTransactions.clear(); // Clear pending transactions
}

// Check if a block's hash is valid
bool Blockchain::isBlockHashValid(const Block &block)
{
    return block.m_BlockHash == block.generateHash();
}

// Check if a transaction is valid
bool Blockchain::isTransactionValid(const Transaction &tx)
{
    return tx.m_Amount > 0;
}

// Check the validity of the entire blockchain
bool Blockchain::isChainValid()
{
    for (int i = 1; i < static_cast<int>(m_Chain.size()); ++i)
    {
        Block currBlock = m_Chain[i];
        Block prevBlock = m_Chain[i - 1];

        if (!isBlockHashValid(currBlock))
        {
            return false;
        }

        if (currBlock.m_PrevHash != prevBlock.m_BlockHash)
        {
            return false;
        }

        for (const auto &tx : currBlock.m_Transactions)
        {
            RSA *publicKey = m_PublicKeyMap[tx.m_Sender]; // Retrieve publicKey based on tx.m_Sender
            if (!tx.isValid(publicKey))
            {
                return false;
            }
        }
    }
    return true;
}

std::string Blockchain::toHumanTime(std::time_t timestamp)
{
    char timeString[80];
    std::tm *now = std::localtime(&timestamp); // Převod na strukturu tm pro zpracování
    std::strftime(timeString, sizeof(timeString), "%Y/%m/%d %I:%S:%M %p", now);
    return timeString;
}
// Display the details of the entire blockchain
void Blockchain::printChain()
{
    for (const auto &block : m_Chain)
    {

        std::cout << ">" << std::endl;
        std::cout << "Block Timestamp: " << block.m_Timestamp << " | " << toHumanTime(block.m_Timestamp) << std::endl;
        std::cout << "Previous Hash: " << block.m_PrevHash << std::endl;
        std::cout << "Block Hash: " << block.m_BlockHash << std::endl;
        std::cout << "Transactions:" << std::endl;

        for (const auto &tx : block.m_Transactions)
        {
            std::cout << "  Sender: " << tx.m_Sender << " Receiver: " << tx.m_Receiver << " Amount: " << tx.m_Amount << std::endl;
        }

        std::cout << "Nonce: " << block.m_Nonce << std::endl; // Display the nonce
        std::cout << std::endl;
    }
}

// Notify wallets with updated transactions and balances
void Blockchain::notifyWallets(std::vector<Wallet *> &wallets)
{
    for (auto &wallet : wallets)
    {
        m_PublicKeyMap[wallet->m_Id] = wallet->m_PublicKey; // Store the public key in the map
        for (auto &block : m_Chain)
        {
            wallet->updateBalance(block.m_Transactions);
        }
    }
}
