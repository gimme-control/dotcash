#include <string>

// We will be using UTXO system here because we want it to be like real cash:q
class Transaction
{
    private: 
        std::string sender; 
        std::string recipient; 
        double amount; 
        std::string transactionID; 

    public: 
        Transaction(std::string snd, std::string rcp, double amt, std::string txID)
        {
            sender = snd; 
            recipient = rcp; 
            amount = amt; 
            transactionID = txID; 
        }


        ~Transaction();

        std::string transactionToString()
        {
            return sender + recipient + std::to_string(amount) + transactionID; 
        }

        bool validateTransaction() // learn public private key stuff 
        {
            // implementation 
            // use public key to validate it ? 
            return true; 
        }

}; 
