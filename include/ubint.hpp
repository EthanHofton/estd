#ifndef ubint_hpp
#define ubint_hpp

#include <iostream>
#include <stdexcept>
#include <vector>

namespace estd
{
    // unsgined big integer
    class ubint
    {
    private:

        // store each digit of the number as each byte (char) strung together
        std::string digits;

    public:

        // constructors
        // int constructor
        ubint(unsigned long long n = 0);
        // string constructor
        ubint(std::string s);
        // copy constructor
        ubint(const ubint &u);

        // check if a ubint is null
        friend bool null(const ubint &);
        // return the length of a ubint
        friend int length(const ubint &);

        // member access
        // [] operator overload
        int operator[](const int) const;
        // get the string value of the ubint
        std::string value() const;

        // direct assignment
        ubint &operator=(const ubint &);

        // post/pre incrementation
        ubint &operator++();
        ubint operator++(int);
        ubint &operator--();
        ubint operator--(int);

        // addition and subtraction
        // addition to self
        friend ubint &operator+=(ubint &, const ubint &);
        // addition
        friend ubint operator+(const ubint &, const ubint &);
        // subtraction
        friend ubint operator-(const ubint &, const ubint &);
        // subtraction to self
        friend ubint &operator-=(ubint &, const ubint &);

        // comparison operators
        // is equal to
        friend bool operator==(const ubint &, const ubint &);
        // is not equal to
        friend bool operator!=(const ubint &, const ubint &);
        // is grater than
        friend bool operator>(const ubint &, const ubint &);
        // is grater than or equal to
        friend bool operator>=(const ubint &, const ubint &);
        // is less than
        friend bool operator<(const ubint &, const ubint &);
        // is less than or equal to
        friend bool operator<=(const ubint &, const ubint &);

        // multiplication and division
        // multiply and assign
        friend ubint &operator*=(ubint &, const ubint &);
        // multiply
        friend ubint operator*(const ubint &, const ubint &);
        // divide and assign
        friend ubint &operator/=(ubint &, const ubint &);
        // divide
        friend ubint operator/(const ubint &, const ubint &);
    
        // modulo
        friend ubint operator%(const ubint &, const ubint &);
        // modulo and assign
        friend ubint &operator%=(ubint &, const ubint &);

        // bit shifts
        friend ubint operator<<(const ubint &, const ubint &);
        friend ubint operator>>(const ubint &, const ubint &);
    
        // exponent
        // raise to power and assign
        friend ubint &operator^=(ubint &, const ubint &);
        // raise to power
        friend ubint operator^(ubint &, const ubint &);

        // square root
        friend ubint sqrt(ubint &);

        // min, max
        // return the min of a and b
        friend ubint min(ubint &a, ubint &b);
        // return the max of a and b
        friend ubint max(ubint &a, ubint &b);

        // read and write
        // witre to output stream
        friend std::ostream &operator<<(std::ostream &, const ubint &);
        // read to input stream
        friend std::istream &operator>>(std::istream &, ubint &);

        // return n!
        friend ubint factorial(ubint &n);
        // maps ubint x from range (a, b) to (c, d)
        friend ubint map(ubint &x, ubint &a, ubint &b, ubint &c, ubint &d);
    };

    ubint::ubint(unsigned long long n)
    {
        do {
            digits.push_back(n % 10);
            n /= 10;
        } while (n);
    }

    ubint::ubint(std::string s)
    {
        digits = "";
        for (int i = s.size() - 1; i >= 0; i--)
        {
            if (!isdigit(s[i]))
            {
                throw std::invalid_argument("input must be a number");
            }

            digits.push_back(s[i] - '0');
        }
    }

    ubint::ubint(const ubint &u)
    {
        digits = u.digits;
    }



    std::ostream &operator<<(std::ostream &out, const ubint &a)
    {
        for (int i = a.digits.size() - 1; i >= 0; i--)
        {
            out << (short)a.digits[i];
        }

        return out;
    }

    std::istream &operator>>(std::istream &in, ubint &a)
    {
        std::string s;
        in >> s;
        int n = s.size();

        for (int i = n - 1; i >= 0; i--)
        {
            if (!isdigit(s[i]))
            {
                throw std::invalid_argument("input must be a number");
            }
            a.digits[n - i - 1] = s[i];
        }

        return in;
    }

