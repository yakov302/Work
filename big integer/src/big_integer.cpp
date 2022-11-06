#include "big_integer.hpp"

namespace impl
{

bool sign(long long int number)
{
	if(number < 0)
	 	return NEGATIVE;
	return POSITIVE;
}

bool sign(char sign)
{
	if(sign == '-')
	 	return NEGATIVE;
	return POSITIVE;
}

void convet_int_to_list_of_digit(std::list<int>& big_int, long long int number)
{
	if(number < 0)
		number *= -1;

	while(number > 0)
	{
		int digit = number % 10;
		number = (number - digit) / 10;
		big_int.push_front(digit);
	}
}

void convert_string_to_list_of_digit(std::list<int>& big_int, std::string& number)
{
	const int num_of_digit = number.size();
	for (int i = num_of_digit - 1; i >= 0; i--)
	{
		if (isdigit(number[i]))
			big_int.push_front(number[i] - '0');
	}
}

void convert_chars_to_list_of_digit(std::list<int>& big_int, const char* number)
{
	const int num_of_digit = strlen(number);
	for (int i = num_of_digit - 1; i >= 0; i--)
	{
		if (isdigit(number[i]))
			big_int.push_front(number[i] - '0');
	}
}

void make_my_right_side(BigInteger& my, std::string const& right_side)
{
	BigInteger big_int(right_side);
	my = big_int;
}

void make_my_right_side(BigInteger& my, long long int const& right_side)
{
	BigInteger big_int(right_side);
	my = big_int;
}

void make_my_right_side(BigInteger& my, const char* right_side)
{
	BigInteger big_int(right_side);
	my = big_int;
}

std::_List_iterator<int> init_iterator(std::list<int>& big_int)
{
	auto it = big_int.end();
	it--;
	return it;
}

int enter(int number)
{
	return number % 10;
}

int remainder(int number)
{
	return (number - enter(number)) / 10;
}

void check_tail(std::list<int>& result, std::list<int>& big_int, std::_List_iterator<int>& it, int* carry)
{
	auto it_end = big_int.end();
	while (it != it_end )
	{
		result.push_front(impl::enter(*it + *carry));
		*carry = impl::remainder(*it + *carry);
		it--;
	}
}


}// impl namespace


BigInteger::BigInteger()
: m_sign(POSITIVE)
, m_big_int()
{

}

BigInteger::BigInteger(long long int number)
: m_sign(POSITIVE)
, m_big_int()
{
	m_sign = impl::sign(number);
	impl::convet_int_to_list_of_digit(m_big_int, number);
}

BigInteger::BigInteger(const char* number)
: m_sign(POSITIVE)
, m_big_int()
{
	m_sign = impl::sign(number[0]);
	impl::convert_chars_to_list_of_digit(m_big_int, number);
}

BigInteger::BigInteger(std::string number)
: m_sign(POSITIVE)
, m_big_int()
{
	m_sign = impl::sign(number[0]);
	impl::convert_string_to_list_of_digit(m_big_int, number);
}

BigInteger::BigInteger(BigInteger const& source)
: m_sign(source.m_sign)
, m_big_int()
{
	m_big_int = source.m_big_int;
}

BigInteger::BigInteger(BigInteger const&& source)
: m_sign(source.m_sign)
, m_big_int()
{
	m_big_int = source.m_big_int;
}

BigInteger& BigInteger::operator=(const char* right_side)
{
	impl::make_my_right_side(*this, right_side);
	return *this;
}

BigInteger& BigInteger::operator=(BigInteger const& right_side)
{
	this->m_big_int = right_side.m_big_int;
	this->m_sign = right_side.m_sign;
	return *this;
}

BigInteger& BigInteger::operator=(BigInteger const&& right_side)
{
	this->m_big_int = right_side.m_big_int;
	this->m_sign = right_side.m_sign;
	return *this;
}

BigInteger& BigInteger::operator=(std::string const& right_side)
{
	impl::make_my_right_side(*this, right_side);
	return *this;
}

BigInteger& BigInteger::operator=(std::string const&& right_side)
{
	impl::make_my_right_side(*this, right_side);
	return *this;
}

BigInteger& BigInteger::operator=(long long int const& right_side)
{
	impl::make_my_right_side(*this, right_side);
	return *this;
}

std::ostream& operator<<(std::ostream& a_os, BigInteger const& big_int)
{
	if(big_int.m_sign == NEGATIVE)
		std::cout << "-";

	for(auto digit : big_int.m_big_int)
		std::cout << digit;

	std::cout << std::endl;
	return a_os;
}

