#include <stdio.h>
#include <string.h>

int top = -1;
char myStack[100];
char postfix[100];
int size = 0;

void push(char item){
	top++;
	*(myStack + top) = item;	
}

char pop() {
    char item = myStack[top];
    top--;
    return item;
}

int precedence(char temp){
	if(temp == '('){
		return 0;
	}
	else if( temp == '+' || temp == '-'){
		return 1;
	}
	else if( temp == '*' || temp == '/'){
		return 2;
	}
}

void reverseString(char *str) {
    int length = strlen(str);
    for (int i = 0; i < length / 2; i++) {
        char temp = str[i];
        str[i] = str[length - i - 1];
        str[length - i - 1] = temp;
    }
}


void toPostfix(char *expression){
    int ctr = 0;
    
    while(*expression != '\0'){
        if(*expression >= '0' && *expression <= '9'){
            postfix[ctr] = *expression;
            ctr++;
        }
        else if(*expression == '('){
            push(*expression);
        }
        else if(*expression == ')'){
            while(top != -1 && myStack[top] != '('){
                //postfix[ctr]= pop();
				postfix[ctr] = myStack[top];
                ctr++;
				pop();
            }
            pop();
        }
        else{
            while(top != -1 && precedence(myStack[top]) >= precedence(*expression)){
                 //postfix[ctr]= pop();
				postfix[ctr] = myStack[top];
                ctr++;
                pop();
            }
            push(*expression);
        }
        expression++; 
    }
    
    while(top != -1){
    	 //postfix[ctr]= pop();
        postfix[ctr] = myStack[top];
        ctr++;
        pop();
    }
    postfix[ctr] = '\0'; 
}


void toPrefix(char *expression) {
    //strrev(expression);
    reverseString(expression);
    for(int i= 0; i < size;i++){
    	if(expression[i] == ')'){
    		expression[i] = '(';
		}
		else if(expression[i] == '('){
    		expression[i] = ')';
		}
	}
	
	toPostfix(expression);
    
    //strrev(expression);
    reverseString(postfix);
    
}

int evalPrefix(char *prefix) {
    
    for(int i = size - 1; i >= 0; i--) {
        if(prefix[i] >= '0' && prefix[i] <= '9') {
            push(prefix[i] - '0');
        } else {
            int num1 = pop();
            int num2 = pop();
            
            switch(prefix[i]) {
                case '+':
                    push(num1 + num2);
                    break;
                case '-':
                    push(num1 - num2);
                    break;
                case '*':
                    push(num1 * num2);
                    break;
                case '/':
                    push(num1 / num2);
                    break;				
            }
        }	
    }
    
    return pop();
}


int main(){
	char expression[100];
	
	printf("Enter an Expression: ");
	scanf("%s",expression);
    size = strlen(expression);
    //size = sizeof(expression)/sizeof(expression[0]);
	printf("Infix Expression is: %s",expression);
	
	toPostfix(expression);
	printf("\nPostfix Expression is: %s",postfix);
	
	toPrefix(expression);
	printf("\nPrefix Expression is: %s",postfix);
	
	int result = evalPrefix(postfix);
	printf("\nEvaluated Expression is: %d", result);
	return 0;
}