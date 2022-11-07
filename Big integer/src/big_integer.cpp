#include "big_integer.hpp"

namespace big_integer
{

Compare lass([](int first, int second){return first < second;});
Compare greater([](int first, int second){return first > second;});

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

void convet_int_to_list_of_digit(BigIntList& big_int, long long int number)
{
	if(number == 0)
	{
		big_int.push_front(0);
		return;
	}

	if(number < 0)
		number *= -1;

	while(number > 0)
	{
		int digit = number % 10;
		number = (number - digit) / 10;
		big_int.push_front(digit);
	}
}

void convert_string_to_list_of_digit(BigIntList& big_int, std::string& number)
{
	const int num_of_digit = number.size();
	for (int i = num_of_digit - 1; i >= 0; i--)
	{
		if (isdigit(number[i]))
			big_int.push_front(number[i] - '0');
	}
}

void convert_chars_to_list_of_digit(BigIntList& big_int, const char* number)
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

BigIntIterator init_iterator(BigIntList& big_int)
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

void check_tail(BigIntList& result, BigIntList& big_int, BigIntIterator& it, int& carry)
{
	auto it_end = big_int.end();
	while (it != it_end )
	{
		result.push_front(impl::enter(*it + carry));
		carry = impl::remainder(*it + carry);
		it--;
	}
}

int who_is_bigger(BigIntList& first, BigIntList& second, Compare& compare)
{
	if(compare((int)first.size(), second.size()))
		return FIRST;

	if(compare(second.size() ,(int)first.size()))
		return SECOND;

	auto it_end  = first.end();
	auto it_first  = first.begin();
	auto it_second = second.begin();
	while(it_first != it_end)
	{
		if(compare(*it_first, *it_second))
			return FIRST;

		if(compare(*it_second, *it_first))
			return SECOND;

		it_first++;
		it_second++;
	}

	return EQUALS;
}

int compare(BigIntList& first, bool& first_sign, BigIntList& second, bool& second_sign)
{
	if(first_sign != second_sign)
	{
		if(first_sign == POSITIVE)
			return FIRST;
		else
			return SECOND;
	}

	if(first_sign == POSITIVE)
		return who_is_bigger(first, second, greater);
	else
		return who_is_bigger(first, second, lass);
}

bool set_first_and_second(BigIntIterator& first, BigIntIterator& second, BigIntIterator& first_end, BigIntIterator& second_end, BigIntList& my, BigIntList& right_side)
{
	int result = who_is_bigger(my, right_side, greater);

	if(result == EQUALS)
		return false;

	if(result == FIRST)
	{
		first = impl::init_iterator(my);
		second = impl::init_iterator(right_side);
		first_end = my.end();
		second_end = right_side.end();
	}

	if(result == SECOND)
	{
		first = impl::init_iterator(right_side);
		second = impl::init_iterator(my);
		first_end = right_side.end();
		second_end = my.end();
	}

	return true;
}

void lend(BigIntIterator first, BigIntIterator& second)
{
	if (*first - *second >= 0)
		return;

	*first += 10;
	first--;

	while(*first == 0)
	{
		*first = 9;
		first--;
	}

	*first -= 1;
}

void check_tail(BigIntIterator& first, BigIntIterator& first_end, BigIntList& result)
{
	while (first != first_end)
	{
		result.push_front(*first);
		first--;
	}
}

void set_sign(bool& result_sign, bool& my_sign, bool& right_side_sign, BigIntList& my, BigIntList& right_side)
{
	int result = who_is_bigger(my, right_side, greater);
	if(result == FIRST)
	{
		if(my_sign == NEGATIVE && right_side_sign == NEGATIVE)
			result_sign = NEGATIVE;

		return;
	}

	if(result == SECOND)
	{
		if(my_sign == POSITIVE && right_side_sign == POSITIVE)
			result_sign = NEGATIVE;

		return;
	}
}

void set_sign(bool& result_sign, bool& my_sign, bool& right_side_sign)
{
	if(my_sign != right_side_sign)
		result_sign = NEGATIVE;
	else
		result_sign = POSITIVE;
}

void delete_zeros_on_left(BigIntList& result)
{
	auto it = result.begin();
	auto end = result.end();
	while(it != end)
	{
		if(*it == 0)
			it = result.erase(it);
		else
			break;

		it++;
	}
}

void flip_sign(bool& big_int_sign)
{
	if(big_int_sign == NEGATIVE)
		big_int_sign = POSITIVE;
	else
		big_int_sign = NEGATIVE;
}

void zeros_padding(BigIntList& big_int, int padding_index)
{
	for(int i = 0; i < padding_index; ++i)
		big_int.push_front(0);
}

bool all_digits_are_zero(BigIntList& big_int)
{
	auto it = big_int.begin();
	auto end = big_int.end();
	while(it != end)
	{
		if(*it != 0)
			return false;
		it++;
	}
	return true;
}

void settle_zero_result_case(BigIntList& result, bool& sign)
{
	if(result.empty() || all_digits_are_zero(result))
	{
		result.clear();
		result.push_front(0);
		sign= POSITIVE;
	}
}

void close_mul_iteration(BigInteger& temp, BigIntList& temp_list, BigInteger& result, BigIntIterator& second, int& carry, int& padding_index)
{
	if (carry != 0)
	{
		temp_list.push_front(carry);
		carry = 0;
	}

	result = result + temp;
	temp_list.clear();
	padding_index += 1;
	second--;
}

BigInteger make_sub(BigInteger& my, bool& my_sign, BigInteger& right_side)
{
	impl::flip_sign(my_sign);
	BigInteger result = my - right_side;
	impl::flip_sign(result.sign());
	return result;
}

BigInteger make_add(BigInteger& my, bool& my_sign, BigInteger& right_side)
{
	impl::flip_sign(my_sign);
	BigInteger result = my + right_side;
	impl::flip_sign(result.sign());
	return result;
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

BigInteger& BigInteger::operator=(BigInteger const& right_side)
{
	this->m_big_int = right_side.m_big_int;
	this->m_sign = right_side.m_sign;
	return *this;
}

BigInteger& BigInteger::operator=(BigInteger const&& right_side)
{
	*this = right_side;
	return *this;
}

BigInteger& BigInteger::operator=(const char* right_side)
{
	impl::make_my_right_side(*this, right_side);
	return *this;
}

BigInteger& BigInteger::operator=(std::string const& right_side)
{
	impl::make_my_right_side(*this, right_side);
	return *this;
}

BigInteger& BigInteger::operator=(std::string const&& right_side)
{
	*this = right_side;
	return *this;
}

BigInteger& BigInteger::operator=(long long int const& right_side)
{
	impl::make_my_right_side(*this, right_side);
	return *this;
}

BigInteger BigInteger::operator+(BigInteger& right_side)
{
	if(this->m_sign != right_side.m_sign)
		return impl::make_sub(*this, this->m_sign, right_side);

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

	impl::check_tail(result.m_big_int, this->m_big_int, first, carry);
	impl::check_tail(result.m_big_int, right_side.m_big_int, second, carry);
	if (carry != 0)
		result.m_big_int.push_front(carry);
	return result;
}

BigInteger BigInteger::operator+(BigInteger&& right_side)
{
	return *this + right_side;
}

BigInteger BigInteger::operator-(BigInteger& right_side)
{
	if(this->m_sign != right_side.m_sign)
		return impl::make_add(*this, this->m_sign, right_side);
	
	BigInteger result;
	BigIntIterator first;
	BigIntIterator second;
	BigIntIterator first_end;
	BigIntIterator second_end;

	if(!impl::set_first_and_second(first, second, first_end, second_end, this->m_big_int, right_side.m_big_int))
		return BigInteger("0");

	while (first != first_end && second != second_end)
	{
		impl::lend(first, second);
		result.m_big_int.push_front(*first - *second);
		first--;
		second--;
	}

	impl::check_tail(first, first_end, result.m_big_int);
	impl::set_sign(result.m_sign, this->m_sign, right_side.m_sign, this->m_big_int, right_side.m_big_int);
	impl::delete_zeros_on_left(result.m_big_int);
	return result;
}

BigInteger BigInteger::operator-(BigInteger&& right_side)
{
	return *this - right_side;
}

BigInteger BigInteger::operator*(BigInteger& right_side)
{
	int carry = 0;
	int padding_index = 0;
	BigInteger temp;
	BigInteger result("0");
	auto first_end = this->m_big_int.end();
	auto second_end = right_side.m_big_int.end();
	auto second = impl::init_iterator(right_side.m_big_int);

	while (second != second_end)
	{
		impl::zeros_padding(temp.m_big_int, padding_index);
		auto first = impl::init_iterator(this->m_big_int);

		while(first != first_end)
		{
			temp.m_big_int.push_front(impl::enter((*second) * (*first) + carry));
			carry = impl::remainder((*second) * (*first) + carry);
			first--;
		}

		impl::close_mul_iteration(temp, temp.m_big_int, result, second, carry, padding_index);
	}

	impl::delete_zeros_on_left(result.m_big_int);
	impl::set_sign(result.m_sign, this->m_sign, right_side.m_sign);
	impl::settle_zero_result_case(result.m_big_int, result.m_sign);
	return result;
}

BigInteger BigInteger::operator*(BigInteger&& right_side)
{
	return *this * right_side;
}

bool BigInteger::operator==(BigInteger& right_side)
{
	if(impl::compare(this->m_big_int, this->m_sign, right_side.m_big_int, right_side.m_sign) != EQUALS)
		return false;

	return true;
}

bool BigInteger::operator==(BigInteger&& right_side)
{
	return *this == right_side;
}

bool BigInteger::operator!=(BigInteger& right_side)
{
	return !(*this == right_side);
}

bool BigInteger::operator!=(BigInteger&& right_side)
{
	return !(*this == right_side);
}

bool BigInteger::operator<(BigInteger& right_side)
{
	if(impl::compare(this->m_big_int, this->m_sign, right_side.m_big_int, right_side.m_sign) != SECOND)
		return false;

	return true;
}

bool BigInteger::operator<(BigInteger&& right_side)
{
	return *this < right_side;
}

bool BigInteger::operator>(BigInteger& right_side)
{
	if(impl::compare(this->m_big_int, this->m_sign, right_side.m_big_int, right_side.m_sign) != FIRST)
		return false;

	return true;
}

bool BigInteger::operator>(BigInteger&& right_side)
{
	return *this > right_side;
}

bool BigInteger::operator<=(BigInteger& right_side)
{
	return(*this < right_side || *this == right_side);
}

bool BigInteger::operator<=(BigInteger&& right_side)
{
	return(*this < right_side || *this == right_side);
}

bool BigInteger::operator>=(BigInteger& right_side)
{
	return(*this > right_side || *this == right_side);
}

bool BigInteger::operator>=(BigInteger&& right_side)
{
	return(*this > right_side || *this == right_side);
}

std::ostream& operator<<(std::ostream& a_os, BigInteger const& big_int)
{
	if(big_int.m_sign == NEGATIVE)
		std::cout << "-";

	for(auto digit : big_int.m_big_int)
		std::cout << digit;

	return a_os;
}

long long int BigInteger::convert_big_int_to_long_long()
{
	int pos = 0;
	long long int number = 0; 
	auto end = this->m_big_int.end();
	auto it = impl::init_iterator(this->m_big_int);
	
	while(it != end)
	{
		number += (*it)*(pow(10,pos));
		pos++;
		it--;
	}

	if(this->m_sign == NEGATIVE)
		number*=-1;
	return number;
}

bool& BigInteger::sign()
{
	return this->m_sign;
}

size_t BigInteger::num_of_digits()const
{
	return this->m_big_int.size();
}


} //big_integer namespace