BigInteger& BigInteger::operator+(BigInteger& right_side)
{
	// if (first.m_sign != second.m_sign)
	// {
	// 	clean(this->m_list);
	// 	first.flipSign();
	// 	*this = first.sub(second);
	// 	this->flipSign();
	// 	return *this;
	// }

	int carry = 0;
	BigInteger result;
	result.m_sign = this->m_sign;
	auto first_end = this->m_big_int.end();
	auto second_end = right_side.m_big_int.end();
	auto first = impl::init_iterator(this->m_big_int);
	auto second = impl::init_iterator(right_side.m_big_int);

	while (first != first_end && second != second_end)
	{
		result.m_big_int.push_front(impl::enter(*first + *second + carry));
		carry = impl::remainder(*first + *second + carry);
		first--;
		second--;
	}

	impl::check_tail(result.m_big_int, this->m_big_int, first, &carry);
	impl::check_tail(result.m_big_int, right_side.m_big_int, second, &carry);
	if (carry != 0)
		result.m_big_int.push_front(carry);

	*this = result;
	return *this;
}

BigInteger& BigInteger::operator+(BigInteger&& right_side)
{
	BigInteger big_int(right_side);
	*this + big_int;
	return *this;
}

// BigInteger& BigInteger::sub(BigInteger const& a_rhs)
// {
// 	BigInteger first = *this;
// 	BigInteger second = a_rhs;
// 	if ((first.m_sign == -1 && second.m_sign == 1) || (first.m_sign == 1 && second.m_sign == -1))
// 	{
// 		clean(this->m_list);
// 		first.flipSign();
// 		*this = first.add(second);
// 		this->flipSign();
// 		return *this;
// 	}
// 	zeroPadding(first.m_list, second.m_list);
// 	first.m_list = first.flip();
// 	second.m_list = second.flip();
// 	int len = first.m_list.size();
// 	int *First = new int[len];
// 	int *Second = new int[len];
// 	moveToArray(first.m_list, First, second.m_list, Second);
// 	if (first.m_sign == -1 && second.m_sign == -1)
// 	{
// 		this->m_sign = checkBiggest(First, Second, len);
// 		this->flipSign();
// 	}
// 	else
// 	{
// 		this->m_sign = checkBiggest(First, Second, len);
// 	}
// 	LinkedList<int> result;

// 	for (int i = 0; i < len; i++)
// 	{
// 		if (First[i] - Second[i] >= 0)
// 		{
// 			result.add(First[i] - Second[i]);
// 		}
// 		else
// 		{
// 			lend(First, i);
// 			result.add(First[i] - Second[i]);
// 		}
// 	}

// 	delete[] First;
// 	delete[] Second;
// 	DeleteZeros(result);
// 	clean(this->m_list);
// 	this->m_list = result;
// 	return *this;
// }

// BigInteger& BigInteger::mul(BigInteger const& a_rhs)
// {
// 	BigInteger first = *this;
// 	BigInteger second = a_rhs;
// 	zeroPadding(first.m_list, second.m_list);
// 	first.m_list = first.flip();
// 	second.m_list = second.flip();
// 	BigInteger result;
// 	BigInteger temp;
// 	ListIterator<int> itFirst = first.m_list.begin();
// 	ListIterator<int> itSecond;
// 	int carry = 0;
// 	int len = 0;

// 	while (itFirst.notEqual(first.m_list.end()))
// 	{
// 		itSecond = second.m_list.begin();
// 		PutZeros(temp.m_list, len);
// 		while (itSecond.notEqual(second.m_list.end()))
// 		{
// 			temp.m_list.add(enter(itFirst.data() * itSecond.data() + carry));
// 			carry = remainder(itFirst.data() * itSecond.data() + carry);
// 			itSecond.next();
// 		}
// 		if (carry != 0)
// 		{
// 			temp.m_list.add(carry);
// 			carry = 0;
// 		}

// 		result.add(temp);
// 		clean(temp.m_list);
// 		itFirst.next();
// 		len++;
// 	}

// 	DeleteZeros(result.m_list);
// 	clean(this->m_list);
// 	this->m_list = result.m_list;
// 	this->m_sign = checkSigns(first.m_sign, second.m_sign);
// 	return *this;
// }

// const char* BigInteger::toString(String& a_str) const
// {
// 	char* str = new char[(sizeof(char)*m_list.size()) + sizeof('\0')*2];
	
// 	size_t i = 0;
// 	ListIterator<int> it = m_list.begin();
// 	if (m_sign == -1)
// 	{
// 		str[i] = '-';
// 		i++;
// 	}
// 	while (it.notEqual(m_list.end()))
// 	{
// 		str[i] = convert2char(it.data());
// 		i++;
// 		it.next();
// 	}
// 	str[i] = '\0';