    bool null(const ubint &a)
    {
        return (a.digits.size() == 1 && a.digits[0] == 0);
    }

    int length(const ubint &a)
    {
        return a.digits.size();
    }

    int ubint::operator[](const int index) const
    {
        if (digits.size() <= index || index < 0)
        {
            throw std::out_of_range("index out of range");
        }

        return digits[index];
    }

    std::string ubint::value() const
    {
        std::string val;
        for (int i = 0; i < digits.size(); i++)
        {
            val.insert(0, std::to_string(digits[i]));
        }

        return val;
    }

    ubint &ubint::operator=(const ubint &a)
    {
        digits = a.digits;
        return (*this);
    }

    ubint &ubint::operator++()
    {
        int i, n = digits.size();

        for (i = 0; i < n && digits[i] == 9; i++)
        {
            digits[i] = 0;
        }

        if (i == n)
        {
            digits.push_back(1);
        }
        else
        {
            digits[i]++;
        }

        return (*this);
    }

    ubint ubint::operator++(int temp)
    {
        ubint result = *this;

        if (temp != 0)
        {
            (*this) += temp;
        } else {
            ++(*this);
        }

        return result;
    }

    ubint &ubint::operator--()
    {
        if (null(*this))
        {
            throw std::underflow_error("underflow");
        }

        int i, n = digits.size();
        for (i = 0; i < n && digits[i] == 0; i++)
        {
            digits[i] = 9;
        }

        digits[i]--;
        if (n > 1 && digits[n - 1] == 0)
        {
            digits.pop_back();
        }

        return *this;
    }

    ubint ubint::operator--(int temp)
    {
        ubint result = *this;

        if (temp != 0)
        {
            (*this) -= temp;
        } else {
            --(*this);
        }

        return result;
    }

    ubint &operator+=(ubint &a, const ubint &b)
    {
        // t = carry, s = sum, i = index, n = length(a), m = length(b)
        int t = 0, s, i;
        int n = length(a), m = length(b);

        if (m > n)
        {
            a.digits.append(m - n, 0);
            n = length(a);
        }

        for (i = 0; i < n; i++)
        {
            if (i < m)
            {
                s = (a.digits[i] + b.digits[i]) + t;
            }
            else
            {
                s = (a.digits[i]) + t;
            }
            t = s / 10;
            a.digits[i] = (s % 10);
        }

        if (t)
        {
            a.digits.push_back(t);
        }

        return a;
    }

    ubint operator+(const ubint &a, const ubint &b)
    {
        ubint tmp = a;
        tmp += b;
        return tmp;
    }

    ubint operator-(const ubint &a, const ubint &b)
    {
        ubint tmp = a;
        tmp -= b;
        return tmp;
    }

    ubint &operator-=(ubint &a, const ubint &b)
    {
        if (a < b)
        {
            throw std::underflow_error("underflow. a cannot be less than b");
        }

        int n = length(a), m = length(b);
        int i, t = 0, s;

        for (i = 0; i < n; i++)
        {
            if (i < m)
            {
                s = (a.digits[i] - b.digits[i]) + t;
            }
            else
            {
                s = a.digits[i] + t;
            }

            if (s < 0)
            {
                s += 10;
                t = -1;
            }
            else
            {
                t = 0;
            }

            a.digits[i] = s;
        }

        while (n > 1 && a.digits[n - 1] == 0)
        {
            a.digits.pop_back();
            n--;
        }

        return a;
    }

    bool operator==(const ubint &a, const ubint &b)
    {
        return a.digits == b.digits;
    }

    bool operator!=(const ubint &a, const ubint &b)
    {
        return !(a == b);
    }

    bool operator>(const ubint &a, const ubint &b)
    {
        return b < a;
    }

    bool operator>=(const ubint &a, const ubint &b)
    {
        return !(a < b);
    }

    bool operator<(const ubint &a, const ubint &b)
    {
        int n = length(a), m = length(b);
        if (n != m)
        {
            return n < m;
        }

        while (n--)
        {
            if (a.digits[n] != b.digits[n])
            {
                return a.digits[n] < b.digits[n];
            }
        }

        return false;
    }

