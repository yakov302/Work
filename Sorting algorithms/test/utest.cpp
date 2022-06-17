#include "mu_test.h"
#include "time.hpp"
#include "sorting_algorithms.hpp"

using namespace sort;

const size_t N = 10000;

void fillRandomInts(std::vector<int>& a_vector, const size_t& a_size)
{
	for(size_t i = 0; i < a_size; ++i)
	{
		a_vector.emplace_back(rand()%a_size);
	}
}

bool validate(std::vector<int>& a_vector, const size_t& a_size)
{
	for(size_t i = 1; i < a_size; ++i)
	{
		if(a_vector[i-1] > a_vector[i])
			return false;
	}
	return true;
}

BEGIN_TEST(bubble)

	std::vector<int> vector;
	vector.reserve(N);
	fillRandomInts(vector, N);

	bubbleSort(vector);
	ASSERT_EQUAL(validate(vector, N), true);
	
END_TEST

BEGIN_TEST(shake)

	std::vector<int> vector;
	vector.reserve(N);
	fillRandomInts(vector, N);

	shakeSort(vector);
	ASSERT_EQUAL(validate(vector, N), true);

END_TEST

BEGIN_TEST(insertion)

	std::vector<int> vector;
	vector.reserve(N);
	fillRandomInts(vector, N);

	insertionSort(vector);
	ASSERT_EQUAL(validate(vector, N), true);

END_TEST

BEGIN_TEST(selection)

	std::vector<int> vector;
	vector.reserve(N);
	fillRandomInts(vector, N);

	selectionSort(vector);
	ASSERT_EQUAL(validate(vector, N), true);

END_TEST

BEGIN_TEST(shell)

	std::vector<int> vector;
	vector.reserve(N);
	fillRandomInts(vector, N);

	shellSort(vector);
	ASSERT_EQUAL(validate(vector, N), true);

END_TEST

BEGIN_TEST(merge)

	std::vector<int> vector;
	vector.reserve(N);
	fillRandomInts(vector, N);

	mergeSort(vector);
	ASSERT_EQUAL(validate(vector, N), true);

END_TEST

BEGIN_TEST(quick)

	std::vector<int> vector;
	vector.reserve(N);
	fillRandomInts(vector, N);

	quickSort(vector);
	ASSERT_EQUAL(validate(vector, N), true);

END_TEST

BEGIN_TEST(counting)

	std::vector<int> vector;
	vector.reserve(N);
	fillRandomInts(vector, N);

	countingSort(vector);
	ASSERT_EQUAL(validate(vector, N), true);

END_TEST

BEGIN_TEST(redix)

	std::vector<int> vector;
	vector.reserve(N);
	fillRandomInts(vector, N);

	redixSort(vector);
	ASSERT_EQUAL(validate(vector, N), true);

END_TEST

BEGIN_TEST(sort_comparison)

	std::cout << "Running time (in seconds) on " << N << " (int) elements" << std::endl;

	std::vector<int> vector;
	vector.reserve(N);
	fillRandomInts(vector, N);

	std::vector<int> bubble = vector;
	std::cout << "bubble:    ";
	{
		Time time;
		bubbleSort(bubble);
	}
	ASSERT_EQUAL(validate(bubble, N), true);

	std::vector<int> selection = vector;
	std::cout << "selection: ";
	{
		Time time;
		selectionSort(selection);
	}
	ASSERT_EQUAL(validate(selection, N), true);

	std::vector<int> shake = vector;
	std::cout << "shake:     ";
	{
		Time time;
		shakeSort(shake);
	}
	ASSERT_EQUAL(validate(shake, N), true);

	std::vector<int> insertion = vector;
	std::cout << "insertion: ";
	{
		Time time;
		insertionSort(insertion);
	}
	ASSERT_EQUAL(validate(insertion, N), true);

	std::vector<int> shell = vector;
	std::cout << "shell:     ";
	{
		Time time;
		shellSort(shell);
	}
	ASSERT_EQUAL(validate(shell, N), true);

	std::vector<int> quick = vector;
	std::cout << "quick:     ";
	{
		Time time;
		quickSort(quick);
	}
	ASSERT_EQUAL(validate(quick, N), true);

	std::vector<int> merge = vector;
	std::cout << "merge:     ";
	{
		Time time;
		mergeSort(merge);
	}
	ASSERT_EQUAL(validate(merge, N), true);

	std::vector<int> redix = vector;
	std::cout << "redix:     ";
	{
		Time time;
		redixSort(redix);
	}
	ASSERT_EQUAL(validate(redix, N), true);

	std::vector<int> counting = vector;
	std::cout << "counting:  ";
	{
		Time time;
		countingSort(counting);
	}
	ASSERT_EQUAL(validate(counting, N), true);

END_TEST

BEGIN_TEST(search_comparison)

	std::vector<int> vector;
	vector.reserve(N);
	fillRandomInts(vector, N);

	std::cout << "Liniar search, not sortes array, existsting element:     ";
	{
		int index = rand()%N;
		int element = vector[index];
		Time();
		ASSERT_EQUAL(vector[findByLiniarSearch(vector, element)], element);
	}

	std::cout << "Liniar search, not sortes array, not existsting element: ";
	{
		int falseElement = N + 1;
		Time();
		ASSERT_EQUAL(findByLiniarSearch(vector, falseElement), N);
	}

	quickSort(vector);

	std::cout << "Binary search, sortes array, existsting element:         ";
	{
		int index = rand()%N;
		int element = vector[index];
		Time();
		ASSERT_EQUAL(vector[findByBinarySearch(vector, element)], element);
	}

	std::cout << "Binary search, sortes array, not existsting element:     ";
	{
		int falseElement = N + 1;
		Time();
		ASSERT_EQUAL(findByBinarySearch(vector, falseElement), N);
	}

END_TEST

BEGIN_SUITE(TEST)

	//TEST(bubble)
	// TEST(selection)
	// TEST(shake)
	// TEST(insertion)
	// TEST(shell)
	// TEST(merge)
	// TEST(quick)
	//TEST(counting)
	//TEST(redix)
	TEST(sort_comparison)
	TEST(search_comparison)
	
END_SUITE
