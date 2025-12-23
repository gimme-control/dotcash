#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <openssl/sha.h>
#include <iomanip>
#include "hashing.h"
#include "transaction.h"

class Block 
{
    private: 
        int index; // index 
        std::string timestamp; // curr timeestamp of block 
        std::vector<Transaction> transactions; // merkle root of prev transactiosn? 
        std::string previousHash; // hash of the prev block
        std::string hash; 

        int nonce; // you update this until you hit the hash we want? 

    public: 
        Block(int id, std::string time, std::vector<Transaction> txs, std::string prevHash)
        {
            index = id; 
            timestamp = time; 
            transactions = txs; 
            previousHash = prevHash; 
            nonce = 0; 
            hash = calculateHash(); 
        }

        std::string calculateHash() 
        {
            std::stringstream ss; 
            ss << index << timestamp << previousHash << nonce; 

            // adding transactions to the hash
            for(Transaction t : transactions)
                ss << t.transactionToString(); 

            return sha256(ss.str());  
        }


        // what is this function
        int mineBlock(int difficulty) // who sets this difficulty
        {
            std::string target(difficulty, '0'); 
            while(hash.substr(0, difficulty) != target)
            {
                nonce++; 
                hash = calculateHash(); 
            }
            return nonce; 
        }

        const std::string getHash() const 
        {
            return hash; 
        }
}; 


class BlockChain 
{
    private:
        std::vector<Block> chain; 
        int difficulty;
        
    public: 
        BlockChain(int diff, std::string date)
        {
            difficulty = diff; 
            chain.emplace_back(createGenesisBlock(date));
        }

        Block createGenesisBlock(std::string date)
        {

            // add some transaction that gives someone some initial money (?)
            std::vector<Transaction> transaction{};             

            // how can we add transactions now? 
            // maybe the genesis block just gives some coins to me? 
            return Block(0, date, transaction, "Genesis Block");
        }

        Block getLatestBlock()
        {
            return chain.back();  
        }

        bool isValidProof(const Block& block) 
        {

            return block.getHash().substr(0, difficulty) == std::string(difficulty, '0'); 
        }

        void addBlock(std::string data, std::vector<Transaction> transactions)
        {
            Block newBlock(chain.size(), data, transactions, chain.back().getHash()); 

            if (isValidProof(newBlock)) 
            {
                chain.push_back(newBlock); 
            }
        }
}; 
