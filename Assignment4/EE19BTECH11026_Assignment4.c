#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
// Node structure for the stack
struct node{
	char *name;
	int t;
	struct node* left;
	struct node* right;
};


typedef struct node node;


// char* ccint(char ch[],int i);
int intlen(int a);												// To calculate the length of an integer
void displayqueue(node **head);									// To display a queue								
void advance(node** head);										// TO advance the head of the queue by 1
void dequeue(node** head);										// To remove from the head of the queue
void enqueue(node** head,char* name, int t);					// To add to the tail of the queue

void main(int argc, char const *argv[])
{
	srand(time(0));								 				// Seeds  the random no. generator
	node* head = (node*)malloc(sizeof(node));					
	head -> left = NULL;
	head -> right = NULL;
	char ch[700][10];											// Array that stores the names of nodes
	int j;														
	// ch[0] = 'J';
	// char *x;
	int i;								
	int sz = 0;													// Stores the total number of elements in the queue
	int clk = 0;												// Emulates the clock of a processor
	for(i = 1; i <= 100; ++i){									// Loop to initialise everything
		int s = intlen(i);
		int d = 0;
		ch[i-1][0] = 'J';
		j = i;
		while(j != 0){											// To covert the integer to a character
			d = j%10;
			ch[i-1][s] = (char)(d + 48);
			--s;
			j = j/10;
		}
		ch[i-1][intlen(i)+1] = '\0';
		enqueue(&head,ch[i-1],rand()%300);						// Creates a new queue element
		++sz;													// Simultaneously increments the size
	}
	printf("Initial Queue:\n");									// Initial Queue
	displayqueue(&head);									
	while (sz>0){												// THe loop executes till all of the queue elements are dequeued
		++clk;
		(head) -> t --;											// Each clock cycle(i.e, each loop) decreases the time of execution needed
		if((head) -> t <= 0){									// for the given element by one
			dequeue(&head);										// Checks whether the head element has finished executing,
			--sz;												// if so, it dequeues it
		}




		if(clk%50 == 0){										// At every 50 virtual seconds, the queue is displayed
			advance(&head);									
			printf("Queue at t=%d: ",clk );
			displayqueue(&head);
		}
		int k = 7 - (int)clk/200;
		int x = pow(2,k);
		int c=0;
		if(clk%200 == 0 && k>=0){								// At every 200 virtual seconds, elements are added to the queue as given
			printf("*****%d passed and added %d more jobs at the end\n",clk,x);
			while(c < x){
				++i;
				++c;
				int s = intlen(i);
				int d = 0;
				ch[i-1][0] = 'J';
				j = i;
				while(j != 0){
					d = j%10;
					ch[i-1][s] = (char)(d + 48);
					--s;
					j = j/10;
				}
				ch[i-1][intlen(i)+1] = '\0';
				enqueue(&head,ch[i-1],rand()%300);
				++sz;
				// printf("%d\n",i);
			}	
			printf("Queue after adding:\n");
			displayqueue(&head);
		}
	}



}


// Function to enqueue values to a queue
void enqueue(node** head,char* name, int t){
	node* temp = (node*)malloc(sizeof(node));
	temp -> name = name;
	temp -> t = t;
	temp -> left = NULL;
	temp -> right = NULL;
	// Error in case memory is full
	if(temp == NULL){
		printf("Memory Full\n" );

	}
	else{
		
		if((*head) -> left == NULL){									// The usual Linked List insert code,but with 2 pointers
			*head = temp;		
			(*head) -> left = *head;
			(*head) -> right = *head;									// which inserts to the last position
		}
		else
			temp -> left = (*head) -> left;
			temp -> right = *head;
			(*head) -> left -> right = temp;
			(*head) -> left = temp;
	}

}


// Function to dequeue values from a queue
void dequeue(node** head){
	
	if((*head) -> left == NULL){									// Error Handling in case queue is empty
		printf("No Value left to dequeue\n");
	}
	else{
		node* temp = *head;
		if((*head) -> right !=NULL){							// Moves by one to delete the element at the top
			*head = (*head) -> right;
			temp -> left -> right = *head;
			(*head) -> left = temp -> left;
			free(temp);											// Frees the memory after deleting 
		}
		// temp = NULL;										
	}

}

// Advances the head of the queue to the next element 
void advance(node** head){
	*head = (*head) -> right;
}

void displayqueue(node **head){										// Displays the queue,as given

	if(head != NULL){
		node* temp = *head;
		printf("%s:%d;  ",temp -> name,temp -> t);
		temp = temp -> right;
		while(temp != *head){
			printf("%s:%d; ",temp -> name,temp -> t);
			temp = temp -> right;
		}
		printf("\n");
	}
	

}


int intlen(int a){													// Finds the length of an integer in terms of digits
	int s = 0;
	while(a != 0){
		a=a/10;
		++s;
	}
	return s;
}