// 	a_str.setStr(str);
// 	return a_str.getStr();
// }

// LinkedList<int> BigInteger::flip()const
// {
// 	LinkedList<int> flip;
// 	ListIterator<int> it = m_list.begin();
// 	while (it.notEqual(m_list.end()))
// 	{
// 		flip.add(it.data());
// 		it.next();
// 	}
// 	return flip;
// }

// void BigInteger::flipSign()
// {
// 	m_sign *= (-1);
// }

// LinkedList<int> BigInteger::getList()const
// {
// 	return m_list;
// }

// bool BigInteger::equal(BigInteger const& a_rhs)const
// {
// 	if(this == &a_rhs)
// 	{
// 		return true;
// 	}
// 	if(numOfDigits() != a_rhs.numOfDigits())
// 	{
// 		return false;
// 	}
// 	if(m_sign != a_rhs.m_sign)
// 	{
// 		return false;
// 	}
// 	BigInteger first = *this;
// 	first.sub(a_rhs);
// 	if(first.numOfDigits() == 1 && first.m_list.begin().data() == 0)
// 	{
// 		return true;
// 	}
// 	return false;
// }

// bool BigInteger::notEqual(BigInteger const& a_rhs)const
// {
// 	return equal(a_rhs) == false;
// } 

// bool BigInteger::less(BigInteger const& a_rhs)const
// {
// 	if(m_sign < a_rhs.m_sign)
// 	{
// 		return true;
// 	}
// 	if(m_sign > a_rhs.m_sign)
// 	{
// 		return false;
// 	}
// 	if(m_sign == a_rhs.m_sign)
// 	{
// 		if(numOfDigits() < a_rhs.numOfDigits())
// 		{
// 			return true;
// 		}
// 		if(numOfDigits() > a_rhs.numOfDigits())
// 		{
// 			return false;
// 		}
// 	}

// 	BigInteger first = *this;
// 	first.sub(a_rhs);
// 	if(first.m_sign == -1)
// 	{
// 		return true;
// 	}
// 	return false;
// }

// bool BigInteger::greater(BigInteger const& a_rhs)const
// {
// 	return less(a_rhs) == false;
// }

// bool BigInteger::lessOrEqua (BigInteger const& a_rhs)const
// {
// 	return less(a_rhs) == true || equal(a_rhs) == true;
// }

// bool BigInteger::greaterOrEqual(BigInteger const& a_rhs)const
// {
// 	return greater(a_rhs) == true || equal(a_rhs) == true;
// }

// BigInteger add(BigInteger const& a_lhs, BigInteger const& a_rhs)
// {
// 	BigInteger result = a_lhs;
// 	result.add(a_rhs);
// 	return result;
// }

// void add(BigInteger const& a_lhs, BigInteger const& a_rhs, BigInteger& a_sum)
// {
// 	a_sum.add(a_lhs);
// 	a_sum.add(a_rhs);
// }

// BigInteger sub(BigInteger const& a_lhs, BigInteger const& a_rhs)
// {
// 	BigInteger result = a_lhs;
// 	result.sub(a_rhs);
// 	return result;
// }

// void sub(BigInteger const& a_lhs, BigInteger const& a_rhs, BigInteger& a_sum)
// {
// 	a_sum = a_lhs;
// 	a_sum.sub(a_rhs);
// }

// BigInteger mul(BigInteger const& a_lhs, BigInteger const& a_rhs)
// {
// 	BigInteger result = a_lhs;
// 	result.mul(a_rhs);
// 	return result;
// }

// void mul(BigInteger const& a_lhs, BigInteger const& a_rhs, BigInteger& a_sum)
// {
// 	a_sum = a_lhs;
// 	a_sum.mul(a_rhs);
// }

// bool equal(BigInteger const& a_rhs, BigInteger const& a_lhs)
// {
// 	return 	a_rhs.equal(a_lhs);
// }

// bool notEqual(BigInteger const& a_rhs, BigInteger const& a_lhs)
// {
// 	return 	a_rhs.notEqual(a_lhs);	
// }

// bool less(BigInteger const& a_rhs, BigInteger const& a_lhs)
// {
// 	return 	a_rhs.less(a_lhs);
// }

// bool greater(BigInteger const& a_rhs, BigInteger const& a_lhs)
// {
// 	return 	a_rhs.greater(a_lhs);
// }

// bool lessOrEqua(BigInteger const& a_rhs, BigInteger const& a_lhs)
// {
// 	return 	a_rhs.lessOrEqua(a_lhs);
// }

