#include <iostream>
#include <cstdint>
#include "../include/transaction.h" 

// fast modular exponentiation
uint64_t modexp(uint64_t base, uint64_t exp, uint64_t mod) {
    uint64_t result = 1;
    base %= mod;

    while (exp > 0) {
        if (exp & 1)
            result = (result * base) % mod;
        base = (base * base) % mod;
        exp >>= 1;
    }
    return result;
}

int main() {
    uint64_t n = 3233;     // p * q
    uint64_t e = 17;       // public exponent
    uint64_t d = 2753;     // private exponent

    uint64_t message = 42;

    // "Sign" with private key
    uint64_t signature = modexp(message, d, n);

    // "Verify" with public key
    uint64_t recovered = modexp(signature, e, n);

    std::cout << "Message:    " << message << "\n";
    std::cout << "Signature:  " << signature << "\n";
    std::cout << "Recovered:  " << recovered << "\n";

    if (recovered == message)
        std::cout << "Signature VALID\n";
    else
        std::cout << "Signature INVALID\n";

    Transaction transaction("send", "receiv", 100, "id"); 

    if(transaction.validateTransaction())
        std::cout << "validated" << '\n';  
    else 
        std::cout << "not validated" << '\n';  

    return 0;
}
