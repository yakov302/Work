#pragma once

namespace bst
{

namespace impl
{

template <typename T>
void goRightAndThenToFarLeft(Node<T>*& a_node)
{
    a_node = a_node->right();
    while (a_node->left() != nullptr)
    {
        a_node = a_node->left();
    }
}

template <typename T>
void goUpUntilYoreFatherLeftBigerThenMe(Node<T>*& a_node)
{
    if(a_node == a_node->father())
        return;
        
    Node<T> *father = a_node->father();
    while(father->left() != a_node)
    {
        a_node = father;
        father = father->father();
    }
    a_node = father;
}

template <typename T>
void goLeftAndThenToFarRight(Node<T>*& a_node)
{
    a_node = a_node->left();
    while (a_node->right() != nullptr)
    {
        a_node = a_node->right();
    }
}

template <typename T>
void goUpUntilYoreFatherRightSmallerThenMe(Node<T>*& a_node)
{
    Node<T> *father = a_node->father();
    while (father->right() != a_node)
    {
        if(father == a_node)
            return;

        a_node = father;
        father = father->father();
    }
    a_node = father;
}


} //impl namespace

template <typename T>
BstIterator<T>::BstIterator(Node<T> *a_node)
: m_current(a_node)
{

}

template <typename T>
BstIterator<T> BstIterator<T>::father()
{
    return BstIterator<T>(m_current->father());
}

template <typename T>
BstIterator<T> BstIterator<T>::left()
{
    return BstIterator<T>(m_current->left());
}

template <typename T>
BstIterator<T> BstIterator<T>::right()
{
    return BstIterator<T>(m_current->right());
}

template <typename T>
void BstIterator<T>::setFather(BstIterator<T>& a_it)
{
    m_current->setFather(a_it.m_current);
}

template <typename T>
void BstIterator<T>::setLeft(BstIterator<T>& a_it)
{
    m_current->setLeft(a_it.m_current);
}

template <typename T>
void BstIterator<T>::setRight(BstIterator<T>& a_it)
{
    m_current->setRight(a_it.m_current);
}

template <typename T>
T& BstIterator<T>::data()
{
    return m_current->data();
}

template <typename T>
bool BstIterator<T>::isNull()
{
    return m_current == nullptr;
}

template <typename T>
void BstIterator<T>::distroy()
{
    delete m_current;
}

template <typename T>
bool BstIterator<T>::operator==(BstIterator<T> a_itr)
{
    return m_current == a_itr.m_current;
}

template <typename T>
bool BstIterator<T>::operator!=(BstIterator<T> a_itr)
{
    return m_current != a_itr.m_current;
}

template <typename T>
BstIterator<T>& BstIterator<T>::operator++()
{
    if (m_current->right() != nullptr)
    {
        impl::goRightAndThenToFarLeft(m_current);
        return *this;
    }

    impl::goUpUntilYoreFatherLeftBigerThenMe(m_current);
    return *this;
}

template <typename T>
BstIterator<T> BstIterator<T>::operator++(int)
{
    Node<T>* node = m_current;
    ++*this;
    return BstIterator(node);
}

template <typename T>
BstIterator<T> &BstIterator<T>::operator--()
{
    if (m_current->left() != nullptr)
    {
        impl::goLeftAndThenToFarRight(m_current);
        return *this;
    }

    impl::goUpUntilYoreFatherRightSmallerThenMe(m_current);
    return *this;
}

template <typename T>
BstIterator<T> BstIterator<T>::operator--(int)
{
    Node<T> *node = m_current;
    --*this;
    return BstIterator(node);
}

template <typename T>
T& BstIterator<T>::operator*()
{
    return m_current->data();
}

template <typename T>
T *BstIterator<T>::operator->()
{
    return &m_current->data();
}

   
} // bst namespace