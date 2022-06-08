#pragma once

namespace bst
{

template<typename T>
class Node
{
public:
    Node(T a_data = 0, Node<T>* a_father = nullptr);

    Node<T>* father();
    Node<T>* left();
    Node<T>* right();

    void setFather(Node<T>* a_node);
    void setLeft(Node<T>* a_node);
    void setRight(Node<T>* a_node);

    T& data();

private:
    T m_data;
    Node<T>* m_father;
    Node<T>* m_left;
    Node<T>* m_right;
};


} // bst namespace

#include "./inl/bst_node.hxx"
