#include <iostream> 
#include <string> 
#include <openssl/sha.h>
#include <iomanip>

// so this is a sha256 hash. 
//
// trying to understand it to implement a blockchain w it.
int main()
{
    unsigned char hash[SHA256_DIGEST_LENGTH];  
    // 32 bytes.. 
    // 32 * 8 = 256. makes sense

    std::cout << SHA256_DIGEST_LENGTH << '\n'; 

    std::string str; // take in input
    std::cin >> str; 

    SHA256_CTX sha256; // what is this ? 

    SHA256_Init(&sha256);    
    SHA256_Update(&sha256, str.c_str(), str.length());    
    SHA256_Final(hash, &sha256);    

    std::stringstream ss;    

    for(int i = 0; i < SHA256_DIGEST_LENGTH; i++) {        
        ss << std::hex << std::setw(2) << std::setfill('0') << (int)hash[i];    
    }    

    std::cout << ss.str() << '\n'; 

    return 0; 
}
