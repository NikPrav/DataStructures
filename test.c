//The DNA Molecule Code, Written by Nikhil P
#include <stdio.h>
#include <string.h>

typedef struct node{
	char molecule;
	struct node* hor;
	struct node* ver;
};

void createMolecule(char alphain[],char betain[]);   // To create a molecule
void insert(node* head,int pos); // To insert to a specific position of an element
void delete(node* head,int pos); // To delete a specific element of an array
void split(node* head);		   // To split the chain
void printChain(node* head);	   // To print a chain

//Main Function
int main(int argc, char const *argv[]){
	int choice;
	int flag=1;
	char alphain[30],betain[30];
	while(flag){
		printf("##DNA Database\n" );
		printf("##MENU\n");
		printf("1)Create a new Molecule\n");
		printf("2)Insert into existing molecule\n");
		printf("3)Delete from existing molecule\n");
		printf("4)Split a chain\n");
		printf("5)Print a chain\n");
		printf("6)Print all chains\n");
		printf("7)Exit\n");
		printf("Enter your choice:\n");
		scanf("%d",&choice);
		switch(choice){
			case 1:
				   
				   printf("Enter the alpha chain, seperating unit with a comma:\n"); 
				   gets(alphain);				   
				   printf("Enter the beta chain, seperating unit with a comma:\n");
				   gets(betain);
				   createMolecule(alphain,betain);
				   break;

		}
	}
	return 0;
}



void createMolecule(char str[]){
	//struct 

}