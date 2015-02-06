#include "rpn.h"
#include <stdio.h>
#include <stdlib.h>

int isDigit(char val){
	return val >= '0' && val <= '9';
}

void operation(int o1,int o2,char op,Stack operands) {
	int res;
	op == '+' && (res = o1+o2);
	op == '-' && (res = o1-o2);
	op == '*' && (res = o1*o2);
	op == '/' && (res = o1/o2);
	push(operands,(voidPtr)res);
}

void insertToken(LinkedList* exprList, int i, int type){
	Token *newToken;
	Node **node;
	newToken = malloc(sizeof(Token));
	newToken->type=type;
	newToken->location=i;
	node = malloc(sizeof(Node*));
	*node = create_node(newToken);
	add_to_list(exprList, *node);
}

LinkedList createTokensList(char *expression){
	int i;
	LinkedList exprList = createList();
	for(i=0;expression[i];i++){
		if(isDigit(expression[i])) insertToken(&exprList, i, 1);
		if(expression[i]==32) insertToken(&exprList, i, 0);
		if(!isDigit(expression[i]) && expression[i]!=32) insertToken(&exprList, i, 2);
	}
	return exprList;
}

void calculator(Stack *operand,char expression){
	char o1,o2;
	o2 = (int)pop(*operand);
	o1 = (int)pop(*operand);
	operation(o1, o2, expression, *operand);
}

void pushToStack(LinkedList newList, Stack *operand, char *expression){
	Node *walker = newList.head;
	int i, location, tmp=0, type, nextType=0;

	while(walker!=NULL){
		i =  ((Token*)walker->data)->type;
		location = (*(Token*)walker->data).location;
		if(i==1){
			nextType = ((Token*)walker->next->data)->type;
			(nextType==1) && (tmp = tmp*10 + expression[location] - '0');
			(nextType!=1) 
				&& (tmp = tmp*10 + expression[location] - '0')
				&& push(*operand, (voidPtr)tmp) && (tmp=0);
		}
		if(i==2) calculator(operand, expression[location]);
		walker = walker->next;
	}
}

int evaluate(char *expression){
	Stack operand=createStack();
	LinkedList newList = createTokensList(expression);
	pushToStack(newList, &operand, expression);
	return (int)(*operand.top)->data;
} 