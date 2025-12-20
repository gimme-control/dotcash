#include <string>

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


        std::string transactionToString()
        {
            return sender + recipient + std::to_string(amount) + transactionID; 
        }

        bool validateTransaction() // learn public private key stuff 
        {
            // implementation 
            return true; 
        }
    
}; 
