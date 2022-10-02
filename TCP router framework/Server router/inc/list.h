#ifndef LIST_H
#define LIST_H

#include <stddef.h>  
#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    void* m_data;
    struct Node *m_next;
    struct Node *m_prev;

}Node;

typedef struct List
{
    Node m_head;
    Node m_tail;
    size_t m_size;

}List;

typedef enum List_Result{
    LIST_SUCCESS,
    LIST_UNINITIALIZED_ERROR,			
    LIST_ALLOCATION_ERROR,				
    LIST_NULL_ELEMENT_ERROR,
    LIST_UNDERFLOW_ERROR

} ListResult;

static void PushNode(Node *_node, Node *_next);

static void PopNode(Node *_node);

List* ListCreate(void);

void ListDestroy(List** _list, void (*_elementDestroy)(void* _item));

void ListErase(List** _list, void (*_elementDestroy)(void* _item));

ListResult ListPushHead(List* _list, void* _item);

ListResult ListPushTail(List* _list, void* _item);

ListResult ListPopHead(List* _list, void** _item);

ListResult ListPopTail(List* _list, void** _pItem);

size_t ListSize(const List* _list);

void ListPrint(List* _list, void(*printItem)(void* item));


#endif// LIST_H

