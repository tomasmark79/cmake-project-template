#ifndef __BLOCKCHAIN_H__
#define __BLOCKCHAIN_H__

#include <vector>
#include <unordered_map>
#include "Block.hpp"
#include "Transaction.hpp"
#include "Wallet.hpp"

class Blockchain
{

public:
    // Constructor to initialize blockchain with genesis block
    Blockchain();

    // Method to add a new transaction to pendingTransactions
    void createTransaction(Transaction transaction);

    // Method to mine pending transactions and add a new block to the blockchain
    void minePendingTransactions();

    // Method to validate if a block's hash is correct
    bool isBlockHashValid(const Block &block);

    // Method to validate if a transaction is valid
    bool isTransactionValid(const Transaction &tx);

    // Method to validate the integrity of the entire blockchain
    bool isChainValid();

    std::string toHumanTime(std::time_t timestamp);

    // Method to print the details of all blocks in the blockchain
    void printChain();

    // Method to notify all wallets about the state of the blockchain
    void notifyWallets(std::vector<Wallet *> &wallets);

private:
    std::vector<Block> m_Chain;                            // Blockchain consisting of blocks
    std::vector<Transaction> m_PendingTransactions;        // Transactions waiting to be added to a block
    std::unordered_map<std::string, RSA *> m_PublicKeyMap; // Map of wallet IDs to their public keys
};

#endif // __BLOCKCHAIN_H__