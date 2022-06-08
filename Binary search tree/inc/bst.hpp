#pragma once

#include <functional>

#include "bst_node.hpp"
#include "bst_iterator.hpp"

namespace bst
{

typedef enum
{
    PRE_ORDER,
    IN_ORDER,
    POST_ORDER,
    BY_LEVELS
} Modes;

template<typename T>
std::function<bool(T, T)> naturalLess(
    [](const T& a_first, const T& a_second)
    {
        return a_first < a_second;
    }
);

template<typename T>
std::function<bool(Node<T>*, void*)> printNodeData(
    [](Node<T>* a_node, void*)
    {
        std::cout << a_node->data() << ", ";
        return true;
    }
);

template<typename T>
std::function<bool(Node<T>*, void*)> findNodeByData(
    [](Node<T>* a_node, void* a_context)
    {
        T* element = (T*)a_context;
        if(a_node->data() == *element)
            return false;

        return true;
    }
);

template<typename T>
class Bst
{
public:
    using compareFunction = std::function<bool(T, T)>;
    using actionFunction = std::function<bool(Node<T>*, void*)>;

    Bst(compareFunction a_compare = naturalLess<T>);
    ~Bst();

    Bst(Bst<T>& a_other);
    Bst(Bst<T>&& a_other);
    Bst& operator=(Bst<T>& a_other);
    Bst& operator=(Bst<T>&& a_other);

    BstIterator<T> begine();
    BstIterator<T> end();

    BstIterator<T> push(T a_data);
    T pull(BstIterator<T>& a_it);
    void pull(T a_data);

    size_t size();

    BstIterator<T> forEach(Modes a_mode, actionFunction a_action = printNodeData<T>, void* a_contex = nullptr);
    BstIterator<T> findFirst(actionFunction a_action = findNodeByData<T>, void* a_contex = nullptr);

    bool operator==(Bst<T>& a_other);
    bool operator!=(Bst<T>& a_other);

private:
    BstIterator<T> begineRec (Node<T>* a_node);
    BstIterator<T> pushRec(Node<T>* a_node, T a_data);
    T removeOneChild(BstIterator<T> &a_it);
    T removeTwoChilds(BstIterator<T>& a_it);
    T removeLeaf(BstIterator<T> &a_it, BstIterator<T> a_childIt);
    BstIterator<T> forEachPreOrder(actionFunction& a_action, Node<T>* a_root, void* a_contex);
    BstIterator<T> forEachInOrder(actionFunction& a_action, Node<T>* a_root, void* a_contex);
    BstIterator<T> forEachPostOrder(actionFunction& a_action, Node<T>* a_root, void* a_contex);
    BstIterator<T> forEachByLevel(actionFunction& a_action, Node<T>* a_root, void* a_contex);

private:
    Node<T>* m_root;
    compareFunction m_compare;
    size_t m_size;
};


} // bst namespace

#include "./inl/bst.hxx"
