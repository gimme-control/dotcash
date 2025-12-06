#include <string>

class Transaction
{
    std::string sender; 
    std::string recipient; 
    double amount; 
    std::string transactionID; 

    Transaction(std::string snd, std::string rcp, double amt, std::string txID)
    {
        sender = snd; 
        recipient = rcp; 
        amount = amt; 
        transactionID = txID; 
    }


    bool validateTransaction()
    {
        // implementation
        return true; 
    }


    
}
