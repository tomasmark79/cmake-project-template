#include "Wallet.hpp"
#include <iostream> // Include iostream for std::cerr
#include <openssl/rand.h>
#include <openssl/pem.h>

// Constructor to initialize a Wallet with given ID
Wallet::Wallet(std::string id) : m_Id(id), m_Balance(0.0f), m_PublicKey(nullptr), m_PrivateKey(nullptr)
{
    generateKeys();
}

// Destructor to free RSA key pairs
Wallet::~Wallet()
{
    if (m_PrivateKey)
    {
        RSA_free(m_PrivateKey);
        m_PrivateKey = nullptr;
    }
    if (m_PublicKey)
    {
        RSA_free(m_PublicKey);
        m_PublicKey = nullptr;
    }
}

// Method to generate RSA key pairs
void Wallet::generateKeys()
{
    m_PrivateKey = RSA_new();
    BIGNUM *exponent = BN_new();
    BN_set_word(exponent, RSA_F4); // Public exponent
    RSA_generate_key_ex(m_PrivateKey, 2048, exponent, nullptr);

    // Create a new RSA object for the public key and set its fields
    m_PublicKey = RSA_new();
    RSA_set0_key(m_PublicKey, BN_dup(RSA_get0_n(m_PrivateKey)), BN_dup(exponent), nullptr);

    // Free the exponent as it is duplicated in publicKey and privateKey
    BN_free(exponent);

    char *publicKeyStr = nullptr;
    BIO *bio = BIO_new(BIO_s_mem());
    PEM_write_bio_RSAPublicKey(bio, m_PublicKey);
    size_t keylen = BIO_pending(bio);
    publicKeyStr = (char *)malloc(keylen + 1);
    BIO_read(bio, publicKeyStr, keylen);
    publicKeyStr[keylen] = 0;
    BIO_free_all(bio);

    free(publicKeyStr); // Don't forget to free allocated memory
}

// Method to send funds to another wallet
Transaction Wallet::sendFunds(Wallet &receiver, float amount)
{
    // Generate a nonce (for simplicity, this could be a random number)
    int nonce = 12345; // Replace with your nonce generation logic

    Transaction tx(m_Id, receiver.m_Id, amount, nonce);
    tx.sign(m_PrivateKey); // Sign the transaction
    std::cout << m_PrivateKey << std::endl;

    return tx;
}

// Method to update balance based on the blockchain transactions
void Wallet::updateBalance(const std::vector<Transaction> &transactions)
{
    for (const auto &tx : transactions)
    {
        if (tx.m_Sender == m_Id)
        {
            m_Balance -= tx.m_Amount;
        }
        if (tx.m_Receiver == m_Id)
        {
            m_Balance += tx.m_Amount;
        }
    }
}

// Method to print wallet details
void Wallet::printWalletData() const
{
    std::cout << "Wallet ID: " << m_Id << std::endl;
    std::cout << "Balance: " << m_Balance << std::endl;
    std::cout << "Public Key: " << m_PublicKey << std::endl;
    // You can add more fields to print as necessary,
    // such as displaying a simplified form of the public key, etc.

    // Note: be careful about logging sensitive information such as private keys.
}
