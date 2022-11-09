#pragma once

#include <list>
#include <string>
#include <vector>
#include <math.h>
#include <iostream>
#include <string.h>
 #include <functional>

namespace big_integer
{

#define POSITIVE true
#define NEGATIVE false
#define FIRST 1
#define SECOND 2
#define EQUALS 3

using  BigIntList = std::list<int>;
using Compare = std::function<bool(int, int)>;
using  BigIntIterator = std::_List_iterator<int>;

class BigInteger
{
public:
    BigInteger();
    BigInteger(const char* number);
    BigInteger(long long int number);
    BigInteger(std::string const& number);
    BigInteger(std::string const&& number);

    BigInteger(BigInteger const& source);
    BigInteger(BigInteger const&& source);

    BigInteger& operator=(const char* right_side);
    BigInteger& operator=(BigInteger const& right_side);
    BigInteger& operator=(BigInteger const&& right_side);
    BigInteger& operator=(std::string const& right_side);
    BigInteger& operator=(std::string const&& right_side);
    BigInteger& operator=(long long int const& right_side);

    BigInteger operator+(const char* right_side);
    BigInteger operator+(long long int right_side);
    BigInteger operator+(std::string& right_side);
    BigInteger operator+(std::string&& right_side);
    BigInteger operator+(BigInteger& right_side);
    BigInteger operator+(BigInteger&& right_side);

    BigInteger operator-(const char* right_side);
    BigInteger operator-(long long int right_side);
    BigInteger operator-(std::string& right_side);
    BigInteger operator-(std::string&& right_side);
    BigInteger operator-(BigInteger& right_side);
    BigInteger operator-(BigInteger&& right_side);

    BigInteger operator*(const char* right_side);
    BigInteger operator*(long long int right_side);
    BigInteger operator*(std::string& right_side);
    BigInteger operator*(std::string&& right_side);
    BigInteger operator*(BigInteger& right_side);
    BigInteger operator*(BigInteger&& right_side);

    BigInteger operator/(const char* right_side);
    BigInteger operator/(long long int right_side);
    BigInteger operator/(std::string& right_side);
    BigInteger operator/(std::string&& right_side);
    BigInteger operator/(BigInteger& right_side);
    BigInteger operator/(BigInteger&& right_side);

    BigInteger operator%(const char* right_side);
    BigInteger operator%(long long int right_side);
    BigInteger operator%(std::string& right_side);
    BigInteger operator%(std::string&& right_side);
    BigInteger operator%(BigInteger& right_side);
    BigInteger operator%(BigInteger&& right_side);

    //power operator
    BigInteger operator^(const char* right_side);
    BigInteger operator^(long long int right_side);
    BigInteger operator^(std::string& right_side);
    BigInteger operator^(std::string&& right_side);
    BigInteger operator^(BigInteger& right_side);  
    BigInteger operator^(BigInteger&& right_side);

    BigInteger operator++();
    BigInteger operator--();  
    BigInteger operator++(int); 
    BigInteger operator--(int);  

    BigInteger operator+=(const char* right_side);
    BigInteger operator+=(long long int right_side);
    BigInteger operator+=(std::string& right_side);
    BigInteger operator+=(std::string&& right_side);
    BigInteger operator+=(BigInteger& right_side);
    BigInteger operator+=(BigInteger&& right_side);

    BigInteger operator-=(const char* right_side);
    BigInteger operator-=(long long int right_side);
    BigInteger operator-=(std::string& right_side);
    BigInteger operator-=(std::string&& right_side);
    BigInteger operator-=(BigInteger& right_side);
    BigInteger operator-=(BigInteger&& right_side);

    BigInteger operator*=(const char* right_side);
    BigInteger operator*=(long long int right_side);
    BigInteger operator*=(std::string& right_side);
    BigInteger operator*=(std::string&& right_side);
    BigInteger operator*=(BigInteger& right_side);
    BigInteger operator*=(BigInteger&& right_side);

    BigInteger operator/=(const char* right_side);
    BigInteger operator/=(long long int right_side);
    BigInteger operator/=(std::string& right_side);
    BigInteger operator/=(std::string&& right_side);
    BigInteger operator/=(BigInteger& right_side);
    BigInteger operator/=(BigInteger&& right_side);

    BigInteger operator%=(const char* right_side);
    BigInteger operator%=(long long int right_side);
    BigInteger operator%=(std::string& right_side);
    BigInteger operator%=(std::string&& right_side);
    BigInteger operator%=(BigInteger& right_side);
    BigInteger operator%=(BigInteger&& right_side);

    BigInteger operator^=(const char* right_side);
    BigInteger operator^=(long long int right_side);
    BigInteger operator^=(std::string& right_side);
    BigInteger operator^=(std::string&& right_side);
    BigInteger operator^=(BigInteger& right_side);
    BigInteger operator^=(BigInteger&& right_side);

    bool operator==(BigInteger& right_side);
    bool operator==(BigInteger&& right_side);
    bool operator!=(BigInteger& right_side);
    bool operator!=(BigInteger&& right_side);  
    bool operator<(BigInteger& right_side);
    bool operator<(BigInteger&& right_side);
    bool operator>(BigInteger& right_side);
    bool operator>(BigInteger&& right_side);
    bool operator<=(BigInteger& right_side);
    bool operator<=(BigInteger&& right_side);
    bool operator>=(BigInteger& right_side);
    bool operator>=(BigInteger&& right_side);
    
    bool& sign();
    size_t num_of_digits()const;
    std::string convert_big_int_to_string();
    friend std::ostream& operator<<(std::ostream& a_os, BigInteger const& big_int);
    long long int convert_big_int_to_long_long(); // Warning!!! use only for numbers smaller than sizeof(long long int)

private:
    bool m_sign;
    BigIntList m_big_int;
};


} //namespace big_integer
