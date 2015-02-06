#include "stack.h"
typedef struct token Token;
typedef struct result Result;

struct result {
  int error;
  int status;
};
struct token{
	int type;
	int location;
};
int evaluate(char *expression);                                                           

void insertToken(LinkedList* exprList, int i, int type);
LinkedList createTokensList(char *expression);
void pushToStack(LinkedList newList, Stack *operand, char *expression);
void calculator(Stack *operand,char expression);
