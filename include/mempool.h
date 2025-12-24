#pragma once
#include <map> 
#include <set> 
#include <transaction.h>

class MemPool
{
    private:
        std::map<uint256, Transaction> mem_pool; 

        // we need another data structure to hold transactions sorted by amount 
        std::multiset<Transaction> ordered_pool; 
        
    public: 
        MemPool()
        {
            mem_pool.clear(); 
            ordered_pool.clear(); 
        }


        void add_to_mempool(uint256 hash, Transaction transaction)
        {
            mem_pool[hash] = transaction; 
        }
        
        ~MemPool(); 

}; 
