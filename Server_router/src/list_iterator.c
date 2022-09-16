#include "list_iterator.h"

ListItr ListItrBegin(const List* _list)
{
	if(_list == NULL)
		return NULL;
	
	return _list-> m_head.m_next;
}

ListItr ListItrEnd(const List* _list)
{
	if(_list == NULL)
		return NULL;
	
	return (ListItr*)&_list-> m_tail;
}

int ListItrEquals(const ListItr _a, const ListItr _b)
{
	if(_a == NULL || _b == NULL)
		return -1;
	
	if(_a == _b)
		return 1;
	
	return 0;
}

ListItr ListItrNext(ListItr _itr)
{
	if(_itr == NULL)
		return NULL;
	
	return ((Node*)_itr) -> m_next;
}

ListItr ListItrPrev(ListItr _itr)
{
	if(_itr == NULL)
		return NULL;

	if(((Node*)_itr) -> m_prev -> m_prev == ((Node*)_itr) -> m_prev)
		return _itr;	
	
	return ((Node*)_itr) -> m_prev;
}

void* ListItrGet(ListItr _itr)
{
	if(_itr == NULL || _itr == ListItrNext(_itr))
		return NULL;

	return ((Node*)_itr) -> m_data;
}

void* ListItrSet(ListItr _itr, void* _element)
{
	void* oldElement;

	if(_itr == NULL || _element == NULL || _itr == ListItrNext(_itr))
		return NULL;
	
	oldElement = ((Node*)_itr) -> m_data;
	((Node*)_itr) -> m_data = _element;
	return oldElement;
}

ListItr ListItrInsertBefore(ListItr _itr, void* _element)
{
	Node *node = NULL;

	if(_itr == NULL || _element == NULL) 
		return NULL;

	if((node = (Node*) malloc(sizeof(Node))) == NULL)
		return NULL;	

	PushNode(node, _itr);
	node -> m_data = _element;
	return node;
}

void* ListItrRemove(ListItr _itr)
{
	void* deletedNodeData;

	if(_itr == NULL || _itr == ListItrNext(_itr))
		return NULL;

	deletedNodeData = ((Node*)_itr) -> m_data;
	PopNode(_itr);	
	return deletedNodeData;
}

static void PushNode(Node *_node, Node *_next)
{
	_node -> m_prev = _next -> m_prev;
	_node -> m_next = _next;
	_next -> m_prev -> m_next = _node;
	_next -> m_prev = _node;
}

static void PopNode(Node *_node)
{
	_node -> m_next -> m_prev = _node -> m_prev;
	_node -> m_prev -> m_next = _node -> m_next;
	free(_node);
}
