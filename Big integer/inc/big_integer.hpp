#pragma once

#include <list>
#include <string>
#include <vector>
#include <math.h>
#include <iostream>
#include <string.h>


#define POSITIVE true
#define NEGATIVE false
#define FIRST 1
#define SECOND 2
#define EQUALS 3

using  BigIntList = std::list<int>;
using  BigIntIterator = std::_List_iterator<int>;

class BigInteger
{
public:
    BigInteger();
    BigInteger(const char* number);
    BigInteger(std::string number);
    BigInteger(long long int number);

    BigInteger(BigInteger const& source);
    BigInteger(BigInteger const&& source);

    BigInteger& operator=(const char* right_side);
    BigInteger& operator=(BigInteger const& right_side);
    BigInteger& operator=(BigInteger const&& right_side);
    BigInteger& operator=(std::string const& right_side);
    BigInteger& operator=(std::string const&& right_side);
    BigInteger& operator=(long long int const& right_side);

    BigInteger operator+(BigInteger& right_side);
    BigInteger operator+(BigInteger&& right_side);
    BigInteger operator-(BigInteger& right_side);
    BigInteger operator-(BigInteger&& right_side);
    BigInteger operator*(BigInteger& right_side);
    BigInteger operator*(BigInteger&& right_side);


    size_t num_of_digits()const;
    bool operator==(BigInteger const& right_side)const; 
    bool operator<(BigInteger const& right_side)const;
    
    long long int convert_big_int_to_long_long(); // Warning - use only for numbers smaller than sizeof(long long int)
    friend  std::ostream& operator<<(std::ostream& a_os, BigInteger const& big_int);

//private:
    bool m_sign;
    BigIntList m_big_int;
};

