
namespace sort
{

namespace impl
{

bool even(size_t& a_number)
{
    return a_number%2 == 0;
}

template<typename T>
void swap(T& a_first, T& a_second)
{
    T temp = a_first;
    a_first = a_second;
    a_second = temp;
}

template<typename T>
bool bubbleIteration(std::vector<T>& a_vector, size_t const& a_size, size_t& a_i, compareFunction<T>& a_compare)
{
    bool status = false;
    for(size_t i = 1; i < a_size - a_i; ++i)
    {
        if(a_compare(a_vector[i], a_vector[i-1]))
        {
            swap(a_vector[i], a_vector[i-1]);
            status = true;
        }
    }
    return status;
}

template<typename T>
bool shakeStartToEnd(std::vector<T>& a_vector, size_t& a_first, size_t& a_last,  compareFunction<T>& a_compare)
{
    bool status = false;
    for(size_t i = a_first + 1; i <= a_last; ++i)
    {
        if(a_compare(a_vector[i], a_vector[i-1]))
        {
            swap(a_vector[i], a_vector[i-1]);
            status = true;
        }
    }
    --a_last;
    return status;
}

template<typename T>
bool shakeEndToStart(std::vector<T>& a_vector,size_t& a_lest, size_t& a_first, compareFunction<T>& a_compare)
{
    bool status = false;
    for(size_t i = a_lest; i > a_first; --i)
    {
        if(a_compare(a_vector[i], a_vector[i-1]))
        {
            swap(a_vector[i], a_vector[i-1]);
            status = true;
        }
    }
    ++a_first;
    return status;
}

template<typename T>
void insertionIteration(std::vector<T>& a_vector,size_t& a_i, compareFunction<T>& a_compare)
{
    for(size_t i = a_i; i > 0; --i)
    {
        if(!a_compare(a_vector[i], a_vector[i-1]))
            break;
    
        swap(a_vector[i], a_vector[i-1]);
    }
}

template<typename T>
void findMin(std::vector<T>& a_vector,size_t& a_i, const size_t& a_size, size_t& a_min, compareFunction<T>& a_compare)
{
    for(size_t i = a_i + 1; i < a_size; ++i)
    {
        if(a_compare(a_vector[i], a_vector[a_min]))
            a_min = i;
    }
}

template<typename T>
void selectionIteration(std::vector<T>& a_vector, size_t& a_i, const size_t& a_size, compareFunction<T>& a_compare)
{
    size_t min = a_i;
    findMin(a_vector, a_i, a_size, min, a_compare);

    if(min != a_i)
        swap(a_vector[min], a_vector[a_i]);
}

template<typename T>
void shellIteration(std::vector<T>& a_vector, size_t& a_i, size_t& a_gap, compareFunction<T>&a_compare)
{
    for(size_t i = a_i; i >= a_gap; i -= a_gap)
    {
        if(!a_compare(a_vector[i], a_vector[i - a_gap]))
            break;

        swap(a_vector[i], a_vector[i - a_gap]);
    }
}

template<typename T>
void AddTails(std::vector<T>& a_vector, T*& a_merge, size_t& a_first, size_t& a_second, size_t& a_mid, size_t& a_last, size_t& a_i)
{
    while(a_first <= a_mid)
    {
        a_merge[a_i] = a_vector[a_first];
        ++a_first;
        ++a_i;
    }

    while(a_second <= a_last)
    {
        a_merge[a_i] = a_vector[a_second];
        ++a_second;
        ++a_i;
    }
}

template<typename T>
void CopyMergeToOriginal(std::vector<T>& a_vector, T*& a_merge, size_t& a_first, size_t& a_last)
{
    for(size_t i = a_first; i <= a_last; ++i)
    {
        a_vector[i] = a_merge[i];
    }
}

template<typename T>
void merge(std::vector<T>& a_vector, T*& a_merge, size_t& a_first, size_t& a_mid, size_t& a_last, compareFunction<T>& a_compare)
{
    size_t first = a_first;
    size_t second = a_mid + 1;
    size_t i = a_first;

    for(; first <= a_mid && second <= a_last; ++i)
    {
        if(a_compare(a_vector[first], a_vector[second]))
        {
            a_merge[i] = a_vector[first];
            ++first;
        }
        else
        {
           a_merge[i] = a_vector[second];
            ++second;
        }
    }

    AddTails(a_vector, a_merge, first, second, a_mid, a_last, i);
    CopyMergeToOriginal(a_vector, a_merge, a_first, a_last);
}

template<typename T>
void mergeSortRec(std::vector<T>& a_vector, T*& a_merge, size_t a_first, size_t a_last, compareFunction<T>& a_compare)
{
    if(a_last <= a_first)
        return;

    size_t mid = (a_first + a_last)/2;
    mergeSortRec(a_vector, a_merge, a_first, mid, a_compare);
    mergeSortRec(a_vector, a_merge, mid + 1, a_last, a_compare);
    merge(a_vector, a_merge, a_first, mid, a_last, a_compare);
}

template<typename T>
T& findPivot(std::vector<T>& a_vector, size_t& a_first, size_t& a_last, compareFunction<T>& a_compare)
{
    return a_vector[a_first];
}

template<typename T>
void findBiggerOnLeft(std::vector<T>& a_vector, T& a_pivot, size_t& a_first, const size_t& a_last, compareFunction<T>& a_compare)
{
    while(a_first <= a_last)
    {
        if(a_compare(a_pivot, a_vector[a_first]))
            break;
        
        ++a_first;
    }
}

template<typename T>	
void findSmallerOnRight(std::vector<T>& a_vector, T& a_pivot, const size_t& a_first, size_t& a_last, compareFunction<T>& a_compare)
{
    while(a_last > a_first)
    {
        if(a_compare(a_vector[a_last], a_pivot))
            break;

        --a_last;
    }
}

template<typename T>
size_t partition(std::vector<T>& a_vector, const size_t& a_first, const size_t& a_last, T& a_pivot, compareFunction<T>& a_compare)
{
    size_t first = a_first + 1;
    size_t last = a_last;

    while(first <= last)
	{        
		findBiggerOnLeft( a_vector,  a_pivot, first, a_last, a_compare);	
		findSmallerOnRight(a_vector, a_pivot, a_first, last, a_compare);
        
        if(first <= last)
            swap(a_vector[first], a_vector[last]);
	}

	swap(a_pivot, a_vector[last]);
	return last;
}

template<typename T>
void quickSortRec(std::vector<T>& a_vector, size_t a_first, size_t a_last, compareFunction<T>& a_compare)
{
    if(a_first >= a_last)
        return;

    T& pivot = findPivot(a_vector, a_first, a_last, a_compare);
    size_t pivotInsex = partition(a_vector, a_first,  a_last, pivot, a_compare);

    if(pivotInsex  > 1)
        quickSortRec(a_vector, a_first, pivotInsex - 1, a_compare);
    quickSortRec(a_vector, pivotInsex + 1, a_last, a_compare);
}

void findMax(std::vector<int>& a_vector, int& a_max, int const& a_size)
{
    a_max = a_vector[0];
    for(int i = 1; i < a_size; ++i)
    {
        if(a_vector[i] > a_max)
            a_max = a_vector[i];
    }
}

void findMin(std::vector<int>& a_vector, int& a_min, int const& a_size)
{
    a_min = a_vector[0];
    for(int i = 1; i < a_size; ++i)
    {
        if(a_vector[i] < a_min)
            a_min = a_vector[i];
    }
}

void calculateFrequency(std::vector<int>& a_vector, int*& frequency, int& a_gap, const int& a_size)
{
    for(int i = 0; i < a_size; ++i)
    {     
        frequency[a_vector[i] - a_gap] += 1;
    }
}

void calculateCumulativeFrequency(int*& frequency, const int& a_size)
{
    for(int i = 1; i <= a_size; ++i)
    {
        frequency[i] += frequency[i - 1];
    }
}

void makeSoreArray(std::vector<int>& a_vector, int*& sort, int*& frequency, int& a_gap, const int& a_size)
{
    for(int i = a_size - 1; i >= 0; --i)
    {
       sort[frequency[a_vector[i] - a_gap] -1] = a_vector[i];
       frequency[a_vector[i] - a_gap] -= 1;
    }
}

void copySoreArrayToOriginal(std::vector<int>& a_vector, int*& a_sort, const int& a_size)
{
    for(int i = 0; i < a_size; ++i)
    {
        a_vector[i] = a_sort[i];
    }
}

void mallocFrequency(int*& a_frequency, int& a_min, int& a_max)
{
    if(a_min < 0)
    {
        a_frequency = new int[a_max - a_min];
    }
    else
    {
        a_frequency = new int[a_max];
        a_min = 0;
    }
}

int numberLength(int a_number)
{
    int count = 0;
    while(a_number != 0)
    {
        a_number /= 10;
        ++count;
    }
    return count;
}

int findMaxNumberLength(std::vector<int>& a_vector, const size_t& a_size)
{
    int max = 0;
    for(size_t i = 0; i < a_size; ++i)
    {
        if(numberLength(a_vector[i]) > max)
            max = numberLength(a_vector[i]);
    }
    return max;
}

int giveDigit(int a_number, int& position)
{
    int count = 0;
    int sign = 1;

    if(a_number < 0)
        sign = -1;

    while(a_number != 0 && count < position)
    {
        a_number /= 10;
        ++count;
    }

    if(a_number == 0)
        return (a_number%10)*sign;

    return a_number%10;
}

void calculateDigitFrequency(std::vector<int>& a_vector, int& a_digitPosition, int*& a_frequency, const size_t& a_size)
{
    for(size_t i = 0; i < a_size; ++i)
    {    
        int digit = giveDigit(a_vector[i], a_digitPosition);
        a_frequency[digit + 9] += 1;
    }
}

void zeroArray(int*& a_array, const int& arraySize)
{
    memset(a_array, 0, arraySize*sizeof(int));
}

void makeSoreArrayByDigit(std::vector<int>& a_vector, int*& sort, int*& frequency, int& a_digitPosition, const int& a_size)
{
    for(int i = a_size - 1; i >= 0; --i)
    {
        int digit = giveDigit(a_vector[i], a_digitPosition);
        sort[frequency[digit + 9] -1] = a_vector[i];
        frequency[digit + 9] -= 1;
    }
}


} //impl namespace

template<typename T>
void bubbleSort(std::vector<T>& a_vector, compareFunction<T>& a_compare)
{
    size_t const size = a_vector.size();
    for(size_t i = 0 ; i < size; ++i)
    {
        if(!impl::bubbleIteration(a_vector, size, i, a_compare))
            break;
    }
}

template<typename T>
void shakeSort(std::vector<T>& a_vector, compareFunction<T>& a_compare)
{
    size_t const size = a_vector.size();
    size_t first = 0;
    size_t lest = size - 1;

    for(size_t i = 0 ; i < size; ++i)
    {
        if(impl::even(i))
            if(!impl::shakeStartToEnd(a_vector, first, lest, a_compare))
                break;

        if(!impl::even(i))
            if(!impl::shakeEndToStart(a_vector, lest, first, a_compare))
                break;
    }
}

template<typename T>
void insertionSort(std::vector<T>& a_vector, compareFunction<T>& a_compare)
{
    size_t const size = a_vector.size();
    for(size_t i = 1 ; i < size; ++i)
    {
        impl::insertionIteration(a_vector, i, a_compare);
    }
}

template<typename T>
void selectionSort(std::vector<T>& a_vector, compareFunction<T>& a_compare)
{
    size_t const size = a_vector.size();
    for(size_t i = 0 ; i < size -1; ++i)
    {
        impl::selectionIteration(a_vector, i, size, a_compare);
    }
}

template<typename T>
void shellSort(std::vector<T>& a_vector, compareFunction<T>& a_compare)
{
    size_t const size = a_vector.size();
    for(size_t gap = size/2; gap > 0; gap/=2)
    {
        for(size_t i = gap; i < size; ++i)
        {
            impl::shellIteration(a_vector, i, gap, a_compare);
        }
    }
}

template<typename T>
void mergeSort(std::vector<T>& a_vector, compareFunction<T>& a_compare)
{
    size_t const size = a_vector.size();
    T* merge = new T[size];
    impl::mergeSortRec(a_vector, merge, 0, size - 1, a_compare);
    delete[] merge;
}

template<typename T>
void quickSort(std::vector<T>& a_vector, compareFunction<T>& a_compare)
{
    size_t const size = a_vector.size();
    impl::quickSortRec(a_vector, 0, size - 1, a_compare);
}

void countingSort(std::vector<int>& a_vector)
{
    int max, min;
    int const size = a_vector.size();
    impl::findMax(a_vector, max, size);
    impl::findMin(a_vector, min, size); 

    int* frequency;
    impl::mallocFrequency(frequency, min, max);

    impl::calculateFrequency(a_vector, frequency, min, size);
    impl::calculateCumulativeFrequency(frequency, max - min);

    int* sort = new int[size];
    impl::makeSoreArray(a_vector, sort, frequency, min, size);
    impl::copySoreArrayToOriginal(a_vector, sort, size);

    delete[] sort;
    delete[] frequency;
}

void redixSort(std::vector<int>& a_vector)
{

    const int  size = a_vector.size();
    const int digitsSize = 19;
    int* frequency = new int[digitsSize];
    int* sort = new int[size];

    int numberLength = impl::findMaxNumberLength(a_vector, size);

    for(int i = 0; i < numberLength; ++i)
    {
        impl::zeroArray(frequency, digitsSize);
        impl::calculateDigitFrequency(a_vector, i,  frequency, size);
        impl::calculateCumulativeFrequency(frequency, digitsSize - 1);
        impl::makeSoreArrayByDigit(a_vector, sort, frequency, i, size);
        impl::copySoreArrayToOriginal(a_vector, sort, size);
    }

    delete[] sort;
    delete[] frequency;
}

template<typename T>
size_t findByLiniarSearch(std::vector<T>& a_vector,  T a_elemnt, compareFunction<T>& a_compare)
{
    const size_t size = a_vector.size();
    T temp = a_vector[size - 1];
    a_vector[size - 1] = a_elemnt;
    size_t index = 0;

    while(true)
    {
        if(a_compare(a_vector[index], a_elemnt))
            break;
        
        ++index;
    }

    a_vector[size - 1] = temp;
    if(index != size - 1)
        return index;
    
    return size;
}

template<typename T>
size_t findByBinarySearch(std::vector<T>& a_vector, T a_elemnt, compareFunction<T>& a_less, compareFunction<T>& a_equal)
{
    const size_t size = a_vector.size();
    size_t first = 0;
    size_t last = size - 1;

    while(first <= last)
    {
        size_t mid = (first + last)/2;
        if(a_equal(a_vector[mid], a_elemnt))
            return mid;

        if(a_less(a_vector[mid], a_elemnt))
            first = mid + 1;

        else
            last = mid;
    }

    return size;
}


} // sort namespace
