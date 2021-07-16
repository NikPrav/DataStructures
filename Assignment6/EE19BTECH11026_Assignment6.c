// The program ignores negative sign, and all other special characters
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct node{												// Basic Node Structure
	int key;
	struct node* parent;
	struct node* left;
	struct node* right;
};

typedef struct node node;

int Insert(node** Tree, int key){							// k = 1 => succesfull insertion
	int k = 0;												// k = 0  => insertion was not possible
	if((*Tree) -> key == -1){
		(*Tree) -> key = key;
		k = 1;
	}
	else if(key > (*Tree) -> key ){							// If key is greater than key of node,
		if((*Tree) -> right != NULL)
			k = Insert(&((*Tree) -> right), key);			// It is passed to the next node if the right node is non-empty
		else{
			(*Tree) -> right = (node*)malloc(sizeof(node));	// Otherwise, it is inserted at the right
			(*Tree) -> right -> key = key;
			(*Tree) -> right -> parent = (*Tree);
			k = 1;
		}
	}
	else if(key < (*Tree) -> key){							// If key is lesser, 
		if((*Tree) -> left != NULL)
			k = Insert(&((*Tree) -> left), key);			// It is passed to the left node if it is non-empty
		else{
			(*Tree) -> left = (node*)malloc(sizeof(node));	// Otherwise, it is inserted to the left
			(*Tree) -> left -> key = key;
			(*Tree) -> left -> parent = (*Tree);
			k = 1;
		}
	}
	return k;
}

void InOrder(node* Tree,FILE** fp){						// Function to print InOrder of the tree
	if(Tree -> key == -1){
		fprintf(*fp, "false");	
	}
	else{		
		if(Tree -> left != NULL){						// Visits the left node
			InOrder(Tree ->left,fp);
		}
		fprintf(*fp, "%d ", Tree -> key);				// Prints the node
		if(Tree -> right != NULL){
			InOrder(Tree -> right,fp);					// Visits the right node
		}
	}
}
void PreOrder(node* Tree,FILE** fp){					// Function to print PreOrder of the tree
	if(Tree -> key == -1){
		fprintf(*fp, "false");
	}
	else{
		fprintf(*fp, "%d ", Tree -> key);				// Prints the node
		if(Tree -> left != NULL){
			PreOrder(Tree ->left,fp);					// Visits the left node
		}
		
		if(Tree -> right != NULL){
			PreOrder(Tree -> right,fp);					// Visits the right node
		}
	}
}

void PostOrder(node* Tree, FILE** fp){					// Function to Print PostOrder of a tree
	if(Tree -> key == -1){
		fprintf(*fp, "false");
	}
	else{
		
		if(Tree -> left != NULL){						// Visits the left node
			PostOrder(Tree ->left,fp);
		}
		
		if(Tree -> right != NULL){						// Visits the right node
			PostOrder(Tree -> right,fp);
		}
		fprintf(*fp, "%d ", Tree -> key);				// Prints the node
	}
}

void Display(node* Tree){								// Displays acoording to the required output
	FILE* fp = fopen("output.txt","a");
	fprintf(fp, "Inorder: ");
	InOrder(Tree,&fp);
	fprintf(fp, "\n" );	
	fprintf(fp, "Preorder: ");
	PreOrder(Tree,&fp);
	fprintf(fp, "\n" );
	fprintf(fp, "Postorder: ");
	PostOrder(Tree,&fp);
	fprintf(fp, "\n" );
	fclose(fp);
}

int Findinpred(node *Tree){								// Finds the next inorder predecessor
	node* temp = Tree;
	while(temp -> right != NULL){						// By repeatedly going to the left for the least value
		temp = temp -> right;
	}
	return temp -> key;

}

