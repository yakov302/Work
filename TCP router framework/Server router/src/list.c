#include "list.h"

List* ListCreate(void)
{
	List* list;
	if ((list = (List*) malloc (sizeof(List))) == NULL) 
        	return NULL;

   	list-> m_head.m_next = &list-> m_tail;
  	list-> m_head.m_prev = &list-> m_head;
  	list-> m_tail.m_next = &list-> m_tail;
	list-> m_tail.m_prev = &list-> m_head;
	list->m_size = 0;
 	return list;
}

void ListDestroy(List** _list, void(*_elementDestroy)(void* _item))
{
	Node* temp;
	Node* tempNext;

	if(_list == NULL || *_list == NULL)
		return;
	
	temp = (*_list) -> m_head.m_next;
   	while (temp != &(*_list)-> m_tail)
	{
		if(_elementDestroy != NULL)
			_elementDestroy(temp -> m_data);		

		tempNext = temp -> m_next;
		free(temp);
		temp = tempNext;   		
	}

	free(*_list);
	*_list = NULL;
}

void ListErase(List** _list, void (*_elementDestroy)(void* _item))
{
	Node* temp;
	Node* tempNext;

	if(_list == NULL || *_list == NULL)
		return;
	
	temp = (*_list) -> m_head.m_next;
   	while (temp != &(*_list)-> m_tail)
	{
		if(_elementDestroy != NULL)
			_elementDestroy(temp -> m_data);		

		tempNext = temp -> m_next;
		free(temp);
		temp = tempNext;   		
	}
}

ListResult ListPushHead(List* _list, void* _item)
{
	Node *node = NULL;

	if(_list == NULL || _item == NULL)
		return LIST_UNINITIALIZED_ERROR;
	
	if((node = (Node*) malloc(sizeof(Node))) == NULL)
		return LIST_ALLOCATION_ERROR;

	node -> m_data = _item;
	PushNode(node,_list -> m_head.m_next);
	_list->m_size++;
	return LIST_SUCCESS;
}

ListResult ListPushTail(List* _list, void* _item)
{
	Node* node = NULL;

	if(_list == NULL || _item == NULL)
		return LIST_UNINITIALIZED_ERROR;

	if((node = (Node*) malloc(sizeof(Node))) == NULL)
		return LIST_ALLOCATION_ERROR;

	node -> m_data = _item;
	PushNode(node, &_list -> m_tail);
	_list->m_size++;
	return LIST_SUCCESS;
}

ListResult ListPopHead(List* _list, void** _item)
{
	if (_list == NULL ||  _item == NULL) 
      	return LIST_UNINITIALIZED_ERROR;
   		
	if(_list -> m_head.m_next == &_list -> m_tail)
		return LIST_UNDERFLOW_ERROR;
	
	*_item = _list -> m_head.m_next -> m_data;
	PopNode (_list -> m_head.m_next); 
	_list->m_size--;
	return LIST_SUCCESS;
}

ListResult ListPopTail(List* _list, void** _item)
{
	if (_list == NULL || _item == NULL) 
      	return LIST_UNINITIALIZED_ERROR;
   	
	if(_list ->m_head.m_next == &_list -> m_tail)
		return LIST_UNDERFLOW_ERROR;
	
	*_item = _list-> m_tail.m_prev -> m_data;
	PopNode(_list -> m_tail.m_prev);
	_list->m_size--;	
	return LIST_SUCCESS;
}

size_t ListSize(const List* _list)
{
	size_t count = 0;
	Node* node;

	if (_list == NULL) 
       	return 0;
   	
	node = _list -> m_head.m_next;
	while(node != &_list-> m_tail) 
	{
		count++; 
		node = node -> m_next; 
	} 

	return count;
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

void ListPrint(List* _list, void(*printItem)(void* item))
{
	int i = 1;
	Node *node;
	void* item;

	if (_list == NULL || printItem == NULL) 
        return;
	
	node =_list -> m_head.m_next;
	while(node != &_list-> m_tail) 
	{
		item = node -> m_data;
		printItem(item);
		node = node -> m_next; 
	} 
}
