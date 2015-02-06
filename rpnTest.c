#include "expr_assert.h"
#include "rpn.h"
#include <stdio.h>

void test_insertToken_inserts_a_token_into_the_list(){
	LinkedList exprList = createList();
	insertToken(&exprList, 0, 1);
	assertEqual(((Token*)exprList.head->data)->type, 1);
	assertEqual(((Token*)exprList.head->data)->location, 0);
}
void test_createTokenList_creates_a_list_of_tokens(){
	char * expression ="2 3 +";
	LinkedList newList = createTokensList(expression);

	assertEqual(((Token*)newList.head->data)->type, 1);
	assertEqual(((Token*)newList.head->data)->location, 0);

	assertEqual(((Token*)newList.head->next->data)->type, 0);
	assertEqual(((Token*)newList.head->next->data)->location, 1);	

	assertEqual(((Token*)newList.head->next->next->data)->type, 1);
	assertEqual(((Token*)newList.head->next->next->data)->location, 2);		
}

void test_pushToStack_pushes_the_operands_into_the_operands_stack_and_calculates_result(){
	char * expression ="2 3 +";
	LinkedList newList = createTokensList(expression);
	Stack operand=createStack();
	pushToStack(newList, &operand, expression);
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

void test_evaluate_returns_14_for_5_1_2_add_4_mul_add_3_sub  (){
	char * expression ="5 1 2 + 4 * + 3 - ";
	int result  =  evaluate(expression);
	assertEqual(result, 14);
}

void test_evaluate_returns_14_for_2_2_sub_2_2_2_mul_2_sub_sub_sub  (){
	char * expression ="2 2 - 2 2 2 * 2 - - -";
	int result  =  evaluate(expression);
	assertEqual(result, 0);
}
