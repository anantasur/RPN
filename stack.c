#include "stack.h"
#include <stdlib.h>
#include <stdio.h>

Stack createStack(){
	LinkedList * list= calloc(sizeof(LinkedList),1);
	Stack newStack = {list, &list->tail};
	return newStack;
}

int push(Stack s,void* data){
	add_to_list(s.list, create_node(data));
	return s.list->count;
}

void * pop(Stack s){
	return deleteElementAt(s.list,s.list->count-1);
}
