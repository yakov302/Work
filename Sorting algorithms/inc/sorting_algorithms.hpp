#pragma once

#include <vector>
#include <functional>

namespace sort
{

template<typename T>
using compareFunction = std::function<bool(T&, T&)>;

template<typename T>
std::function<bool(T&, T&)> naturalLess(
    [](T& a_first, T& a_second)
    {
        return a_first < a_second;
    }
);

template<typename T>
std::function<bool(T&, T&)> naturalEqual(
    [](T& a_first, T& a_second)
    {
        return a_first == a_second;
    }
);

template<typename T>
void bubbleSort(std::vector<T>& a_vector, compareFunction<T>& = naturalLess<T>);

template<typename T>
void shakeSort(std::vector<T>& a_vector, compareFunction<T>& = naturalLess<T>);

template<typename T>
void insertionSort(std::vector<T>& a_vector, compareFunction<T>& = naturalLess<T>);

template<typename T>
void selectionSort(std::vector<T>& a_vector, compareFunction<T>& = naturalLess<T>);

template<typename T>
void shellSort(std::vector<T>& a_vector, compareFunction<T>& = naturalLess<T>);

template<typename T>
void mergeSort(std::vector<T>& a_vector, compareFunction<T>& = naturalLess<T>);

template<typename T>
void quickSort(std::vector<T>& a_vector, compareFunction<T>& = naturalLess<T>);

void countingSort(std::vector<int>& a_vector);

void redixSort(std::vector<int>& a_vector);

template<typename T>
size_t findByLiniarSearch(std::vector<T>& a_vector, T a_elemnt, compareFunction<T>& = naturalEqual<T>);

template<typename T>
size_t findByBinarySearch(std::vector<T>& a_vector, T a_elemnt, compareFunction<T>& = naturalLess<T>, compareFunction<T>& = naturalEqual<T>);


}// sort namespace

#include "./inl/sorting_algorithms.hxx"