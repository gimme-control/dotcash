#pragma once 
#include <string>
#include "uint256.h" 

// We will be using UTXO system here because we want it to be like real cash:q
class Transaction
{
    private: 
        std::string sender; 
        std::string recipient; 
        double amount; 
        uint256 txHash; 

    public: 
        Transaction(std::string snd, std::string rcp, double amt, uint256 txID)
        {
            sender = snd; 
            recipient = rcp; 
            amount = amt; 
            txHash = txID; 
        }

        ~Transaction();

        uint256 getTxHash()
        {
            return txHash; 
                
        }

        // debug statement 
        std::string transactionToString()
        {
            return sender + recipient + std::to_string(amount); 
        }

        bool validateTransaction() // learn public private key stuff 
        {
            // implementation 
            // use public key to validate it ? 
            return true; 
        }

}; 
