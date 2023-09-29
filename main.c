#include<stdio.h> 
#include<stdlib.h>

typedef struct {
	char top;
	char *arr;
}stack;

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
	char *postfix = (char *)malloc(strlen(exp)*sizeof(char));
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
	char exp[] = {"a-b*d+c"};
	
	intoPostfix(exp);
    return 0;
}
