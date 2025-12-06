#include <array>
class uint256
{
    private:    
        std::array<unsigned int, 8> data; 
    public: 
        bool equals(unsigned int x[], unsigned int y[])
        {
            for(int i = 0; i < 8; ++i) 
            {
                if(x[i] != y[i]) 
                    return false; 
            }
            return true; 
        }

        bool greater(unsigned int x[], unsigned int y[])
        {
            for(int i = 0; i < 8; ++i) 
            {
                if(x[i] < y[i]) 
                    ; 
            }
            return true; 
        }
}; 
