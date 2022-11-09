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

void convert_string_to_list_of_digit(BigIntList& big_int, std::string const& number)
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

void make_me_right_side(BigInteger& self, std::string const& right_side)
{
	BigInteger big_int(right_side);
	self = big_int;
}

void make_me_right_side(BigInteger& self, long long int const& right_side)
{
	BigInteger big_int(right_side);
	self = big_int;
}

void make_me_right_side(BigInteger& self, const char* right_side)
{
	BigInteger big_int(right_side);
	self = big_int;
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

void check_tail(BigIntIterator& first, BigIntIterator& first_end, BigIntList& result)
{
	while (first != first_end)
	{
		result.push_front(*first);
		first--;
	}
}

bool is_i_am_zero(BigIntList& big_int)
{
	int count = 0;
	auto it = big_int.begin();
	auto end = big_int.end();
	while(it != end)
	{
		count += *it;
		if(count != 0)
			return false;

		it++;
	}

	return true;
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
	}
}

int length_comparison(BigIntList& first, BigIntList& second, Compare& compare)
{
	delete_zeros_on_left(first);
	delete_zeros_on_left(second);

	if(compare((int)first.size(), second.size()))
		return FIRST;

	if(compare(second.size(), (int)first.size()))
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
		return length_comparison(first, second, greater);
	else
		return length_comparison(first, second, lass);
}

