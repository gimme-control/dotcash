#pragma once
#include "uint256.h"
#include <map> 
#include <set> 
#include <transaction.h>
#include <iostream>

class MemPool
{
    private:
        std::map<uint256, Transaction> mem_pool; 

        // we need another data structure to hold transactions sorted by amount 
        std::multiset<std::pair<double, Transaction>> ordered_pool; 
        
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
            // if(ordered_pool.empty())
            //     std::cerr << "Pool is empty" << '\n';  

            // auto it = ordered_pool.rbegin();
            // return it->second; 
            return Transaction(); 
        }
}; 
