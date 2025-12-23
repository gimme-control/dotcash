#include <iostream>
#include "../include/block.h" 
#include <openssl/sha.h>
#include <chrono>
#include <unordered_map>
#include <map> 

// important note use the uint256 data structure for hashes instead of strings.
std::map<uint256, Transaction> mem_pool; 

int send_to(std::string receiver_address, std::string sender_address, double amount)
{
    // basically use Transaction to create a new transaction. 
    // check if the inputs and outputs are valid and everything matches. 
    // then add it to your own mem pool and send it to other people. 

    uint256 txID; 
    Transaction transaction(sender_address, receiver_address, amount, txID); 

    if(transaction.validateTransaction())
    {
        // add transaction to the mem pool and send to other nodes
        mem_pool[transaction.getTxHash()] = transaction; 
    }

    else 
    {
        std::cout << "bad transaction" << '\n'; 
        return 1; 
    }

    return 0; 
}

int main() 
{
    // everything for now is oging to ignore networking, all run locally using IPC
    // we create our blockchain
    BlockChain test_net(1, "12/22/2025"); // change this to date rn

    // cli so we can test adding blocks and the functionality locally
    while(true)
    {
        std::string userIn; 
        std::cin >> userIn; 
        
        // probably in a parallel thread keep listening for like other nodes communicating
        // transaction information or block info etc etc. 

        if(userIn == "mine") // trying to mine some block
        {
            // basically traverse the mempool. find the transactions which have the 
            // highest amount (cuz they have highest fee)
            // then add them to the block until the block is full 
            // start mining that block and find the hash for it 
            // then broadcast this block to every node in the network
        }

        else if(userIn == "transaction") // want to make a transaction
        {
            std::string sender_address; 
            std::string receiver_address; 

            std::cin >> sender_address >> receiver_address; 

            send_to(receiver_address, sender_address, 10); 
        }


        else if(userIn == "balance") // get balance of your account (?)
        {
            std::cout << "TBD" << '\n';  
        }


        else if(userIn == "status") // status for debugging (TBD)
        { 
            std::cout << test_net.getLatestBlock().getHash() << '\n'; 
            std::cout << "TBD" << '\n'; 
        }

    }

    return 0;
}
