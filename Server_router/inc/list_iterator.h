#ifndef LIST_ITERATOR_H
#define LIST_ITERATOR_H

#include "list.h"

typedef void* ListItr;

ListItr ListItrBegin(const List* _list);

ListItr ListItrEnd(const List* _list);

int ListItrEquals(const ListItr _a, const ListItr _b);

ListItr ListItrNext(ListItr _itr);

ListItr ListItrPrev(ListItr _itr);

void* ListItrGet(ListItr _itr);

void* ListItrSet(ListItr _itr, void* _element);

ListItr ListItrInsertBefore(ListItr _itr, void* _element);

void* ListItrRemove(ListItr _itr);


#endif // LIST_ITERATOR_H