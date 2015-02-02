#include "linkedList.h"

typedef struct stack Stack;
struct stack{
	LinkedList *list;
	Node **top;
};

Stack createStack(void);
int push(Stack, void *);
void * pop(Stack );