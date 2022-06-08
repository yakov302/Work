#pragma once

namespace bst
{

namespace impl
{

template <typename T>
using actionFunction = std::function<bool(Node<T>*, void*)>;

template <typename T>
std::function<bool(Node<T>*, void*)>deleteAllNods(
[](Node<T>* a_node, void* a_context)
{
    delete a_node;
    return true;
}
);

template <typename T>
std::function<bool(Node<T>*, void*)>copyByLevels(
[](Node<T>* a_node, void* a_destination)
{
    ((Bst<T>*)a_destination)->push(a_node->data());
    return true;
}
);

template <typename T>
void setFather(BstIterator<T> &a_it, BstIterator<T> &a_childIt)
{
    if (!a_childIt.isNull())
    {
        BstIterator<T> father = a_it.father();
        a_childIt.setFather(father);
    }
}

template <typename T>
T removeLeaf(BstIterator<T> &a_it, BstIterator<T> a_childIt)
{
    T data = a_it.data();

    if (a_it.father().right() == a_it)
    {
        a_it.father().setRight(a_childIt);
        setFather(a_it, a_childIt);
    }

    if (a_it.father().left() == a_it)
    {
        a_it.father().setLeft(a_childIt);
        setFather(a_it, a_childIt);
    }

    a_it.distroy();
    return data;
}

template <typename T>
void swapIterators(BstIterator<T> &a_first, BstIterator<T> &a_second)
{
    T temp = a_first.data();
    a_first.data() = a_second.data();
    a_second.data() = temp;
}

template <typename T>
T removeOneChild(BstIterator<T> &a_it)
{
    if (!a_it.left().isNull())
    {
        return removeLeaf(a_it, a_it.left());
    }
    if (!a_it.right().isNull())
    {
        return removeLeaf(a_it, a_it.right());
    }
    return 0;
}

template <typename T>
T removeTwoChilds(BstIterator<T>& a_it)
{
    BstIterator<T> prev = a_it;
    --prev;
    swapIterators(prev, a_it);

    if (prev.left().isNull() && prev.right().isNull())
    {
        BstIterator<T> nullIt;
        return removeLeaf(prev, nullIt);
    }

    if (!prev.left().isNull() && !prev.right().isNull())
        return removeTwoChilds(prev);

    return removeOneChild(prev);
}


} // namespace impl

template <typename T>
Bst<T>::Bst(compareFunction a_compare)
: m_root(new Node<T>)
, m_compare(a_compare)
{
    m_root->setFather(m_root);
}

template <typename T>
Bst<T>::~Bst()
{
    if(m_root != nullptr)
    {
        forEach(IN_ORDER, impl::deleteAllNods<T>);
        delete m_root;
    }
}

template <typename T>
Bst<T>::Bst(Bst<T>& a_other)
: m_root(new Node<T>)
, m_compare(a_other.m_compare)
{
    m_root->setFather(m_root);
    a_other.forEach(BY_LEVELS, impl::copyByLevels<T>, this);
}

template <typename T>
Bst<T>::Bst(Bst<T>&& a_other)
: m_root(a_other.m_root)
, m_compare(a_other.m_compare)
{
    a_other.m_root = nullptr;
}

template <typename T>
Bst<T>& Bst<T>::operator=(Bst<T>& a_other)
{
    if(*this != a_other)
    {
        m_root = new Node<T>;
        m_root->setFather(m_root);
        m_compare = a_other.m_compare;
        a_other.forEach(BY_LEVELS, impl::copyByLevels<T>, this);
    }
    return *this;
}
 
template <typename T>
Bst<T>& Bst<T>::operator=(Bst<T>&& a_other)
{
    if(*this != a_other)
    {
        m_root = a_other.m_root;
        m_compare = a_other.m_compare;
        a_other.m_root = nullptr;
    }
    return *this;
}

template <typename T>
BstIterator<T> Bst<T>::begine()
{
    if (m_root->left() == nullptr)
    {
        return BstIterator(m_root);
    }
    return begineRec(m_root->left());
}

template <typename T>
BstIterator<T> Bst<T>::begineRec(Node<T> *a_node)
{
    if (a_node->left() == nullptr)
    {
        return BstIterator(a_node);
    }
    return begineRec(a_node->left());
}

template <typename T>
BstIterator<T> Bst<T>::end()
{
    return BstIterator(m_root);
}

template <typename T>
BstIterator<T> Bst<T>::push(T a_data)
{
    if (m_root->left() == nullptr)
    {
        m_root->setLeft(new Node(a_data, m_root));
        return BstIterator(m_root->left());
    }

    BstIterator<T> returnIt = pushRec(m_root->left(), a_data);
    if (returnIt.isNull())
        return end();

    return returnIt;
}

template <typename T>
BstIterator<T> Bst<T>::pushRec(Node<T> *a_node, T a_data)
{
    if (a_data == a_node->data())
        return BstIterator<T>(nullptr);

    if (m_compare(a_data, a_node->data()))
    {
        if (a_node->left() == nullptr)
        {
            a_node->setLeft(new Node(a_data, a_node));
            return BstIterator(a_node->left());
        }
        return pushRec(a_node->left(), a_data);
    }

    if (a_node->right() == nullptr)
    {
        a_node->setRight(new Node(a_data, a_node));
        return BstIterator(a_node->right());
    }
    return pushRec(a_node->right(), a_data);
}

template <typename T>
T Bst<T>::pull(BstIterator<T>& a_it)
{
    BstIterator<T> nallIt;
    if (a_it.left().isNull() && a_it.right().isNull())
        return impl::removeLeaf(a_it, nallIt);

    if (!a_it.left().isNull() && !a_it.right().isNull())
        return impl::removeTwoChilds(a_it);

    return impl::removeOneChild(a_it);
}

template <typename T>
void Bst<T>::pull(T a_data)
{
    T data = a_data;
    BstIterator<T> findIt = findFirst(findNodeByData<T>, (void*)&data);
    pull(findIt);
}

template <typename T>
BstIterator<T> Bst<T>::findFirst(actionFunction a_action, void* a_contex)
{
    return forEach(IN_ORDER, a_action, a_contex);
}

template <typename T>
BstIterator<T> Bst<T>::forEach(Modes a_mode, actionFunction a_action, void* a_contex)
{
    if(a_mode == PRE_ORDER)
        return forEachPreOrder(a_action, m_root->left(), a_contex);
    if(a_mode == IN_ORDER)
        return forEachInOrder(a_action, m_root->left(), a_contex);
    if(a_mode == POST_ORDER)
        return forEachPostOrder(a_action, m_root->left(), a_contex);
    if(a_mode == BY_LEVELS)
       return forEachByLevel(a_action, m_root->left(), a_contex);

    return end();
}

template <typename T>
BstIterator<T> Bst<T>::forEachInOrder(actionFunction& a_action, Node<T>* a_root, void* a_contex)
{
    BstIterator<T> returnIt;
    
    if(a_root == nullptr)
	    return end();
	
	if(a_root->left() != nullptr)
    {
		returnIt = forEachInOrder(a_action, a_root->left(), a_contex); 
        if(returnIt != end())
            return returnIt;
    }
		
	if(!a_action(a_root, a_contex))
        return BstIterator<T>(a_root);

	if(a_root -> right() != nullptr)
    {
		returnIt = forEachInOrder(a_action, a_root->right(), a_contex);
        if (returnIt != end())
            return returnIt;
    }
	
	return end();
}

template <typename T>
BstIterator<T> Bst<T>::forEachPreOrder(actionFunction& a_action, Node<T>* a_root, void* a_contex)
{
    BstIterator<T> returnIt;

    if(a_root == nullptr)
	    return end();
	
	if(!a_action(a_root, a_contex))
        return BstIterator<T>(a_root);
	
	if(a_root->left() != nullptr)
    {
		returnIt = forEachPreOrder(a_action, a_root->left(), a_contex);
        if(returnIt != end())
            return returnIt;
    }

	if(a_root->right() != nullptr)
    {
		returnIt = forEachPreOrder(a_action, a_root->right(), a_contex);
        if(returnIt != end())
            return returnIt;
    }
    
    return end();
}

template <typename T>
BstIterator<T> Bst<T>::forEachPostOrder(actionFunction& a_action, Node<T>* a_root, void* a_contex)
{
    BstIterator<T> returnIt;
    
    if(a_root == nullptr)
		return end();

	if(a_root->left() != nullptr)
    {
		returnIt = forEachPostOrder(a_action, a_root->left(), a_contex);
        if(returnIt != end())
            return returnIt;
    }

	returnIt = forEachPostOrder(a_action, a_root->right(), a_contex);
    if(returnIt != end())
            return returnIt;

    if(!a_action(a_root, a_contex))
        return BstIterator<T>(a_root);

    return end();
}

template <typename T>
BstIterator<T> Bst<T>::forEachByLevel(actionFunction& a_action, Node<T>* a_root, void* a_contex)
{
    BstIterator<T> returnIt;

    if(a_root == nullptr)
	    return end();

    if(a_root->father() == a_root->father()->father())
    {
	    if(!a_action(a_root, a_contex))
            return BstIterator<T>(a_root);
    }

	if(a_root->left() != nullptr)
    {
        if(!a_action(a_root->left(), a_contex))
            return BstIterator<T>(a_root->left());
    }

	if(a_root->right() != nullptr)
    {
		if(!a_action(a_root->right(), a_contex))
            return BstIterator<T>(a_root->right());
    }
 		
    returnIt = forEachByLevel(a_action, a_root->left(), a_contex);
    if(returnIt != end())
        return returnIt;

    returnIt = forEachByLevel(a_action, a_root->right(), a_contex);
    if(returnIt != end())
        return returnIt;

    return end();
}

template <typename T>
bool Bst<T>::operator==(Bst<T>& a_other)
{
    return m_root == a_other.m_root;
}

template <typename T>
bool Bst<T>::operator!=(Bst<T>& a_other)
{
    return m_root != a_other.m_root;
}


} // bst namespace