int delete(node** Tree, int key){										// k = 0 deletion failed
	int k = 1;															// k = 1 yaay
	if((*Tree) -> key > key  && (*Tree) -> left != NULL) {				// If the given key is lesser,
		k = delete(&((*Tree) -> left), key);							// it is passed to the left, if it is non-empty
	}
	else if((*Tree) -> key < key   && (*Tree) -> right != NULL ){		// If the given key is greater,
		k = delete(&((*Tree) -> right), key);							// it is passed to the right
	} 
	else if((*Tree) -> key == key){										// In case they are equal
		if((*Tree) -> right == NULL && (*Tree) -> left == NULL){		// the node is checked whether it has one child or two
			if((*Tree) -> parent -> right  == (*Tree)){					// In case of no children, the node is just deleted 
				(*Tree) -> parent -> right = NULL;	
			}else
				(*Tree) -> parent -> left = NULL;				
			free(*Tree);
		}	
		else if((*Tree) -> left == NULL){								// In case the left node is empty, it is copied, as per the document
			(*Tree)  = (*Tree) -> right;
		} 
		else{															// Otherwise, the inorder predecessor is searched for
			key = Findinpred((*Tree) -> left);							// and the value is copied,
			(*Tree) -> key = key;										// making sure to delete the succesor
			k = delete(&((*Tree) -> left), key);
		}
	}
	else																// in case no children were found
		k = 0;
	return k;
}


int Find(node* Tree, int key){											// Finds a given node
	node* temp = Tree;
	int depth = 0;
	while(1){
		if(temp -> key < key && temp -> right != NULL){					// Same as before, key is greater, sedn to right
			temp = temp -> right;										// key is lesser, send to left
			++depth;													
		}else if(temp -> key > key && temp -> left != NULL){
			temp = temp -> left;
			++depth;
		}else if(temp -> key == key){									// If found, depth is returned
			break;
		}else{
			depth = -1;													// Otherwise, it is set to -1
			break;
		}
	}
	return depth;
}

int PrintSubTree(node* Tree, int key){									// Prints the subtree of the given key
	node* temp = Tree;
	int k = 0;															// k for error checking
	while(1){
		if(temp -> key < key && temp -> right != NULL){					// Same as before
			temp = temp -> right;
		}else if(temp -> key > key && temp -> left != NULL){
			temp = temp -> left;
		}else if(temp -> key == key){									// If found, it is displayed
			Display(temp);
			k = 1;
			break;
		}else{															// Otherwise, error is given
			break;
		}
	}
	return k;
}

int countNodes(node* Tree){												// Counts the total no. of nodes recursively
	int n = 1; 
	if(Tree -> left != NULL){
		n  += countNodes(Tree -> left);
	}
	if(Tree -> right != NULL){
		n += countNodes(Tree -> right);
	}
	return n;
}

void countImbalance(node* Tree, int key,FILE** fp){						// Counts the imbalance
	node* temp = Tree;
	int k = 0;
	while(1){
		if(temp -> key < key && temp -> right != NULL){					// Same deal as before
			temp = temp -> right;
		}else if(temp -> key > key && temp -> left != NULL){
			temp = temp -> left;
		}else if(temp -> key == key){
			k = 1;
			break;
		}else{
			break;
		}
	}
	if(k){																// If the key is found, the difference is calculated and printed						
		int left = countNodes(temp -> left);
		int right = countNodes(temp -> right);
		fprintf(*fp,"Left - Right = %d - %d = %d\n",left,right,left-right);
	}else{
		fprintf(*fp, "false\n");
	}

}

int toint(char str[]){
	int x = 0;
	int i = 0;
	while(str[i] != ' ' && str[i]!= '\0' && str[i]!= '\n'){
		x = x*10 + (str[i] - 48);
		++i;
	}
	return x;
}

void inputhandler(char x[], node** Tree){							// Handles the input to a BST from a file
	int i = 2;
	int buffer = 0;
	FILE* fp = fopen("output.txt","a");
	while(x[i] != '\n' && x[i] != '\0'){							// To extract each number from a given string
		buffer = 0;
		while(x[i] != ' ' && x[i] != '\n' && x[i] != '\0'){
			buffer = buffer*10 + (int)(x[i] - 48);
			++i;
		}
		if(!(Insert(Tree,buffer))){									// if input is not succesfull
			fprintf(fp,"false \n");
			fclose(fp);		
			return;
		}
		++i;
	}
	fprintf(fp, "true\n");											// If the input is succesfull
	fclose(fp);
}



