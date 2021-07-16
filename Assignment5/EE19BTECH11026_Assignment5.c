// The comments on the push and pop function maybe sparse


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
struct node{											// Handles creating the expression
	char op;
	struct node* next;
};


typedef struct node node;

struct node2{											// Handles operating on a stack
	float op;
	struct node2* next;;
};

typedef struct node2 node2;

float eval(char exp[]);									// Evaluates a postfix expression
int getorder(char ch);									// Returns the order of a character, to find out its precedence as well as the type
float calc(float a, float b, char op);					// Simple function that calculates according to operator
void push2(node2** head,float p);						// Pushes to a stack of node2 type
void push(node** head,char p);							// Pushes to a stack of node type
void pop(node** head);									// Pops from a stack of node type
void pop2(node2** head);								// Pops from a stack of node2 type


int main(int argc, char const *argv[]){
	int s =0;
	int l = 0;
	int error = 0;
	int wasint = 0;
	int wasbrace  = 0;
	int i;
	char exp[100];
	char pfix[100];
	node* head = (node*)malloc(sizeof(node));
	printf("Enter your expression, w/o spaces:\n");
	scanf("%s",exp);
	for( i=0;i<strlen(exp);++i)
	{
		int k = getorder(exp[i]);
		if(k == -1){														// Checks whether it is a no. or not
			pfix[l] = exp[i];
			wasint = 1;
			if(wasbrace == 1){												// If brackets preceeds it, error 
				printf("Invalid brackets placement at %d\n", i);
				error = 1;
				break;
			}
			++l;
		}
		else if(k == -2){													// Checks if invalid characters are present in the expression
			printf("Invalid character, error at %d\n",i );
			error = 1;
			break;
		}
		else if(k<3){														// Checks if it is an operator
			if(l==0){														// In case of operators in the beginning
				printf("Invalid operator placement at the beginning, error at %d\n",i );
				error = 1;
				break;
			}
			if(s>0){ 														// If the stack is not empty
				while(getorder(head -> op)>=k && getorder(head -> op)<3){	// pops the stack of all the higher or same preference operators
					pfix[l] = ' ';											// making sure to add a space before putting the operator in
					++l;
					pfix[l] = head -> op;
					pop(&head);
					++l;
					--s;
				}
			}
			if(wasint == 0){												// In case of adjacent operators
				printf("Invalid operator placement, error at %d\n",i );
				error = 1;
				break;
			}
			wasint = 0;
			wasbrace = 0;
			push(&head,exp[i]);												// Pushes the current operator to the stacke
			pfix[l] = ' ';
			++l;
			++s;
		}
		else if(k < 6){														// Checks for opening braces
			push(&head,exp[i]);
			// ++l;
			++s;
			if(wasint == 1){												// In case an integer preceeded the brackets
				printf("Invalid brackets placement, error at %d\n",i );
				error = 1;
				break;
			}
		}
		else{
			while(getorder(head -> op)<3 && s>0){							// Pops everything from the stack until an opening brace is found
				pfix[l] = ' ';
				++l;
				pfix[l] = head -> op;
				pop(&head);
				++l;
				--s;
			}
			if((getorder(head -> op))+3 != k){								// Checks if the opening and closing braces match
				printf("Mismatched bracket at %d\n",i );
				error = 1;
				break;
			}

			pop(&head);														// If they do, pops the opening brace from stack
			--s;
			wasbrace = 1;
		}

	}
	while(s>0){																// Frees the stack of any leftovers
		pfix[l] = ' ';
		++l;
		pfix[l] = head -> op;
		pop(&head);
		++l;
		--s;
	}
	pfix[l] ='\0';
	printf("Expression:\n");
	printf("%s\n",exp );
	if(!error){																// Final output
		printf("Prefix:\n");
		printf("%s\n",pfix);
		printf("Value:%f \n",eval(pfix));

	}
	else{																	// Fancy error checking
		for (int j = 0; j < i; ++j)
		{
			printf(" ");
		}
		printf("^\n");
	}
	return 0;
}



float eval(char exp[]){										// Evaluates a postfix expression
	node2* head = (node2*)malloc(sizeof(node2));
	float buff = 0;
	int wasint = 0;
	int s = 0;
	for (int i = 0; i < strlen(exp); ++i)
	{
		buff = 0;
		wasint = 0;
		while(getorder(exp[i]) == -1){						// Reads and extracts each integer
			buff = buff*10 + (exp[i] - 48);
			wasint = 1;			
			++i;

		}
		if(wasint){											// Once reading an integer is finished, it is pushed to the stack
			push2(&head,buff);
			++s;
		}
		else if(getorder(exp[i])>=0){						// Checks whether it is an operator or not			
			buff = head -> op;
			pop2(&head);									
			--s;
			buff = calc(head -> op,buff,exp[i]);			// Does the operation on the top 2 elements
			pop2(&head);	
			push2(&head,buff);								// And pops the stack of the 2 elements and pushes the result
		}



	}
	return buff;
}



int getorder(char ch){									// Returns the order of a character, to find out its precedence as well as the type
	switch(ch){
		case '+':
		case '-':
				 return 0;
				 break;
		case '*':
		case '/':
				 return 1;
				 break;
		case '^':
				 return 2;
				 break;
		case '(':
				 return 3;
				 break;
		case '{':
				 return 4;
				 break;
		case '[':
				 return 5;
				 break;
		case ')':
				 return 6;
				 break;
		case '}':
				 return 7;
				 break;
		case ']':
				 return 8;
				 break;
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
		case '0':
				 return -1;
				 break;
		default: 												// Returns -2 if it is error		
				 return -2;
	}
}

float calc(float a, float b, char op){							// Simple function that calculates according to operator
	switch(op){
		case '+':
				 return a+b;
				 break;
		case '-':
				 return a-b;
				 break;
		case '*':
				 return a*b;
				 break;
		case '/':
				 return a/b;
				 break;
		case '^':
				 return pow(a,b);
				 break;
		
	}
}

void push2(node2** head,float p){							// Pushes to a stack of node2 type
	node2* temp = (node2*)malloc(sizeof(node2));
	temp -> op = p;
	temp -> next = NULL;
	
	
		if((*head) == NULL){
			*head = temp;
			// printf("DEBUG: Pos1\n");
		}
		else
			temp -> next = *head;
			*head = temp;
	

}

void push(node** head,char p){								// Pushes to a stack of node type
	node* temp = (node*)malloc(sizeof(node));
	temp -> op = p;
	temp -> next = NULL;
	
	
		if((*head) == NULL){
			*head = temp;
		}
		else
			temp -> next = *head;
			*head = temp;
	

}


void pop(node** head){										// Pops from stack of node type
	if(*head == NULL){
		printf("No Value left to pop\n");
	}
	else{
		node* temp = *head;
		if((*head) -> next !=NULL)			
			*head = (*head) -> next;
		free(temp);
	}

	
}


void pop2(node2** head){									// Pops from a stack fo node2 type
	if(*head == NULL){
		printf("No Value left to pop\n");
	}
	else{
		node2* temp = *head;
		if((*head) -> next !=NULL)			
			*head = (*head) -> next;
		// else
		// 	free(head);
		free(temp);
	}

	
}




