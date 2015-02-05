#include "expr_assert.h"
#include "rpn.h"
#include <stdio.h>

void test_insertToken_inserts_a_token_into_the_list(){
	LinkedList exprList = createList();
	insertToken(&exprList, 0, 1);
	assertEqual(((Token*)exprList.head->data)->type, 1);
	assertEqual(((Token*)exprList.head->data)->start, 0);
	assertEqual(((Token*)exprList.head->data)->end, 0);	
}
void test_createTokenList_creates_a_list_of_tokens(){
	char * expression ="2 3 +";
	LinkedList newList = createTokensList(expression);

	assertEqual(((Token*)newList.head->data)->type, 1);
	assertEqual(((Token*)newList.head->data)->start, 0);

	assertEqual(((Token*)newList.head->next->data)->type, 0);
	assertEqual(((Token*)newList.head->next->data)->start, 1);	

	assertEqual(((Token*)newList.head->next->next->data)->type, 1);
	assertEqual(((Token*)newList.head->next->next->data)->start, 2);		
}

void test_getValues_pushes_the_operands_into_the_operands_stack(){
	char * expression ="2 3 +";
	LinkedList newList = createTokensList(expression);
	Stack operator=createStack(), operand=createStack();
	getValues(newList, &operator, &operand, expression);
	assertEqual((int)(*operand.top)->data, 3);
	assertEqual((char)(*operator.top)->data, '+');
}

void test_doOpertion_operates_on_the_operand_stsack_and_gives_the_result_back(){
	char * expression ="2 3 +";
	LinkedList newList = createTokensList(expression);
	Stack operator=createStack(), operand=createStack();
	getValues(newList, &operator, &operand, expression);
	doOperation(&operator, &operand, expression);
	assertEqual((int)(*operand.top)->data, 5);
}


void test_evaluate_returns_5_for_2_3_Plus (){
	char * expression ="2 3 +";
	int result  =  evaluate(expression);
	assertEqual(result, 5);
}

void test_evaluate_returns_1_for_2_3_MINUS (){
	char * expression ="2 3 -";
	int result  =  evaluate(expression);
	assertEqual(result, -1);
}

void test_evaluate_returns_6_for_2_3_multiply (){
	char * expression ="2 3 *";
	int result  =  evaluate(expression);
	assertEqual(result, 6);
}

void test_evaluate_returns_0_for_2_3_divide (){
	char * expression ="2 3 /";
	int result  =  evaluate(expression);
	assertEqual(result, 0);
}

void test_evaluate_returns_9_for_2_3_4_plus_plus (){
	char * expression ="2 3 4 + +";
	int result  =  evaluate(expression);
	assertEqual(result, 9);
}

void test_evaluate_returns_120_for_1_2_3_4_5_mul_mul_mul_mul (){
	char * expression ="1 2 3 4 5 * * * *";
	int result  =  evaluate(expression);
	assertEqual(result, 120);
}

void test_evaluate_returns_63_for_21_22_add (){
	char * expression ="21 22 +";
	int result  =  evaluate(expression);
	assertEqual(result, 43);
}

void test_evaluate_returns_60_for_20_20_20_add_add (){
	char * expression ="20 20 20 + +";
	int result  =  evaluate(expression);
	assertEqual(result, 60);
}