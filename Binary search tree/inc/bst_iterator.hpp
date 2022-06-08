# pragma once

namespace bst
{

template<typename T>
class BstIterator
{
public:
    BstIterator(Node<T>* a_node = nullptr);

    BstIterator<T> father();
    BstIterator<T> left();
    BstIterator<T> right();

    void setFather(BstIterator<T>& a_it);
    void setLeft(BstIterator<T>& a_it);
    void setRight(BstIterator<T>& a_it);

    T& data();

    bool operator==(BstIterator<T> a_itr);
    bool operator!=(BstIterator<T> a_itr);

    BstIterator<T>& operator++();
    BstIterator<T>& operator--();
	BstIterator<T> operator++(int);
	BstIterator<T> operator--(int);
    
    T& operator*();
    T* operator->();

    bool isNull();
    void distroy();

private:
    Node<T>* m_current;
};


} // bst namespace

#include "./inl/bst_iterator.hxx"
