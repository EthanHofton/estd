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
        // false for posative
        // true for negative
        bool sign = false;

    public:

        // constructors
        // int constructor
        bint(const long long int& n = 0);
        // string constructor
        bint(const std::string& s);
        // const char* constructor
        bint(const char* s);
        // copy constructor
        bint(const bint &u);

        // check if a ubint is null
        friend bool null(const bint &);
        // return the length of a ubint
        friend int length(const bint &);
        // check if the number is negative
        friend bool negative(const bint &a);

        // member access
        // [] operator overload
        int operator[](const int) const;
        // get the string value of the ubint
        std::string value() const;

        // direct assignment
        bint &operator=(const bint &);

        // post/pre incrementation
        bint &operator++();
        bint operator++(int);
        bint &operator--();
        bint operator--(int);

        // flip sign
        friend bint operator-(const bint &);

        // addition and subtraction
        // addition to self
        friend bint &operator+=(bint &, const bint &);
        // addition
        friend bint operator+(const bint &, const bint &);
        // subtraction
        friend bint operator-(const bint &, const bint &);
        // subtraction to self
        friend bint &operator-=(bint &, const bint &);

        // comparison operators
        // is equal to
        friend bool operator==(const bint &, const bint &);
        // is not equal to
        friend bool operator!=(const bint &, const bint &);
        // is grater than
        friend bool operator>(const bint &, const bint &);
        // is grater than or equal to
        friend bool operator>=(const bint &, const bint &);
        // is less than
        friend bool operator<(const bint &, const bint &);
        // is less than or equal to
        friend bool operator<=(const bint &, const bint &);

        // multiplication and division
        // multiply and assign
        friend bint &operator*=(bint &, const bint &);
        // multiply
        friend bint operator*(const bint &, const bint &);
        // divide and assign
        friend bint &operator/=(bint &, const bint &);
        // divide
        friend bint operator/(const bint &, const bint &);

        // modulo
        friend bint operator%(const bint &, const bint &);
        // modulo and assign
        friend bint &operator%=(bint &, const bint &);

        // bit shifts
        friend bint operator<<(const bint &, const bint &);
        friend bint &operator<<=(bint &, const bint &);
        friend bint operator>>(const bint &, const bint &);
        friend bint &operator>>=(bint &, const bint &);

        // exponent
        // raise to power and assign
        friend bint &operator^=(bint &, const bint &);
        // raise to power
        friend bint operator^(const bint &, const bint &);

        // square root
        friend bint sqrt(const bint &);

        // min, max
        // return the min of a and b
        friend bint min(const bint &a, const bint &b);
        // return the max of a and b
        friend bint max(const bint &a, const bint &b);

        // read and write
        // witre to output stream
        friend std::ostream &operator<<(std::ostream &, const bint &);
        // read to input stream
        friend std::istream &operator>>(std::istream &, bint &);

        // return n!
        friend bint factorial(const bint &n);
        // maps ubint x from range (a, b) to (c, d)
        friend bint map(const bint &x, const bint &a, const bint &b, const bint &c, const bint &d);
    };

    bint::bint(const long long int& n)
    {
        if (n < 0)
        {
            sign = true;
            number = std::abs(n);
            return;
        }

        number = n;
    }

    bint::bint(const std::string& s)
    {
        if (s[0] == '-')
        {
            sign = true;
            number = s.substr(1);
            return;
        }

        number = s;
    }

    bint::bint(const char* s) : bint(std::string(s)) {}

    bint::bint(const bint &u)
    {
        sign = u.sign;
        number = u.number;
    }

    std::ostream &operator<<(std::ostream &out, const bint &a)
    {
        if (a.sign)
        {
            out << "-";
        }

        out << a.number;

        return out;
    }

    std::istream &operator>>(std::istream &in, bint &a)
    {
        std::string s;
        in >> s;
        
        a = (bint)s;

        return in;
    }

    bool null(const bint &a)
    {
        return null(a.number);
    }

    int length(const bint &a)
    {
        return length(a.number);
    }

    bool negative(const bint &a)
    {
        return (a.sign && (a.number != 0ULL));
    }

    int bint::operator[](const int index) const
    {
        if (length(number) <= index || index < 0)
        {
            throw std::out_of_range("index out of range");
        }

        return number[index];
    }

    std::string bint::value() const
    {
        std::string val = (negative(*this)) ? "-" : "";

        val += number.value();

        return val;
    }

    bint &bint::operator=(const bint &a)
    {
        number = a.number;
        sign = a.sign;
        return (*this);
    }

    bint &bint::operator++()
    {
        if (negative(*this))
        {
            if (number == 1)
            {
                sign = false;
                number = 0ULL;
            } 
            else
            {
                --number;
            }
        }
        else
        {
            ++number;
        }

        return *this;
    }

    bint bint::operator++(int temp)
    {
        bint result = *this;

        if (temp != 0)
        {
            (*this) += temp;
        } else {
            ++(*this);
        }

        return result;
    }

    bint &bint::operator--()
    {
        if (negative(*this))
        {
            ++number;
        }
        else
        {
            if (number == 0ULL)
            {
                sign = true;
                number = 1;
            }
            else
            {
                --number;
            }
        }

        return *this;
    }

    bint bint::operator--(int temp)
    {
        bint result = *this;

        if (temp != 0)
        {
            (*this) -= temp;
        } else {
            --(*this);
        }

        return result;
    }

    bint operator-(const bint &a)
    {
        bint tmp = a;
        tmp.sign = !tmp.sign;
        return tmp;
    }

    bint &operator+=(bint &a, const bint &b)
    {
        // -a + -b or a + b
        // if a and b are posative or if a and b are negative, a + b
        if ( (!negative(a) && !negative(b)) || (negative(a) && negative(b)))
        {
            a.number += b.number;
            return a;
        }

        // -a + b = b - a
        // b - a
        // if a is negative and b is posative, this is the same as
        // b + a where b is posative and a is negative
        // this is the same as the case below (a posative, b negative) and is used
        // to stop repeting code
        if (negative(a) && !negative(b))
        {
            a = b - (-a);
        }

        // a + -b = a - (-b)
        // if a is posative and b is negative
        if (!negative(a) && negative(b))
        {
            a = a - (-b);
        }

        return a;
    }

    bint operator+(const bint &a, const bint &b)
    {
        bint tmp = a;
        tmp += b;
        return tmp;
    }

    bint operator-(const bint &a, const bint &b)
    {
        bint tmp = a;
        tmp -= b;
        return tmp;
    }

    bint &operator-=(bint &a, const bint &b)
    {
        // if b is negative and a is posative (a -- b = a + b)
        // a + b
        if (!negative(a) && negative(b))
        {
            a = a + -b;
            return a;
        }

        // if a is negative and b is posative (-a - b)
        // -a - b
        // a can only get more negative
        if (negative(a) && !negative(b))
        {
            a.number += b.number;
            return a;
        }

        // if a is posative and b is posative (a - b)
        // a - b
        if (!negative(a) && !negative(b))
        {
            // if b is bigger then a, the number will be negative
            if (b.number > a.number)
            {
                a.sign = true;
                ubint reminder = b.number - a.number;
                a.number = reminder;
            }
            else
            {
                a.number -= b.number;
            }

            return a;
        }

        // if a is negative and b is negative (-a - -b = -a + b)
        // b - a
        if (negative(a) && negative(b))
        {
            a = (-b) - (-a);
            return a;
        }

        return a;
    }

    bool operator==(const bint &a, const bint &b)
    {
        return (negative(a) == negative(b) && a.number == b.number);
    }

    bool operator!=(const bint &a, const bint &b)
    {
        return !(a == b);
    }

    bool operator>(const bint &a, const bint &b)
    {
        if (!negative(a) && negative(b))
        {
            return true;
        }

        if (!negative(b) && negative(a))
        {
            return false;
        }

        if (negative(a) && negative(b))
        {
            return (a.number < b.number);
        }

        if (!negative(a) && !negative(b))
        {
            return (a.number > b.number);
        }

        return false;
    }

    bool operator>=(const bint &a, const bint &b)
    {
        return !(a < b);
    }

    bool operator<(const bint &a, const bint &b)
    {
        return b > a;
    }

    bool operator<=(const bint &a, const bint &b)
    {
        return !(a > b);
    }

    bint &operator*=(bint &a, const bint &b)
    {
        a.number *= b.number;
        a.sign = (a.sign ^ b.sign);

        return a;
    }

    bint operator*(const bint &a, const bint &b)
    {   
        bint tmp = a;
        tmp *= b;
        return tmp;
    }

    bint &operator/=(bint &a, const bint &b)
    {
        a.number /= b.number;
        a.sign = (a.sign ^ b.sign);

        return a;
    }

    bint operator/(const bint &a, const bint &b)
    {
        bint tmp = a;
        tmp /= b;
        return tmp;
    }

    bint operator%(const bint &a, const bint &b)
    {
        bint tmp = a;
        tmp %= b;
        return tmp;
    }

    bint &operator%=(bint &a, const bint &b)
    {
        a.number %= b.number;
        a.sign = (a.sign && b.sign) || (b.sign && !a.sign);

        return a;
    }

    bint operator<<(const bint &a, const bint &b)
    {
        bint tmp = a;
        tmp <<= b;
        return tmp;
    }

    bint &operator<<=(bint &a, const bint &b)
    {
        if (negative(b))
        {
            throw std::invalid_argument("bit shift count cannot be negative");
        }

        a.number <<= b.number;
        return a;
    }

    bint operator>>(const bint &a, const bint &b)
    {
        bint tmp = a;
        tmp >>= b;
        return tmp;
    }

    bint &operator>>=(bint &a, const bint &b)
    {
        if (negative(b))
        {
            throw std::invalid_argument("bit shift count cannot be negative");
        }

        a.number >>= b.number;
        return a;
    }

    bint &operator^=(bint &a, const bint &b)
    {
        bint exp = b, base = a;
        a = 1;

        while (!null(exp))
        {
            if (exp[0] & 1)
            {
                a *= base;
            }

            base *= base;
            exp >>= 1;
        }

        return a;
    }

    bint operator^(const bint &a, const bint &b)
    {
        bint tmp = a;
        tmp ^= b;
        return tmp;
    }

    bint sqrt(const bint &a)
    {
        if (negative(a))
        {
            throw std::invalid_argument("cannot squere root negative number");
        }

        bint res;
        res.number = sqrt(a.number);
        res.sign = false;
        return res;
    }

    bint min(const bint &a, const bint &b)
    {
        if (a < b)
        {
            return a;
        }

        return b;
    }

    bint max(const bint &a, const bint &b)
    {
        if (a > b)
        {
            return a;
        }

        return b;
    }

    bint factorial(const bint &n)
    {
        if (n.number == 1)
        {
            return 1;
        }

        if (negative(n))
        {
            return n * factorial(n + 1);
        }
        else
        {
            return n * factorial(n - 1);
        }
    }

    bint map(const bint &x, const bint &a, const bint &b, const bint &c, const bint &d)
    {
        return (x - a) * (d - c) / (b - a) + c;
    }
}

#endif