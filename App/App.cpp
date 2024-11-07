#include "App.hpp"

#include "Blockchain.hpp"
#include "HelloWorld.hpp"
#include "Wallet.hpp"

#include <iostream>

int main(int argc, char *argv[], char *env[])
{
    std::cout << HEADER;

    // HelloWorld library
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

    return 0;
}
