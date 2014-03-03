#pragma warning(disable: 4996)
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "intstack.h"

#define MAX_LINE 80

int precedence(char a, char b){
	if ((a == '*' || a == '/') && (b == '+' || b == '-'))
		return 1;
	else if ((b == '*' || b == '/') && (a == '+' || a == '-'))
		return -1;
	else
		return 0;
}

void infixTopostfix(char *infix, char *postfix){
	Tintstack operator_stack;
	int i = 0, j = 0, oper;
	char first_in_stack;

	initialize_int_stack(&operator_stack);

	while (i < strlen(infix)){// search the string until the end of the string
		if (infix[i] == '+' ||
			infix[i] == '-' ||
			infix[i] == '*' ||
			infix[i] == '/'){
			if (is_empty_int_stack(&operator_stack) == 1)// if stack is empty push symbol there
				push_int(&operator_stack, infix[i]);
			else{
				// compare the precedence
				pop_int(&operator_stack, &oper);
				first_in_stack = oper;
				if (precedence(first_in_stack, infix[i]) == 1){
					postfix[j++] = first_in_stack;
					push_int(&operator_stack, infix[i]);
				}
				if (precedence(first_in_stack, infix[i]) == -1) {
					push_int(&operator_stack, first_in_stack);
					push_int(&operator_stack, infix[i]);
				}
				if (precedence(first_in_stack, infix[i]) == 0) {
					if (first_in_stack != '(') // skip if encounter '('
						postfix[j++] = first_in_stack;
					push_int(&operator_stack, infix[i]);
				}
			}
		}
		else if (infix[i] == '('){
			push_int(&operator_stack, infix[i]);
		}
		else if (infix[i] == ')'){
			while (is_empty_int_stack(&operator_stack) != 1){
				pop_int(&operator_stack, &oper);
				first_in_stack = oper;
				if (first_in_stack != '(') // skip if encounter '('
					postfix[j++] = first_in_stack;
			}
		}
		else
			postfix[j++] = infix[i];
		i++;
	}
	while (is_empty_int_stack(&operator_stack) != 1){
		pop_int(&operator_stack, &oper);
		first_in_stack = oper;
		postfix[j++] = first_in_stack;
	}
	postfix[j] = '\0';
}

int main(){

	char *input;
	char *output;
	Tintstack my_stack;
	int tmp_num1 = 0, tmp_num2 = 0, count = 0;
	initialize_int_stack(&my_stack);

	printf("\n Infix to postfix converter and calculator\n");
	printf("\n Give an infix equation at one line: \n\n ");
	input = (char*)malloc(MAX_LINE * sizeof(char));
	output = (char*)malloc(MAX_LINE * sizeof(char));
	scanf("%s", input);
	// function that converts infix input into postfix output
	infixTopostfix(input, output); 
	// perfirming calculations over postfix notation using stack
	while (count < strlen(output)){
		if (isdigit(output[count])){
			tmp_num1 = output[count] - 48;
			push_int(&my_stack, tmp_num1);
		}
		else{
			if (output[count] =='+'){
				pop_int(&my_stack, &tmp_num1);
				pop_int(&my_stack, &tmp_num2);
				push_int(&my_stack, tmp_num1 + tmp_num2);
			}
			if (output[count] == '-'){
				pop_int(&my_stack, &tmp_num1);
				pop_int(&my_stack, &tmp_num2);
				push_int(&my_stack, tmp_num1 - tmp_num2);
			}
			if (output[count] == '*'){
				pop_int(&my_stack, &tmp_num1);
				pop_int(&my_stack, &tmp_num2);
				push_int(&my_stack, tmp_num1 * tmp_num2);
			}
			if (output[count] == '/'){
				pop_int(&my_stack, &tmp_num1);
				pop_int(&my_stack, &tmp_num2);
				push_int(&my_stack, tmp_num1 / tmp_num2);
			}
		}
		count++;
	}
	pop_int(&my_stack, &tmp_num1);
	printf("\n Equivivalent postfix equation is %s \n", output);
	printf("\n And it's value is %d \n", tmp_num1);
	free(input);
	free(output);
	getchar();
	return 0;
}


