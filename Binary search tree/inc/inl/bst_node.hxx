#pragma once

namespace bst
{

template <typename T>
Node<T>::Node(T a_data, Node<T> *a_father)
: m_data(a_data)
, m_father(a_father)
, m_left(nullptr)
, m_right(nullptr)
{

}

template <typename T>
Node<T>* Node<T>::father()
{
    return m_father;
}

template <typename T>
Node<T>* Node<T>::left()
{
    return m_left;
}

template <typename T>
Node<T>* Node<T>::right()
{
    return m_right;
}

template <typename T>
void Node<T>::setFather(Node<T>* a_node)
{
    m_father = a_node;
}

template <typename T>
void Node<T>::setLeft(Node<T>* a_node)
{
    m_left = a_node;
}

template <typename T>
void Node<T>::setRight(Node<T>* a_node)
{
    m_right = a_node;
}

template <typename T>
T& Node<T>::data()
{
    return m_data;
}


} // bst namespace
