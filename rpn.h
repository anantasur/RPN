#include "stack.h"
typedef struct token Token;
struct token{
	int type;
	int start;
	int end;
};
int evaluate(char *expression);

void insertToken(LinkedList* exprList, int i, int type);
LinkedList createTokensList(char *expression);
void* getValues(LinkedList newList, Stack *operators, Stack *operand, char *expression);
void* doOperation(Stack *operators, Stack *operand, char *expression);