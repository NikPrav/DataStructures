#include <stdio.h>
#include <stdlib.h>

// Node structure for the stack
struct node{
	int p;
	int r;
	int ln;
	struct node* next;
};

typedef struct node node;

void display(int *ar, int s);								// TO display the array
void quicksort(int *ar, int p, int r);						// Recursive Quicksort FUnction
int partition(int *ar, int p, int r);						// Partion function for quicksort
void swap(int* i, int*j);									// Swaps two numbers
void push(int p,int r,int ln);								// Pushes onto a stack
void pop();													// Pops from a stack
void displaystack();										// Displays a stack
int length();												// Gives the length of a stack
		
node* head;

int main(){
	int ar[100];	
	int s;

	printf("Enter the size of array:\n");					// Inputting the array
	scanf("%d",&s);

	printf("Enter elements:\n");
	for (int i = 0; i < s; ++i)
	{
		scanf("%d",&ar[i]);
	}

	printf("Unsorted array:\n");
	display(ar,s);
	printf("\n\n");	
	
	time_t t;
	srand((unsigned) time(&t));								// For Random Nos, seeds using time
	
	displaystack();											// Initial Display of stack
	push(0,s-1,__LINE__);
	quicksort(ar,0,s-1);
	pop();

	printf("\n\n");
	printf("Sorted Array:\n");
	display(ar,s);			
	return 0;

}

void display(int *ar, int s){								// To display the array
	
	for(int i=0;i<s;++i){
		printf("%d\t",ar[i]);
	}
	printf("\n");
}

void quicksort(int *ar, int p, int r){
	int q;	
	displaystack();											// Displays the stack after push

	if(p<r){
		q = partition(ar,p,r);								// Calls the Partition code 

		push(p,q-1,__LINE__);								// Pushes the Element, giving the line number
		quicksort(ar,p,q-1);								// Calls itself recursively, with the limits being the left of the pivot
		pop();												// Pops from the stack after execution
		displaystack();										// Displays stack after popping

		push(q+1,r,__LINE__);								// Same as above, but with the limits being the right of the pivot
		quicksort(ar,q+1,r);
		pop();
		displaystack();
	}
	// displaystack();
}


// Function to handle the partion part of QuickSort
int partition(int *ar, int p, int r){

	int pi =p + rand() % (r-p+1);							// Selects an element in random
	swap(&ar[pi],&ar[r]);									// And swaps it with the last element => Randomised Quicksort
	// int pi = r;
	int pivot = ar[r];										// Pivot element is the last element
	int i = p-1;											// i => Stores the greatest position of element lesser than pivot
	
	while(1){
		for(int j=p;j<=r;++j){								// j => iterates along the array
			if(ar[j]<pivot){								// If an element is lesser than pivot
				++i;										// i increases 
				swap(&ar[i],&ar[j]);						// and the element swaps
			}
		}
		++i;
		swap(&ar[i],&ar[r]);								// swaps the pivot and the last element
		return i;											// returns the position of the pivot
	}
}

void swap(int* i, int*j){
	int temp = *i;
	*i = *j;
	*j = temp;
}

// Function to push values to the stack
void push(int p, int r, int ln){
	node* temp = (node*)malloc(sizeof(node));
	temp -> p = p;
	temp -> r = r;
	temp -> ln = ln;
	temp -> next = NULL;
	// Error in case memory is full
	if(temp == NULL){
		printf("Memory Full\n" );

	}
	else{
		
		if(head == NULL){									// The usual Linked List insert code
			head = temp;									// which inserts to the last position
			// printf("DEBUG: Pos1\n");
		}
		else
			temp -> next = head;
			head = temp;
	}

}

void pop(){
	
	if(head == NULL){										// Error Handling in case stack is empty
		printf("No Value left to pop\n");
	}
	else{
		node* temp = head;
		if((head) -> next !=NULL)							// Moves by one to delete the element at te top
			head = (head) -> next;
		
		
		free(temp);											// Frees the memory after deleting 
	}

	
}

int length(){
	int c=0;
	
	if(head != NULL){ 										// Checks whether an element exists or not
		struct node* temp=head;
		while(temp -> next != NULL){						// Traverses through the chain and counting each element
			temp = temp -> next;
			++c;
		}
	}
	else
		return 0;
	
	return c;
}

void displaystack(){										// Displays a stack,as given

	if(head != NULL){
		node* temp = head;
		int s = length();
		for (int i = 0; i < s; ++i)							
		{
			printf("\t");
		}
		printf("{ ");
		while(temp -> next != NULL){
			printf("( %d, %d, %d ), ",temp -> p,temp -> r,temp -> ln );
			temp = temp -> next;
		}	
		printf("( %d, %d, %d ) ",temp -> p,temp -> r,temp -> ln );
		printf("}\n");	
	}
	else{
		printf("{ } \n");									// If the head is empty, display accordingly
		printf("\n");
	}
	

}
