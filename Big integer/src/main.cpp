#include "big_integer.hpp"

#define YELLOW "\x1B[33m"
#define NORMAL "\x1B[0m"
#define GREEN "\x1B[32m"
#define RED "\x1B[91m"

using namespace big_integer;

void add(long long int a, long long int b)
{
    BigInteger result = BigInteger(a) + BigInteger(b);
    if(result.convert_big_int_to_long_long() == a+b)
    {
        std::cout << GREEN;
        std::cout << "PASS!!!\n";
        std::cout << NORMAL;
        std::cout << a << " + " << b << " = " << result << "\n\n";
    }
    else
    {
        std::cout << RED;
        std::cout << "FAIL!!!\n";
        std::cout << NORMAL;
        std::cout << a << " + " << b << " = " << result << "\n\n";
    }
}

void sub(long long int a, long long int b)
{
    BigInteger result = BigInteger(a) - BigInteger(b);
    if(result.convert_big_int_to_long_long() == a-b)
    {
        std::cout << GREEN;
        std::cout << "PASS!!!\n";
        std::cout << NORMAL;
        std::cout << a << " - " << b << " = " << result << "\n\n";
    }
    else
    {
        std::cout << RED;
        std::cout << "FAIL!!!\n";
        std::cout << NORMAL;
        std::cout << a << " - " << b << " = " << result << "\n\n";
    }
}

void mul(long long int a, long long int b)
{
    BigInteger result = BigInteger(a) * BigInteger(b);
    if(result.convert_big_int_to_long_long() == a*b)
    {
        std::cout << GREEN;
        std::cout << "PASS!!!\n";
        std::cout << NORMAL;
        std::cout << a << " * " << b << " = " << result << "\n\n";
    }
    else
    {
        std::cout << RED;
        std::cout << "FAIL!!!\n";
        std::cout << NORMAL;
        std::cout << a << " * " << b << " = " << result << "\n\n";
    }
}

int main()
{
    std::cout << YELLOW;
    std::cout << "\n***add tests***" << "\n\n";
    std::cout << NORMAL;

    add(5496861654, 5664);
    add(789, 849849684989);
    add(549686545641654, 6548568686465165);
    add(564, 56);
    add(5676684, 0);
    add(0, 6546546);

    add(-549686498, -8749);
    add(-468, -96849/8498);
    add(-98746546846868, -6519898498);
    add(-29, -189);
    add(-48989, -0);
    add(-0, -549898);

    add(-654549898, 4989);
    add(6546546566, -6546);
    add(-489, 685498198198498);
    add(189, -79849898989898);
    add(-49898984984988, 56651658498988);
    add(649898498489, -5646854685485);
    add(-486, 18);
    add(189, -65);
    add(-5465546, 0);
    add(97898498, -0);
    add(-0, 9684989849);
    add(0, -84684989);
    add(0, 0);

    std::cout << YELLOW;
    std::cout << "\n***sub tests***" << "\n\n";
    std::cout << NORMAL;

    sub(5496861654, 5664);
    sub(789, 849849684989);
    sub(549686545641654, 6548568686465165);
    sub(564, 56);
    sub(5676684, 0);
    sub(0, 6546546);

    sub(-549686498, -8749);
    sub(-468, -96849/8498);
    sub(-98746546846868, -6519898498);
    sub(-29, -189);
    sub(-48989, -0);
    sub(-0, -549898);

    sub(-654549898, 4989);
    sub(6546546566, -6546);
    sub(-489, 685498198198498);
    sub(189, -79849898989898);
    sub(-49898984984988, 56651658498988);
    sub(649898498489, -5646854685485);
    sub(-486, 18);
    sub(189, -65);
    sub(-5465546, 0);
    sub(97898498, -0);
    sub(-0, 9684989849);
    sub(0, -84684989);
    sub(50, 50);
    sub(-50, -50);


    std::cout << YELLOW;
    std::cout << "\n***mul tests***" << "\n\n";
    std::cout << NORMAL;

    mul(549686654, 5664);
    mul(789, 849844989);
    mul(54941654, 6548555);
    mul(564, 56);
    mul(5676684, 0);
    mul(0, 6546546);

    mul(-549686498, -8749);
    mul(-468, -96849/8498);
    mul(-9876668, -651988);
    mul(-29, -189);
    mul(-48989, -0);
    mul(-0, -549898);

    mul(-654549898, 4989);
    mul(6546546566, -6546);
    mul(-489, 68549198498);
    mul(189, -79849889898);
    mul(-4989988, 568988);
    mul(6498889, -585485);
    mul(-486, 18);
    mul(189, -65);
    mul(-5465546, 0);
    mul(97898498, -0);
    mul(-0, 9684989849);
    mul(0, -84684989);

    BigInteger x(50);
    x = int(870);
    std::cout << x << "\n";

    return 0;
}