#include<stdio.h> 
#include<stdlib.h>
#include<string.h>

typedef struct {
	int top;
	int size;
	char *arr;
}stack;

int isEmpty(stack *s)
{
    if (s->top == -1)
        return 1;
    else
        return 0;
}

void push(stack *s, char value)
{
    if (s->top == s->size-1)
    {
        int newSize = s->size + 5;
        char *newArr = (char *)realloc(s->arr, sizeof(char) * newSize);
        if(newArr == NULL){
			printf("Memory can't be allocated\n");
			exit(EXIT_FAILURE);
		}
        s->arr = newArr;
        s->size = newSize;
    }

    s->top++;
	s->arr[s->top] = value;
}

char pop(stack *s)
{
    if( isEmpty(s) == 1)
    {
        printf("Stack is empty\n");
        return -1;
    }
	char temp = s->arr[s->top];
    s->top--;
	return temp;
}

int isOperator(char exp){
	if(exp == '+' || exp == '-' || exp == '*' || exp == '/' || exp == '^')
		return 1;
	return 0;
}

int precedence(char exp){
	if (exp == '+' || exp == '-')
		return 1;
	else if(exp == '*' || exp == '/')
		return 2;
	else if(exp == '^')
		return 3;
	else
		return 0;
}

char stackTop(stack *s){
	if(s->top == -1)
		return '0';
	else
		return s->arr[s->top];
}
char * intoPostfix(char *exp){
	stack *sp = (stack *)malloc(sizeof(stack));
	sp->size = 10;
	sp->top = -1;
	sp->arr = (char *)malloc(sp->size * sizeof(char));
	char *postfix = (char *)malloc((strlen(exp) + 1)*sizeof(char));
	int i = 0, j = 0;

	if(sp->arr == NULL || postfix == NULL){
		printf("Memory can't allocated\n");
		exit(EXIT_FAILURE);
	}

	while(exp[i] != '\0'){
		if(!isOperator(exp[i])){
			postfix[j] = exp[i];
			i++;
			j++;
		}
		else{
			if(precedence(exp[i]) > precedence(stackTop(sp))){
				push(sp,exp[i]);
				i++;
			}
			else{
				postfix[j] = pop(sp);
				j++;
			}
		}
	}
	while(!isEmpty(sp)){
		postfix[j] = pop(sp);
		j++;
	}
	postfix[j] = '\0';
	free(sp->arr);
	return postfix;
}

int main()
{
	char exp[] = {"A+B*C/(E-F)"};

	printf("%s",intoPostfix(exp));
    return 0;
}
