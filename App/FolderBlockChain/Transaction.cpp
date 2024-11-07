#include "Transaction.hpp"
#include <openssl/sha.h>
#include <openssl/pem.h>
#include <openssl/err.h>
#include <iostream>
#include <iomanip> // for std::hex and std::setw

#define OPENSSL_NO_DEPRECATED

// Debugging function to print the hash
void debugPrintHash(unsigned char *hash, size_t length)
{
    for (size_t i = 0; i < length; i++)
    {
        std::cout << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(hash[i]);
    }
    std::cout << std::endl;
}

// Constructor to initialize a Transaction
Transaction::Transaction(std::string sender, std::string receiver, float amount, int nonce)
    : m_Sender(sender), m_Receiver(receiver), m_Amount(amount), m_Nonce(nonce) {}

// Method to sign a transaction
void Transaction::sign(RSA *privateKey)
{
    std::string dataToSign = m_Sender + m_Receiver + std::to_string(m_Amount) + std::to_string(m_Nonce);
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256(reinterpret_cast<const unsigned char *>(dataToSign.c_str()), dataToSign.size(), hash);

    unsigned char sign[RSA_size(privateKey)]; // Correct size for the signature

    unsigned int sLen;

    if (RSA_sign(NID_sha256, hash, SHA256_DIGEST_LENGTH, sign, &sLen, privateKey) != 1)
    {
        // Handle error.
        std::cout << "Signing failed.\n";
        return;
    }

    m_Signature.assign(reinterpret_cast<char *>(sign), sLen);
    m_SignatureLength = sLen; // Store the signature length

    std::cout << "Signed successfully. Signature Length: " << m_SignatureLength << "\n";
}

// Check overall validity of the transaction
bool Transaction::verify(RSA *publicKey) const
{

    // Clear OpenSSL error stack
    ERR_clear_error();

    std::string dataToVerify = m_Sender + m_Receiver + std::to_string(m_Amount) + std::to_string(m_Nonce);
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256(reinterpret_cast<const unsigned char *>(dataToVerify.c_str()), dataToVerify.size(), hash);

    int ret = RSA_verify(NID_sha256, hash, SHA256_DIGEST_LENGTH,
                         reinterpret_cast<const unsigned char *>(m_Signature.data()), m_SignatureLength, publicKey); // Use the stored length

    if (ret != 1)
    {
        unsigned long err = ERR_get_error();
        char *errStr = ERR_error_string(err, NULL);
        std::cout << "Error occurred during verification: " << errStr << std::endl;
        return false;
    }
    std::cout << "Verification successful.\n";
    return true;
}

bool Transaction::isValid(RSA *publicKey) const
{
    if (m_Nonce < 0 || !(m_Amount > 0))
    {
        return false;
    }

    return verify(publicKey);
}
