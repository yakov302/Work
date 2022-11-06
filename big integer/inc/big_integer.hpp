#pragma once

#include <list>
#include <string>
#include <vector>
#include <iostream>
#include <string.h>

#define POSITIVE true
#define NEGATIVE false

class BigInteger
{
public:
    BigInteger();
    BigInteger(const char* number);
    BigInteger(std::string number);
    BigInteger(long long int  number);

    BigInteger(BigInteger const& source);
    BigInteger(BigInteger const&& source);

    BigInteger& operator=(const char* right_side);
    BigInteger& operator=(BigInteger const& right_side);
    BigInteger& operator=(BigInteger const&& right_side);
    BigInteger& operator=(std::string const& right_side);
    BigInteger& operator=(std::string const&& right_side);
    BigInteger& operator=(long long int const& right_side);

    BigInteger& operator+(BigInteger& right_side);
    BigInteger& operator+(BigInteger&& right_side);
    BigInteger& operator-(BigInteger const& right_side);
    BigInteger& operator*(BigInteger const& right_side);

    size_t num_of_digits()const;
    bool operator==(BigInteger const& right_side)const; 
    bool operator<(BigInteger const& right_side)const;
    friend  std::ostream& operator<<(std::ostream& a_os, BigInteger const& big_int);

private:
    bool m_sign;
    std::list<int> m_big_int;
};

