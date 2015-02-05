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
	Node** node;
	newToken = malloc(sizeof(Token));
	newToken->type=type;
	newToken->start=i;
	newToken->end=i;
	node = malloc(sizeof(Node*));
	*node = create_node(newToken);
	add_to_list(exprList, *node);
}

LinkedList createTokensList(char *expression){
	int i;
	LinkedList exprList = createList();
	for(i=0;expression[i];i++){
		if(isDigit(expression[i])){
			insertToken(&exprList, i, 1);
		} 
		if(expression[i]==32){
			insertToken(&exprList, i, 0);
		}
		if(!isDigit(expression[i]) && expression[i]!=32){
			insertToken(&exprList, i, 2);
		}  
	}
	return exprList;
}

void* getValues(LinkedList newList, Stack *operators, Stack *operand, char *expression){
	Node* walker = newList.head;
	int i, start,tmp=0,j=0;
	while(walker!=NULL){
		i =  ((Token*)walker->data)->type;
		start = (*(Token*)walker->data).start;
		if(i==1){
			(((Token*)walker->next->data)->type==1) && (tmp = tmp*10 + expression[start] - '0');
			(((Token*)walker->next->data)->type!=1) && (tmp = tmp*10 + expression[start] - '0');
			(((Token*)walker->next->data)->type!=1) && push(*operand, (voidPtr)tmp) && (tmp=0);
		}
		if(i==2){
			push(*operators, (voidPtr)expression[start]);
		}
		walker = walker->next;
		j++;
	}
	return 0;
}

void* doOperation(Stack *operators, Stack *operand, char *expression){
	char o1,o2,op;
	int i;
	for(i=0;i<=(operand->list->count)-1;i++){
		o2 = (int)pop(*operand);
		o1 = (int)pop(*operand);
		op = (char)pop(*operators);
		operation(o1, o2, op, *operand);
	}
	return 0;
}

int evaluate(char *expression){
	Stack operators=createStack(), operand=createStack();
	LinkedList newList = createTokensList(expression);
	getValues(newList, &operators, &operand, expression);
	doOperation(&operators, &operand, expression);
	return (int)(*operand.top)->data;
} 