    bool operator<=(const ubint &a, const ubint &b)
    {
        return !(a > b);
    }

    ubint &operator*=(ubint &a, const ubint &b)
    {
        if (null(a) || null(b))
        {
            a = ubint();
            return a;
        }

        int n = length(a), m = length(b);
        std::vector<int> v(n + m, 0);
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                v[i+j] += (a.digits[i]) * (b.digits[j]);
            }
        }
        n += m;
        a.digits.resize(v.size());
        for (int s, i = 0, t = 0; i < n; i++)
        {
            s = t + v[i];
            v[i] = (s % 10);
            t = s / 10;
            a.digits[i] = v[i];
        }

        for (int i = n - 1; i >= 1 && !v[i]; i--)
        {
            a.digits.pop_back();
        }

        return a;
    }

    ubint operator*(const ubint &a, const ubint &b)
    {
        ubint tmp = a;
        tmp *= b;
        return tmp;
    }

    ubint &operator/=(ubint &a, const ubint &b)
    {
        if (null(b))
        {
            throw std::invalid_argument("cannot divide by zero");
        }

        if (a < b)
        {
            a = 0;
            return a;
        }

        if (a == b)
        {
            a = 1;
            return a;
        }

        int i, lgcat = 0, cc;
        int n = length(a);
        std::vector<int> cat(n, 0);
        ubint t;
        for (i = n - 1; t * 10 + a.digits[i] < b; i--)
        {
            t *= 10;
            t += a.digits[i];
        }

        for (; i >= 0; i--)
        {
            t = t * 10 + a.digits[i];
            for (cc = 9; cc * b > t; cc--);
            t -= cc * b;
            cat[lgcat++] = cc;
        }

        a.digits.resize(cat.size());
        for (i = 0; i < lgcat; i++)
        {
            a.digits[i] = cat[lgcat - i - 1];
        }
        a.digits.resize(lgcat);

        return a;
    }

    ubint operator/(const ubint &a, const ubint &b)
    {
        ubint tmp = a;
        tmp /= b;
        return tmp;
    }

    ubint operator%(const ubint &a, const ubint &b)
    {
        ubint tmp = a;
        tmp %= b;
        return tmp;
    }

    ubint &operator%=(ubint &a, const ubint &b)
    {
        if (null(b))
        {
            throw std::invalid_argument("cannot divide by zero");
        }

        if (b == 1 || a == b)
        {
            a = 0;
            return a;
        }

        if (a < b)
        {
            return a;
        }

        int i, lgcat = 0, cc;
        int n = length(a);
        std::vector<int> cat(n, 0);
        ubint t;
        for (i = n - 1; t * 10 + a.digits[i] < b; i--)
        {
            t *= 10;
            t += a.digits[i];
        }

        for (; i >= 0; i--)
        {
            t = t * 10 + a.digits[i];
            for (cc = 9; cc * b > t;cc--);
            t -= cc * b;
            cat[lgcat++] = cc;
        }

        a = t;
        return a;
    }

    ubint operator<<(const ubint &a, const ubint &b)
    {
        ubint res = a;
        for (ubint i = 0; i < b; i++)
        {
            res += res;
        }

        return res;
    }

    ubint operator>>(const ubint &a, const ubint &b)
    {
        ubint res = a;
        for (ubint i = 0; i < b; i++)
        {
            int add = 0;
            for (int i = res.digits.size() - 1; i >= 0; i--)
            {
                int digit = (res.digits[i] >> 1) + add;
                add = ((res.digits[i] & 1) * 5);
                res.digits[i] = digit;
            }

            while(res.digits.size() > 1 && !res.digits.back())
            {
                res.digits.pop_back();
            }
        }

        return res;
    }

    ubint &operator^=(ubint &a, const ubint &b)
    {
        ubint exp = b, base = a;
        a = 1;

        while(!null(exp))
        {
            if (exp[0] & 1)
            {
                
            }
        }
    }

    ubint operator^(ubint &a, const ubint &b)
    {

    }
}

#endif