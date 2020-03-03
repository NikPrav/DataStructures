// The Matrix code, written by Nikhil P
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct node{
	int val;
	struct node* left;
	struct node* right;
	struct node* up;
	struct node* down;
};

typedef struct node node;
void printMat (node** head);
void matfromfile(char fname[], node** head);
void iniptr(node** ptr);


int main()
{
	char fname[]="test.txt";
	int i =0;
	node* head = (node*) malloc(sizeof(node));

	printf("Enter filename to read matrix from:\n");
	// scanf("%s",fname);	
	matfromfile(fname, (&head));
	printf("Functioninu erangi\n");

	printMat(&head);
	return 0;
}

void matfromfile(char fname[], node** head){
	printf("Functionil kerii\n");
	
	FILE *fp;
 	fp=fopen(fname,"r");
 	if(fp == NULL){
 		printf("Moonji Mone\n");
 	}
 	int buff=0;
 	char s[60];
	fscanf(fp, "%s", s);
	printf("%s\n",s );
	int i=0;
	node* temp = malloc(sizeof(node));
	iniptr((&temp));
	while(s[i] != ';'){
		buff=0;
		temp =  malloc(sizeof(node));
		printf("Ithalla scene\t %d\n",i);
		while(s[i] != ';' && s[i] != ','){
			buff= buff*10 + (s[i] - '0');
			++i;	
		}
		if(s[i] == ',')
			++i;

		printf("Ivide scene illa \t %d\n",i);

		temp -> val = buff;
		if(*head != NULL){
			temp -> left = *head;
			(*head) -> right = temp;
			*head = temp;
			printf("Everything okay\n");
		}
		else
		{
			printf("Scene ivide kaanm\n");
			*head = temp;

		}
		printf("ividem scene illa\n");
		
	
	}

	fclose(fp);
	return;


}


void iniptr(node** ptr){
	(*ptr) -> left = NULL;
	(*ptr) -> right = NULL;
	(*ptr) -> up = NULL;
	(*ptr) -> down = NULL;
}

void printMat (node** head){/*struct node* alphahead, struct node* betahead*/
	int c=0;
	node* temp=*head;
	if(*head == NULL){
		printf("moonji \n");
	}
	char dump[10];

	while(temp -> left != NULL){
			printf("%d-",temp -> val );
			temp = temp->left;
			++c;
			//  gets(dump);
		}

		//printf ("Loopil Kerathe poi \n");
		printf("%d \n",temp -> val );
	return;

}

