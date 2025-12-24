#pragma once
#include "uint256.h"
#include <map> 
#include <set> 
#include <transaction.h>
#include <functional>

class MemPool
{
    private:
        std::map<uint256, Transaction> mem_pool; 


        // we need another data structure to hold transactions sorted by amount 
        std::multiset<std::pair<double, Transaction>, 
    std::greater<std::pair<double, Transaction>>> ordered_pool; 
        
    public: 
        MemPool()
        {
            mem_pool.clear(); 
            ordered_pool.clear(); 
        }

        void add_to_mempool(uint256 hash, Transaction transaction)
        {
            mem_pool[hash] = transaction; 
            ordered_pool.insert(
            std::pair<double, Transaction>(transaction.getAmount(), transaction)); 
        }

        Transaction get_value_transaction()
        {
            auto it = ordered_pool.begin();
            return it->second; 
        }
        
        ~MemPool(); 
}; 
