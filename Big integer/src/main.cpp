#include <iostream>
#include <stdlib.h>  
#include <math.h>
#include <time.h>     
#include <random>
#include <limits>

#include "big_integer.hpp"

#define YELLOW "\x1B[33m"
#define NORMAL "\x1B[0m"
#define GREEN "\x1B[32m"
#define RED "\x1B[91m"

#define MAX_DEV 99999999999999
#define MAX_ADD 99999999999999
#define MAX_SUB 99999999999999
#define MAX_MUL 9999999

using namespace big_integer;

void contractor(long long int a, long long int b)
{
    if(a == b)
    {
        std::cout << GREEN;
        std::cout << "PASS!!!\n";
        std::cout << NORMAL;
        std::cout << a << " == " << b << "\n\n";
    }
    else
    {
        std::cout << RED;
        std::cout << "FAIL!!!\n";
        std::cout << NORMAL;
        std::cout << a << " != " << b << "\n\n";
    }
}

void contractor_test()
{
    std::cout << YELLOW;
    std::cout << "\n***contractor tests***" << "\n\n";
    std::cout << NORMAL;

    BigInteger a(4654685464656546);
    contractor(a.convert_big_int_to_long_long(), 4654685464656546);

    BigInteger b(-6546546556);
    contractor(b.convert_big_int_to_long_long(), -6546546556);

    contractor(BigInteger(8987989989).convert_big_int_to_long_long(), 8987989989);
    contractor(BigInteger(-5465866).convert_big_int_to_long_long(), -5465866);

    char char1[20] = "15654656546";
    BigInteger c(char1);
    contractor(c.convert_big_int_to_long_long(), 15654656546);

    char char2[20] = "-6546565465";
    BigInteger d(char2);
    contractor(d.convert_big_int_to_long_long(), -6546565465);

    char char3[20] = "0";
    BigInteger e(char3);
    contractor(e.convert_big_int_to_long_long(), 0);

    BigInteger f("85646546546");
    contractor(f.convert_big_int_to_long_long(), 85646546546);

    BigInteger g("-6465465465");
    contractor(g.convert_big_int_to_long_long(), -6465465465);

    BigInteger h("0");
    contractor(h.convert_big_int_to_long_long(), 0);

    std::string s = "564654656";
    BigInteger i(s);
    contractor(i.convert_big_int_to_long_long(), 564654656);

    std::string s2 = "-65846565";
    BigInteger j(s2);
    contractor(j.convert_big_int_to_long_long(), -65846565);

    std::string s3 = "0";
    BigInteger k(s3);
    contractor(k.convert_big_int_to_long_long(), 0);

    BigInteger l(std::string("1654684646"));
    contractor(l.convert_big_int_to_long_long(), 1654684646);

    BigInteger m(std::string("-68495615"));
    contractor(m.convert_big_int_to_long_long(), -68495615);

    BigInteger n(std::string("0"));
    contractor(n.convert_big_int_to_long_long(), 0);
}

long long int getRandom() 
{
    std::random_device rd;    
    std::mt19937_64 eng(rd());
    std::uniform_int_distribution<long long int> distr;
    return distr(eng);
};

bool add(long long int a, long long int b)
{
    BigInteger result = BigInteger(a) + BigInteger(b);
    if(result.convert_big_int_to_long_long() == a+b)
    {
        std::cout << GREEN;
        std::cout << "PASS!!!\n";
        std::cout << NORMAL;
        std::cout << a << " + " << b << " = " << result << "\n\n";
        return true;
    }
    else
    {
        std::cout << RED;
        std::cout << "FAIL!!!\n";
        std::cout << NORMAL;
        std::cout << a << " + " << b << " = " << result << "\n\n";
        return false;
    }
}

void add_test()
{
    std::cout << YELLOW;
    std::cout << "\n***add tests***" << "\n\n";
    std::cout << NORMAL;

    while(true)
    {
        long long int a = getRandom()%MAX_ADD;
        if(a%4 == 0)
            a *= -1;

        long long int b = getRandom()%MAX_ADD;
        if(b%4 == 0)
            b *= -1;

        if(!add(a, b))
            return;
    }
}

bool sub(long long int a, long long int b)
{
    BigInteger result = BigInteger(a) - BigInteger(b);
    if(result.convert_big_int_to_long_long() == a-b)
    {
        std::cout << GREEN;
        std::cout << "PASS!!!\n";
        std::cout << NORMAL;
        std::cout << a << " - " << b << " = " << result << "\n\n";
        return true;
    }
    else
    {
        std::cout << RED;
        std::cout << "FAIL!!!\n";
        std::cout << NORMAL;
        std::cout << a << " - " << b << " = " << result << "\n\n";
        return false;
    }
}

void sub_test()
{
    std::cout << YELLOW;
    std::cout << "\n***sub tests***" << "\n\n";
    std::cout << NORMAL;

    while(true)
    {
        long long int a = getRandom()%MAX_SUB;
        if(a%4 == 0)
            a *= -1;

        long long int b = getRandom()%MAX_SUB;
        if(b%4 == 0)
            b *= -1;

        if(!sub(a, b))
            return;
    }
}

bool mul(long long int a, long long int b)
{
    BigInteger result = BigInteger(a) * BigInteger(b);
    if(result.convert_big_int_to_long_long() == a*b)
    {
        std::cout << GREEN;
        std::cout << "PASS!!!\n";
        std::cout << NORMAL;
        std::cout << a << " * " << b << " = " << result << "\n\n";
        return true;
    }
    else
    {
        std::cout << RED;
        std::cout << "FAIL!!!\n";
        std::cout << NORMAL;
        std::cout << a << " * " << b << " = " << result << "\n\n";
        return false;
    }
}

void mul_test()
{
    std::cout << YELLOW;
    std::cout << "\n***mul tests***" << "\n\n";
    std::cout << NORMAL;

    while(true)
    {
        long long int a = getRandom()%MAX_MUL;
        if(a%4 == 0)
            a *= -1;

        long long int b = getRandom()%MAX_MUL;
        if(b%4 == 0)
            b *= -1;

        if(!mul(a, b))
            return;
    }
}

bool dev(long long int a, long long int b)
{
    BigInteger result = BigInteger(a) / BigInteger(b);
    if(result.convert_big_int_to_long_long() == a/b)
    {
        std::cout << GREEN;
        std::cout << "PASS!!!\n";
        std::cout << NORMAL;
        std::cout << a << " / " << b << " = " << result << "\n\n";
        return true;
    }
    else
    {
        std::cout << RED;
        std::cout << "FAIL!!!\n";
        std::cout << NORMAL;
        std::cout << a << " / " << b << " = " << result << "\n\n";
        return false;
    }
}

void dev_test()
{
    std::cout << YELLOW;
    std::cout << "\n***mul tests***" << "\n\n";
    std::cout << NORMAL;

    while(true)
    {
        long long int a = getRandom()%MAX_DEV;
        if(a%4 == 0)
            a *= -1;
        if(a == 0)
            a = 1;

        long long int b = getRandom()%MAX_DEV;
        if(b%4 == 0)
            b *= -1;
        if(b == 0)
            b = 1;

        if(!dev(a, b))
            return;
    }
}
int main()
{
    //add_test();
    //sub_test();
    //mul_test();
    dev_test();

    // BigInteger r = BigInteger(67935728716124759) / BigInteger(2);
    // long long int res = r.convert_big_int_to_long_long();
    //  std::cout << (res == 67935728716124759 / 2) << "\n";
    // std::cout << res << "\n";
    // std::cout << 67935728716124759 / 2 << "\n";

    return 0;
}