// bool greaterOrEqual(BigInteger const& a_rhs, BigInteger const& a_lhs)
// {
// 	return 	a_rhs.greaterOrEqual(a_lhs);
// }

// static int giveMeSign(long n)
// {
// 	if (n < 0)
// 	{
// 		return -1;
// 	}
// 	return 1;
// }

// static int convert2digit(char c)
// {
// 	return c - '0';
// }

// static int checkSign(char c)
// {
// 	if (c == '-')
// 	{
// 		return -1;
// 	}
// 	return 1;
// }

// static bool checkIfNumber(char c)
// {
// 	return isdigit(c);
// }

// static void zeroPadding(LinkedList<int>& a_first, LinkedList<int>& a_second)
// {
// 	int len;
// 	if (a_first.size() > a_second.size())
// 	{
// 		len = a_first.size() - a_second.size();
// 		for (int i = 0; i < len; i++)
// 		{
// 			a_second.add(0);
// 		}
// 	}
// 	if (a_first.size() < a_second.size())
// 	{
// 		len = a_second.size() - a_first.size();
// 		for (int i = 0; i < len; i++)
// 		{
// 			a_first.add(0);
// 		}
// 	}
// }

// static int enter(int n)
// {
// 	return n % 10;
// }

// static int remainder(int n)
// {
// 	return (n - enter(n)) / 10;
// }

// static void clean(LinkedList<int>& a_list)
// {
// 	size_t len = a_list.size();
// 	for (size_t i = 0; i < len; i++)
// 	{
// 		a_list.remove();
// 	}
// }

// static int checkSigns(int first, int second)
// {
// 	if ((first == 1) && (second == -1))
// 	{
// 		return -1;
// 	}
// 	if ((first == -1) && (second == 1))
// 	{
// 		return -1;
// 	}

// 	return 1;
// }

// static void swapArr(int* First, int* Second, int a_len)
// {
// 	int *temp = new int[a_len];
// 	for (int i = a_len - 1; i >= 0; i--)
// 	{
// 		temp[i] = First[i];
// 	}
// 	for (int i = a_len - 1; i >= 0; i--)
// 	{
// 		First[i] = Second[i];
// 	}
// 	for (int i = a_len - 1; i >= 0; i--)
// 	{
// 		Second[i] = temp[i];
// 	}
// 	delete[] temp;
// }

// static int checkBiggest(int* First, int* Second, int a_len)
// {
// 	int i = a_len - 1;
// 	if (First[i] > Second[i])
// 	{
// 		return 1;
// 	}
// 	else if (First[i] < Second[i])
// 	{
// 		swapArr(First, Second, a_len);
// 		return -1;
// 	}

// 	for (; i > 0; i--)
// 	{
// 		if (First[i] > Second[i])
// 		{
// 			return 1;
// 		}
// 		else if (First[i] < Second[i])
// 		{
// 			swapArr(First, Second, a_len);
// 			return -1;
// 		}
// 	}

// 	return 0;
// }

// static void moveToArray(LinkedList<int> first, int* First, LinkedList<int> second, int* Second)
// {
// 	ListIterator<int> it = first.begin();
// 	int i = 0;
// 	while (it.notEqual(first.end()))
// 	{
// 		First[i] = it.data();
// 		it.next();
// 		i++;
// 	}

// 	it = second.begin();
// 	i = 0;
// 	while (it.notEqual(second.end()))
// 	{
// 		Second[i] = it.data();
// 		it.next();
// 		i++;
// 	}
// }

// static void lend(int* First, int a_frome)
// {
// 	First[a_frome] += 10;
// 	int i = a_frome + 1;
// 	while (First[i] == 0)
// 	{
// 		First[i] = 9;
// 		i++;
// 	}
// 	First[i] -= 1;
// }

// static void DeleteZeros(LinkedList<int>& a_list)
// {
// 	ListIterator<int> it;
// 	while (true)
// 	{
// 		if (a_list.size() == 1)
// 		{
// 			return;
// 		}
// 		it = a_list.begin();
// 		if (it.data() != 0)
// 		{
// 			return;
// 		}
// 		else
// 		{
// 			a_list.remove();
// 		}
// 	}
// }

// static void PutZeros(LinkedList<int>& a_list, int n)
// {
// 	for (int i = 0; i < n; i++)
// 	{
// 		a_list.add(0);
// 	}
// }

// static char convert2char(int n)
// {
// 	return n + '0';
// }

// size_t BigInteger::numOfDigits()const
// {
// 	return m_list.size();
// }
