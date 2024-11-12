#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>
#include <openssl/rsa.h>

class Transaction
{
public:
    std::string m_Sender;           // Sender's wallet ID
    std::string m_Receiver;         // Receiver's wallet ID
    float m_Amount;                 // Amount of money transferred
    std::string m_Signature;        // Digital signature for this transaction
    int m_Nonce;                    // Nonce for transaction, can be used for security or versioning
    unsigned int m_SignatureLength; // Length of the digital signature

    // Constructor to initialize the transaction
    Transaction(std::string sender, std::string receiver, float amount, int nonce);

    // Method to sign the transaction with the sender's private key
    void sign(RSA *privateKey);

    // Method to verify the transaction using the sender's public key
    bool verify(RSA *publicKey) const;

    // Method to check overall validity of the transaction
    bool isValid(RSA *publicKey) const;
};

#endif // TRANSACTION_H