bool set_first_and_second(BigIntIterator& first, BigIntIterator& second, BigIntIterator& first_end, BigIntIterator& second_end, BigIntList& self, BigIntList& right_side)
{
	int result = length_comparison(self, right_side, greater);
	if(result == EQUALS)
		return false;
	
	if(is_i_am_zero(self) && is_i_am_zero(right_side))
		return false;

	if(result == FIRST)
	{
		first = impl::init_iterator(self);
		second = impl::init_iterator(right_side);
		first_end = self.end();
		second_end = right_side.end();
	}

	if(result == SECOND)
	{
		first = impl::init_iterator(right_side);
		second = impl::init_iterator(self);
		first_end = right_side.end();
		second_end = self.end();
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

void set_sign(bool& result_sign, bool& self_sign, bool& right_side_sign, BigIntList& self, BigIntList& right_side)
{
	int result = length_comparison(self, right_side, greater);
	if(result == FIRST)
	{
		if(self_sign == NEGATIVE && right_side_sign == NEGATIVE)
			result_sign = NEGATIVE;

		return;
	}

	if(result == SECOND)
	{
		if(self_sign == POSITIVE && right_side_sign == POSITIVE)
			result_sign = NEGATIVE;

		return;
	}
}

void set_sign(bool& result_sign, bool& self_sign, bool& right_side_sign)
{
	if(self_sign != right_side_sign)
		result_sign = NEGATIVE;
	else
		result_sign = POSITIVE;
}

void set_dev_sign(bool& result_sign, bool& self_sign, bool& right_side_sign)
{
	set_sign(result_sign, self_sign, right_side_sign);
	right_side_sign = POSITIVE;
	self_sign = POSITIVE;
}

void set_mod_sign(bool& self_sign, bool& right_side_sign)
{
	self_sign = POSITIVE;
	right_side_sign = POSITIVE;
}

void set_sign_back(bool& self, bool& right_side, bool self_sign, bool right_side_sign)
{
	self = self_sign;
	right_side = right_side_sign;
}

void set_mod_sign_back(bool& self, bool& right_side, bool& result, bool self_sign, bool right_side_sign)
{
	set_sign_back(self, right_side, self_sign, right_side_sign);
	result = self_sign;
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

BigInteger make_sub(BigInteger& self, bool& self_sign, BigInteger& right_side)
{
	impl::flip_sign(self_sign);
	BigInteger result = self - right_side;
	impl::flip_sign(self_sign);
	impl::flip_sign(result.sign());
	return result;
}

BigInteger make_add(BigInteger& self, bool& self_sign, BigInteger& right_side)
{
	impl::flip_sign(self_sign);
	BigInteger result = self + right_side;
	impl::flip_sign(self_sign);
	impl::flip_sign(result.sign());
	return result;
}

bool one_of_them_is_zero(BigIntList& self, BigIntList& right_side)
{
	if(is_i_am_zero(self) || is_i_am_zero(right_side))
		return true;

	return false;
}

bool special_cases(BigIntList& self, bool& self_sign, BigIntList& right_side, bool& right_side_sign, BigInteger& result)
{
	BigIntList zero;
	zero.push_back(0);

	if(length_comparison(zero, right_side, greater) == EQUALS)
		throw std::runtime_error(std::string("ERROR: invalid division by zero!"));

	if(length_comparison(self, right_side, greater) == SECOND)
	{
		result = BigInteger("0");
		return true;
	}

	if(length_comparison(self, right_side, greater) == EQUALS)
	{
		if(self_sign == right_side_sign)
			result = BigInteger("1");
		else
			result = BigInteger("-1");
		return true;
	}
		
	return false;
}

bool special_cases(BigInteger& self, BigInteger& right_side, BigInteger& result)
{
	if(right_side  ==  BigInteger("0"))
		throw std::runtime_error(std::string("ERROR: invalid division by zero!"));

	if(self < right_side)
	{
		result = self;
		return true;
	}

	if(self == right_side)
	{
		result = BigInteger("0");
		return true;
	}

	return false;
}

bool special_cases_pow(bool right_side_sign, BigInteger& result, BigInteger& self, BigInteger& right_side)
{
	if(self == BigInteger("1"))
	{
		result = BigInteger("1");
		return true;
	}

	if(self == BigInteger("-1"))
	{
		result = BigInteger("-1");
		return true;
	}

	if(right_side_sign == NEGATIVE)
	{
		if(self == BigInteger("0"))
			throw std::runtime_error(std::string("ERROR: invalid division by zero!"));
		
		result = BigInteger("0");
		return true;
	}
	
	if(right_side == BigInteger("0"))
	{
		result = BigInteger("1");
		return true;
	}
	
	if(right_side == BigInteger("1"))
	{
		result = self;
		return true;
	}

	return false;
}

bool special_cases(BigInteger& self)
{
	if(self < BigInteger("0"))
		throw std::runtime_error(std::string("ERROR: invalid negative number!"));

	if(self == BigInteger("0") || self == BigInteger("1"))
		return true;
	
	return false;
}

bool divide_temp_self_by_right_side(BigInteger& temp_self, BigInteger& right_side, BigInteger& temp_result, bool first_iteration)
{
	if(right_side > temp_self && first_iteration)
		return false;

	BigInteger counter("0");
	BigInteger temp_right_side;

	while(true)
	{
		temp_right_side = temp_right_side + right_side;
		if(temp_right_side > temp_self)
			break;
		else
			counter = counter + 1;
	}

	temp_result = counter;
	return true;
}

void concatenate(BigIntList& result, BigIntList& temp_result)
{
	for(auto digit : temp_result)
		result.push_back(digit);
}

bool is_i_am_root(BigInteger& root, BigInteger& number, BigInteger& upper, BigInteger& lower)
{
	if((root^BigInteger(2)) > number)
	{
		upper = root;
		return false;
	}

	if((root^BigInteger(2)) < number)
	{
		lower = root;
		return false;
	}

	return true;
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

BigInteger::BigInteger(std::string const& number)
: m_sign(POSITIVE)
, m_big_int()
{
	m_sign = impl::sign(number[0]);
	impl::convert_string_to_list_of_digit(m_big_int, number);
}

BigInteger::BigInteger(std::string const&& number)
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
	impl::make_me_right_side(*this, right_side);
	return *this;
}

BigInteger& BigInteger::operator=(std::string const& right_side)
{
	impl::make_me_right_side(*this, right_side);
	return *this;
}

BigInteger& BigInteger::operator=(std::string const&& right_side)
{
	*this = right_side;
	return *this;
}

BigInteger& BigInteger::operator=(long long int const& right_side)
{
	impl::make_me_right_side(*this, right_side);
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

BigInteger BigInteger::operator+(const char* right_side)
{
	return *this + BigInteger(right_side);
}

BigInteger BigInteger::operator+(long long int right_side)
{
	return *this + BigInteger(right_side);
}

BigInteger BigInteger::operator+(std::string& right_side)
{
	return *this + BigInteger(right_side);
}

BigInteger BigInteger::operator+(std::string&& right_side)
{
	return *this + BigInteger(right_side);
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
	BigInteger self = *this;

	if(!impl::set_first_and_second(first, second, first_end, second_end, self.m_big_int, right_side.m_big_int))
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

BigInteger BigInteger::operator-(const char* right_side)
{
	return *this - BigInteger(right_side);
}

BigInteger BigInteger::operator-(long long int right_side)
{
	return *this - BigInteger(right_side);
}

BigInteger BigInteger::operator-(std::string& right_side)
{
	return *this - BigInteger(right_side);
}

BigInteger BigInteger::operator-(std::string&& right_side)
{
	return *this - BigInteger(right_side);
}

BigInteger BigInteger::operator*(BigInteger& right_side)
{
	if(impl::one_of_them_is_zero(this->m_big_int, right_side.m_big_int))
		return BigInteger("0");

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

	impl::set_sign(result.m_sign, this->m_sign, right_side.m_sign);
	return result;
}

BigInteger BigInteger::operator*(BigInteger&& right_side)
{
	return *this * right_side;
}

BigInteger BigInteger::operator*(const char* right_side)
{
	return *this * BigInteger(right_side);
}

BigInteger BigInteger::operator*(long long int right_side)
{
	return *this * BigInteger(right_side);
}

BigInteger BigInteger::operator*(std::string& right_side)
{
	return *this * BigInteger(right_side);
}

BigInteger BigInteger::operator*(std::string&& right_side)
{
	return *this * BigInteger(right_side);
}

BigInteger BigInteger::operator/(BigInteger& right_side)
{
	BigInteger result;
	if(impl::special_cases(this->m_big_int, this->m_sign, right_side.m_big_int, right_side.m_sign, result))
		return result;

	BigInteger temp_self;
	BigInteger temp_result;
	BigInteger temp_result_mul_right_side;
	auto it = this->m_big_int.begin();
	auto end = this->m_big_int.end();
	bool first_iteration = true;
	bool self_sign = this->m_sign;
	bool right_side_sign = right_side.m_sign;
	impl::set_dev_sign(result.m_sign, this->m_sign, right_side.m_sign);

	while(it != end)
	{
		temp_self.m_big_int.push_back((*it));
		impl::delete_zeros_on_left(temp_self.m_big_int);

		if(impl::divide_temp_self_by_right_side(temp_self, right_side, temp_result, first_iteration))
		{
			first_iteration = false;
			impl::concatenate(result.m_big_int, temp_result.m_big_int);
			temp_result_mul_right_side = temp_result * right_side;
			temp_self = temp_self - temp_result_mul_right_side;
		}

		++it;
	}

	impl::set_sign_back(this->m_sign, right_side.m_sign, self_sign, right_side_sign);
	return result;
}

BigInteger BigInteger::operator/(BigInteger&& right_side)
{
	return *this / right_side;
}

BigInteger BigInteger::operator/(const char* right_side)
{
	return *this / BigInteger(right_side);
}

BigInteger BigInteger::operator/(long long int right_side)
{
	return *this / BigInteger(right_side);
}

BigInteger BigInteger::operator/(std::string& right_side)
{
	return *this / BigInteger(right_side);
}

BigInteger BigInteger::operator/(std::string&& right_side)
{
	return *this / BigInteger(right_side);
}

BigInteger BigInteger::operator%(BigInteger& right_side)
{
	BigInteger result;
	bool self_sign = this->m_sign;
	bool right_side_sign = right_side.m_sign;
	impl::set_mod_sign(this->m_sign, right_side.m_sign);
	if(impl::special_cases(*this, right_side, result))
	{
		impl::set_mod_sign_back(this->m_sign, right_side.m_sign, result.m_sign, self_sign, right_side_sign);
		return result;
	}		

	BigInteger dev = *this/right_side;
	result = (*this) - (dev*right_side);

	impl::set_mod_sign_back(this->m_sign, right_side.m_sign, result.m_sign, self_sign, right_side_sign);
	return result;
}

BigInteger BigInteger::operator%(BigInteger&& right_side)
{
	return *this % right_side;
}

BigInteger BigInteger::operator%(const char* right_side)
{
	return *this % BigInteger(right_side);
}

BigInteger BigInteger::operator%(long long int right_side)
{
	return *this % BigInteger(right_side);
}

BigInteger BigInteger::operator%(std::string& right_side)
{
	return *this % BigInteger(right_side);
}

BigInteger BigInteger::operator%(std::string&& right_side)
{
	return *this % BigInteger(right_side);
}

BigInteger BigInteger::operator^(BigInteger& right_side)
{
	BigInteger result(1);
	if(impl::special_cases_pow(right_side.m_sign, result, *this, right_side))
		return result;

	BigInteger counter("0");
	while(counter < right_side)
	{
		result = result * (*this);
		counter = counter + 1;
	}

	return result;
}

BigInteger BigInteger::operator^(BigInteger&& right_side)
{
	return *this ^ right_side;
}

BigInteger BigInteger::operator^(const char* right_side)
{
	return *this ^ BigInteger(right_side);
}

BigInteger BigInteger::operator^(long long int right_side)
{
	return *this ^ BigInteger(right_side);
}

BigInteger BigInteger::operator^(std::string& right_side)
{
	return *this ^ BigInteger(right_side);
}

BigInteger BigInteger::operator^(std::string&& right_side)
{
	return *this ^ BigInteger(right_side);
}

BigInteger BigInteger::square_root()
{
	if(impl::special_cases(*this))
		return *this;

    BigInteger lower("1");
    BigInteger upper = *this;
	BigInteger root = *this/2;

	while((upper - lower) > "1")
	{
		if(impl::is_i_am_root(root, *this, upper, lower))
			break;

		root = lower + ((upper - lower)/BigInteger(2));
	}

	return root;
}

BigInteger BigInteger::operator++()
{
	*this = *this + 1;
	return *this;
}

BigInteger BigInteger::operator++(int)
{
	BigInteger pre = *this;
	*this = *this + 1;
	return pre;
}

BigInteger BigInteger::operator--()
{
	*this = *this - 1;
	return *this;
}

BigInteger BigInteger::operator--(int)
{
	BigInteger pre = *this;
	*this = *this - 1;
	return pre;
}

BigInteger BigInteger::operator+=(BigInteger& right_side)
{
	return *this = *this + right_side;
}

BigInteger BigInteger::operator+=(BigInteger&& right_side)
{
	return *this += right_side;
}

BigInteger BigInteger::operator+=(const char* right_side)
{
	return *this += BigInteger(right_side);
}

BigInteger BigInteger::operator+=(long long int right_side)
{
	return *this += BigInteger(right_side);
}

BigInteger BigInteger::operator+=(std::string& right_side)
{
	return *this += BigInteger(right_side);
}

BigInteger BigInteger::operator+=(std::string&& right_side)
{
	return *this += BigInteger(right_side);
}

BigInteger BigInteger::operator-=(BigInteger& right_side)
{
	return *this = *this - right_side;
}

BigInteger BigInteger::operator-=(BigInteger&& right_side)
{
	return *this -= right_side;
}

BigInteger BigInteger::operator-=(const char* right_side)
{
	return *this -= BigInteger(right_side);
}

BigInteger BigInteger::operator-=(long long int right_side)
{
	return *this -= BigInteger(right_side);
}

BigInteger BigInteger::operator-=(std::string& right_side)
{
	return *this -= BigInteger(right_side);
}

BigInteger BigInteger::operator-=(std::string&& right_side)
{
	return *this -= BigInteger(right_side);
}

BigInteger BigInteger::operator*=(BigInteger& right_side)
{
	return *this = (*this) * right_side;
}

BigInteger BigInteger::operator*=(BigInteger&& right_side)
{
	return *this *= right_side;
}

BigInteger BigInteger::operator*=(const char* right_side)
{
	return *this *= BigInteger(right_side);
}

BigInteger BigInteger::operator*=(long long int right_side)
{
	return *this *= BigInteger(right_side);
}

BigInteger BigInteger::operator*=(std::string& right_side)
{
	return *this *= BigInteger(right_side);
}

BigInteger BigInteger::operator*=(std::string&& right_side)
{
	return *this *= BigInteger(right_side);
}

BigInteger BigInteger::operator/=(BigInteger& right_side)
{
	return *this = (*this) / right_side;
}

BigInteger BigInteger::operator/=(BigInteger&& right_side)
{
	return *this /= right_side;
}

BigInteger BigInteger::operator/=(const char* right_side)
{
	return *this /= BigInteger(right_side);
}

BigInteger BigInteger::operator/=(long long int right_side)
{
	return *this /= BigInteger(right_side);
}

BigInteger BigInteger::operator/=(std::string& right_side)
{
	return *this /= BigInteger(right_side);
}

BigInteger BigInteger::operator/=(std::string&& right_side)
{
	return *this /= BigInteger(right_side);
}

BigInteger BigInteger::operator%=(BigInteger& right_side)
{
	return *this = (*this) % right_side;
}

BigInteger BigInteger::operator%=(BigInteger&& right_side)
{
	return *this %= right_side;
}

BigInteger BigInteger::operator%=(const char* right_side)
{
	return *this %= BigInteger(right_side);
}

BigInteger BigInteger::operator%=(long long int right_side)
{
	return *this %= BigInteger(right_side);
}

BigInteger BigInteger::operator%=(std::string& right_side)
{
	return *this %= BigInteger(right_side);
}

BigInteger BigInteger::operator%=(std::string&& right_side)
{
	return *this %= BigInteger(right_side);
}

BigInteger BigInteger::operator^=(BigInteger& right_side)
{
	return *this = (*this) ^ right_side;
}

BigInteger BigInteger::operator^=(BigInteger&& right_side)
{
	return *this ^= right_side;
}

BigInteger BigInteger::operator^=(const char* right_side)
{
	return *this ^= BigInteger(right_side);
}

BigInteger BigInteger::operator^=(long long int right_side)
{
	return *this ^= BigInteger(right_side);
}

BigInteger BigInteger::operator^=(std::string& right_side)
{
	return *this ^= BigInteger(right_side);
}

BigInteger BigInteger::operator^=(std::string&& right_side)
{
	return *this ^= BigInteger(right_side);
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

bool BigInteger::operator==(const char* right_side)
{
	return *this == BigInteger(right_side);
}

bool BigInteger::operator==(long long int right_side)
{
	return *this == BigInteger(right_side);
}

bool BigInteger::operator==(std::string& right_side)
{
	return *this == BigInteger(right_side);
}

bool BigInteger::operator==(std::string&& right_side)
{
	return *this == BigInteger(right_side);
}

bool BigInteger::operator!=(BigInteger& right_side)
{
	return !(*this == right_side);
}

bool BigInteger::operator!=(BigInteger&& right_side)
{
	return *this != right_side;
}

bool BigInteger::operator!=(const char* right_side)
{
	return *this != BigInteger(right_side);
}

bool BigInteger::operator!=(long long int right_side)
{
	return *this != BigInteger(right_side);
}

bool BigInteger::operator!=(std::string& right_side)
{
	return *this != BigInteger(right_side);
}

bool BigInteger::operator!=(std::string&& right_side)
{
	return *this != BigInteger(right_side);
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

bool BigInteger::operator<(const char* right_side)
{
	return *this < BigInteger(right_side);
}

bool BigInteger::operator<(long long int right_side)
{
	return *this < BigInteger(right_side);
}

bool BigInteger::operator<(std::string& right_side)
{
	return *this < BigInteger(right_side);
}

bool BigInteger::operator<(std::string&& right_side)
{
	return *this < BigInteger(right_side);
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

bool BigInteger::operator>(const char* right_side)
{
	return *this > BigInteger(right_side);
}

bool BigInteger::operator>(long long int right_side)
{
	return *this > BigInteger(right_side);
}

bool BigInteger::operator>(std::string& right_side)
{
	return *this > BigInteger(right_side);
}

bool BigInteger::operator>(std::string&& right_side)
{
	return *this > BigInteger(right_side);
}

bool BigInteger::operator<=(BigInteger& right_side)
{
	return (*this < right_side || *this == right_side);
}

bool BigInteger::operator<=(BigInteger&& right_side)
{
	return *this <= right_side;
}

bool BigInteger::operator<=(const char* right_side)
{
	return *this <= BigInteger(right_side);
}

bool BigInteger::operator<=(long long int right_side)
{
	return *this <= BigInteger(right_side);
}

bool BigInteger::operator<=(std::string& right_side)
{
	return *this <= BigInteger(right_side);
}

bool BigInteger::operator<=(std::string&& right_side)
{
	return *this <= BigInteger(right_side);
}

bool BigInteger::operator>=(BigInteger& right_side)
{
	return (*this > right_side || *this == right_side);
}

bool BigInteger::operator>=(BigInteger&& right_side)
{
	return *this >= right_side;
}

bool BigInteger::operator>=(const char* right_side)
{
	return *this >= BigInteger(right_side);
}

bool BigInteger::operator>=(long long int right_side)
{
	return *this >= BigInteger(right_side);
}

bool BigInteger::operator>=(std::string& right_side)
{
	return *this >= BigInteger(right_side);
}

bool BigInteger::operator>=(std::string&& right_side)
{
	return *this >= BigInteger(right_side);
}

std::ostream& operator<<(std::ostream& a_os, BigInteger const& big_int)
{
	if(big_int.m_sign == NEGATIVE)
		std::cout << "-";

	for(auto digit : big_int.m_big_int)
		std::cout << digit;

	return a_os;
}

std::string BigInteger::convert_big_int_to_string()
{
	std::string string;
	auto it = this->m_big_int.begin();
	auto end = this->m_big_int.end();

	while (it != end)
	{
		string.push_back(*it + '0');
		it++;
	}

	return string;
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
