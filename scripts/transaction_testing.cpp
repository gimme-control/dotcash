// Source - https://stackoverflow.com/a
// Posted by Jerry Coffin, modified by community. See post 'Timeline' for change history
// Retrieved 2025-12-20, License - CC BY-SA 4.0

#include <iostream>
#include <iterator>
#include <algorithm>
#include <string>
#include <vector>
#include <functional>

const int e_key = 47;
const int d_key = 15;
const int n = 391;

struct crypt : std::binary_function<int, int, int> {
    int operator()(int input, int key) const { 
        int result = 1;
        for (int i=0; i<key; i++) {
            result *= input;
            result %= n;
        }
        return result;
    }
};

int main() {
    // so we use assymetric encryption for a transaction. 
    // so a single transaction has to be verified through assymetric thingie, 
    // its sent to a mempool and then miners will go through the mempool and clean up 


    // imma try private key public key here 


    std::string msg = "Drink more Ovaltine.";
    std::vector<int> encrypted; // array 

    std::transform(msg.begin(), msg.end(),  
        std::back_inserter(encrypted),
        std::bind2nd(crypt(), e_key));

    for(int i : encrypted)
        std::cout << i; 
    std::cout << '\n'; 

    std::transform(encrypted.begin(), encrypted.end(), 
        std::ostream_iterator<char>(std::cout, ""), 
        std::bind2nd(crypt(), d_key));
    std::cout << "\n";

    return 0;
}
