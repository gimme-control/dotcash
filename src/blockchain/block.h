#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <openssl/sha.h>
#include <iomanip>

std::string sha256(const std::string str) {    
    unsigned char hash[SHA256_DIGEST_LENGTH];    
    SHA256_CTX sha256;    

    SHA256_Init(&sha256);    
    SHA256_Update(&sha256, str.c_str(), str.length());    
    SHA256_Final(hash, &sha256);    

    std::stringstream ss;    

    for(int i = 0; i < SHA256_DIGEST_LENGTH; i++) {        
        ss << std::hex << std::setw(2) << std::setfill('0') << (int)hash[i];    
    }    

    return ss.str();
}

class Block 
{
    public: 
        int index; 
        std::string timestamp;
        std::vector<Transaction> transactions; 
        std::string previousHash; 
        std::string hash; 

        int nonce; 

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
        // Add transactions 
        return sha256(ss.str());  
    }


    void mineBlock(int difficulty) 
    {
        std::string target(difficulty, '0');  
        while(hash.substr(0, difficulty) != target)
        {
            nonce++; 
            hash = calculateHash(); 
        }
    }

    void proofOfWork(int difficulty)
    {
        std::string target(difficulty, '0'); 
        do {
            proof++;  
        } while (hash.substr(0, difficulty) != target);
    }

}; 


class BlockChain 
{
    public:
        std::vector<Block> chain; 
        int difficulty;
        
        BlockChain(int diff)
        {
            difficulty = diff; 
            chain.emplace_back(createGenesisBlock());
        }

        Block createGenesisBlock()
        {
            return Block(0, "10/31/2025", "Genesis Block", "0");
        }

        Block getLatestBlock()
        {
            return chain.back();  
        }

        bool isValidProof(const Block& block) const 
        {
            return block.hash.substr(0, difficulty) == std::string(difficulty, '0'); 
        }

        void addBlock(std::string data)
        {
            Block newBlock(chain.size(), data, chain.back().hash); 
            newBlock.proofOfWork(difficulty)
            if (isValidProof(newBlock)) 
            {
                chain.push_back(newBlock); 
            }
        }

}; 
