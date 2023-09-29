#include<stdio.h> 
#include<stdlib.h>
#include<string.h>

typedef struct {
	char top;
	int size;
	char *arr;
}stack;

int isEmpty(stack s)
{
    if (s.top == -1)
        return 1;
    else
        return 0;
}

void push(stack s, char value)
{
    if (s.top == s.size-1)
    {
        int newSize = s.size + 5;
        char *newArr = (char *)realloc(s.arr, sizeof(char) * newSize);
        if(newArr == NULL){
			printf("Memory can't be allocated\n");
			exit(EXIT_FAILURE);
		}
        s.arr = newArr;
        s.size = newSize;
    }

    s.top++;
	s.arr[s.top] = value;
}

int pop(stack s)
{
    if( isEmpty(s) == 1)
    {
        printf("Stack is empty\n");
        return -1;
    }
	int temp = s.top;
    s.top--;
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
		return -1;
}

char * intoPostfix(char *exp){
	stack sp;
	sp.size = 0;
	char *postfix = (char *)malloc((strlen(exp) + 1)*sizeof(char));
	int i = 0, j = 0;

	while(exp[i] != '\0'){
		if(!isOperator(exp[i])){
			postfix[j] = exp[i];
			i++;
			j++;
		}
		else{
			if(precedence(exp[i] > precedence(sp.top))){
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
	return postfix;
}

int main()
{
	char exp[] = {"a-b*d+c\0"};

	printf("%s",intoPostfix(exp));
    return 0;
}
