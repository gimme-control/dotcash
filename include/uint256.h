#include <array>
#include <string> 
#include <compare> 

class uint256
{
    private:    
        std::array<unsigned long long, 4> data; 
    public: 
        uint256() : data{0,0,0,0} {}

        auto operator<=>(const uint256&) const = default; 
        
        std::string to_string()
        {
            std::string res = ""; 
            for(unsigned long long i = 0; i < data.size(); ++i) 
            {
                res += std::to_string(data[i]); 
            }

            return res; 
        }
}; 