void deletehandler(char x[], node** Tree){							// Handles deleting a from a BST and inputting to a file
	int i = 2;
	int buffer = 0;														
	FILE* fp = fopen("output.txt","a");
	while(x[i] != '\n' && x[i] != '\0'){							// To extract each number from a given string
		buffer = 0;
		while(x[i] != ' ' && x[i] != '\n' && x[i] != '\0'){
			buffer = buffer*10 + (int)(x[i] - 48);
			++i;
		}
		if(!(delete(Tree,buffer))){									// In case delete is not succesfull
			fprintf(fp,"false \n");
			fclose(fp);		
			return;
		}
		++i;
	}
	fprintf(fp, "true\n");											// In case it is succesfull
	fclose(fp);
}

void finder(char x[],node** Tree){								// Function used to find a key and output to a file 
	int i = 2;
	int buffer = 0;
	int k = 0;
	FILE* fp = fopen("output.txt","a");
	while(x[i] != '\n' && x[i] != '\0'){						// Handles each digit
		buffer = 0;
		while(x[i] != ' ' && x[i] != '\n' && x[i] != '\0'){
			buffer = buffer*10 + (int)(x[i] - 48);
			++i;
		}
		k = Find(*Tree,buffer);
		if(k == -1){											// If the given tree is not found
			fprintf(fp,"false \n");
			fclose(fp);
			return;
		}
		++i;
	}
	fprintf(fp, "true, Depth = %d\n",k);						// Otherwise, it gives true
	fclose(fp);
}

void printersub(char x[], node** Tree){							// Handles printing of subtrees onto a file
	int i = 2;
	int buffer = 0;
	int k = 0;
	FILE* fp = fopen("output.txt","a");
	while(x[i] != '\n' && x[i] != '\0'){						// To extract each number from a given string
		buffer = 0;
		while(x[i] != ' ' && x[i] != '\n' && x[i] != '\0'){
			buffer = buffer*10 + (int)(x[i] - 48);
			++i;
		}
		k = PrintSubTree(*Tree,buffer);
		if(!k){													// In case the key is not found
			fprintf(fp,"false \n");
			fclose(fp);
			return;
		}
		++i;
	}
	fclose(fp);												
}

void printerimb(char x[], node* Tree){							// Prints the imbalance at a key onto a file
	int i = 2;
	int buffer = 0;
	int k = 0;
	FILE* fp = fopen("output.txt","a");
	while(x[i] != '\n' && x[i] != '\0'){						// To extract each number from a given string
		buffer = 0;
		while(x[i] != ' ' && x[i] != '\n' && x[i] != '\0'){
			buffer = buffer*10 + (int)(x[i] - 48);
			++i;
		}
		countImbalance(Tree,buffer,&fp);				
		++i;
	}	
	fclose(fp);
}


int ReadFile(char name[]){										// Reads from a file, and chooses the dfunction accordingly
	node* Tree = (node*)malloc(sizeof(node));
	Tree -> left = NULL;
	Tree -> right = NULL;
	Tree -> parent = NULL;
	Tree -> key = -1;
	FILE* fp = fopen(name,"r");
	char buffer[100];
	fgets(buffer,100,fp);
	int lines = toint(buffer);
	for (int i = 0; i < lines; ++i){
		if(fgets(buffer,100,fp) == NULL){
			return 0;
		}
		int j = 0;
		switch(buffer[0]){								// Choosing which function to use, according to the first character of each line 
			case '1':
					inputhandler(buffer,&Tree);
					break;
			case '2':
					deletehandler(buffer,&Tree);
					break;
			case '3':
					finder(buffer,&Tree);
					break;
			case '4':
					Display(Tree);
					break;
			case '5':
					printersub(buffer, &Tree);
					break;
			case '6':
					printerimb(buffer, Tree);
					break;
		}
	}
	fclose(fp);
	return 1;
}



void main(int argc, char const *argv[])
{
	char name[]="input6.txt";
	FILE* fp = fopen("output.txt", "w");					// To clear the output file
	fclose(fp);
	ReadFile(name);											
}