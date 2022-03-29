#ifndef bint_hpp
#define bint_hpp

#include <ubint.hpp>

namespace estd
{
    // big integer
    class bint
    {
    private:
        // the actual number
        ubint number;

        // stores the sign of the number
        bool sign;

    public:

        // constructors
        // int constructor
        bint(long long int n = 0);
        // string constructor
        bint(std::string s);
        // copy constructor
        bint(const ubint &u);
    };
}

#endif