// Ignores anything other than numerals, spaces, end of line characters and /0
// Ignores if two nos are given in the same line(i.e cannot insert 2 nos at once)
// Since only positive nos are allowed, 0 is discarded
// These are all done as error handling procedures were not detailed, and I didn't want to add anything to the program that would change its supposed output.

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>


struct node{												// Basic Node Structure
	int key;
	struct node* parent;
	struct node* left;
	struct node* right;
};

typedef struct node node;
char buf[100];

node* decider(node* Tree,node** Tree2, int key);

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

int countNodes(node* Tree){												// Counts the total no. of nodes recursively
	int n = 1;
	if(Tree -> key == -1)
		return 0; 
	if(Tree -> left != NULL){
		n  += countNodes(Tree -> left);
	}
	if(Tree -> right != NULL){
		n += countNodes(Tree -> right);
	}
	return n;
}



node* Insertrec(node* Tree,node** Tree2, int key){							// Function that inserts recursively
	if(Tree -> key == -1){
		Tree -> key = key;
	}
	else if(key > Tree -> key){												// the algorithm being the same as the last assignment
		if(Tree -> right != NULL){
			Tree -> right = decider(Tree -> right, Tree2, key);				// the only change being that there is 
		}else{																// a decider function in between 
			node* tmp = (node*)malloc(sizeof(node));
			tmp -> key = key;
			tmp -> left = NULL;
			tmp -> right = NULL;
			tmp -> parent = Tree;
			Tree -> right = tmp;
			return Tree;
		}
	}else if(key < Tree -> key){
		if(Tree -> left != NULL){
			Tree -> left = decider(Tree -> left, Tree2,key);
		}else{
			node* tmp = (node*)malloc(sizeof(node));
			tmp -> key = key;
			tmp -> left = NULL;
			tmp -> right = NULL;
			tmp -> parent = Tree;
			Tree -> left = tmp;
			return Tree;
		}
	}else
		return Tree;
}


node* GoToRoot(node** Tree){									// Function that goes to the root of the given trees
	node* tmp = (*Tree);
	while(tmp -> parent != NULL){
		tmp = tmp -> parent;
	}
	return tmp;
}

node* maketree(node** Tree, node** Tree2, int key){				// Makes a tree from 2 given trees
	node* temp = (node*)malloc(sizeof(node));
	node* temp1;
	node* temp2;
	temp1 = GoToRoot(Tree);										// Goes to the roots of the given trees
	temp2 = GoToRoot(Tree2);			
	temp -> parent = NULL;
	temp -> left = NULL;
	temp -> right = NULL;
	temp -> key = key;

	if(temp1 -> key >=0){										// Checking whether any tree is empty or not
		temp -> left = temp1;
		temp1 -> parent = temp;
	}	
	if(temp2 -> key >= 0){
		temp -> right = temp2;
		temp2 -> parent = temp;
	}
	return temp;												// Returns the final tree
}

void AddToTree(node** Tree,node** Tree2){						// Adds one tree to another tree
	node* temp = (*Tree2);										// by calling the insertrec function
	temp = GoToRoot(&temp);
	temp = Insertrec(temp,Tree2 , (*Tree) -> key);
	if((*Tree) -> left != NULL){
		AddToTree(&((*Tree) -> left),Tree2);
	}
	if((*Tree) -> right != NULL){
		AddToTree(&((*Tree) -> right),Tree2);
	}
	// free(Tree);
}


// Does not bother with pre-existing nodes
// Does not bother with pre-existing nodes
node* Insertatroot(node* Tree,node** Tree2,int key){			// The Insert at root function
	if((Tree) -> key == -1){
		(Tree) -> key = key;
	}
	else if(key > Tree -> key){									// It moves on if the current node has a value lesser than the key
		if((Tree) -> right == NULL){							// stopping at the end to make the final tree
			Tree = maketree(&Tree,Tree2,key);
		}
		else
		 	Tree = Insertatroot(Tree -> right,Tree2,key);			// The "Moving on" code
	}
	else if(key < (Tree) -> key){								// If the key is lesser,
		node* temp = (Tree);
		while(key < (temp) -> key && (temp) -> left != NULL){	// a node with value lesser than key is searched for
			(temp) = (temp) -> left;
		}
		if(key > (temp)-> key){									// If there exists such a node,
			temp -> parent -> left = NULL;						// then, this node is broken off
			temp -> parent = NULL; 
			AddToTree(&Tree,Tree2);								// and the other tree is added to tree2
			if((Tree) -> parent != NULL){						// taking care to join the original node's parent 
				(Tree) -> parent -> right = temp;				// (if it exists) and the other found node
				temp -> parent = (Tree) -> parent;
				(Tree) -> parent = NULL;				
			}
			(Tree) = temp;										// The tree carries all the values lesser than the key
			Tree = Insertatroot(Tree,Tree2,key);				// It is then passed to itself.
		}else{			
			if(Tree -> parent != NULL){							// Here, we can see that the insertatroot function is
				Tree = Tree -> parent;							// is called instead of the decider function
				temp = Tree;									// This is because of how the function is supposed to work
				AddToTree(&(Tree -> right),Tree2);				// It adds at the root of the initial given node
				Tree -> right = NULL;							// This is taken care of by the decider function
				Tree = maketree(&Tree,Tree2,key);
			}
			else{
				Tree = maketree(Tree2,&Tree,key);
			}
		}
	}
	return Tree;
}



node* join(node* left, node* right){							// The join function, as given in the question
	int m = countNodes(left);
	int n = countNodes(right);
	int r = random()%(m+n-1);
	// printf("Joining %d and %d naw\n",left->key,right -> key);
	if(r < m){
		if(left -> right != NULL){								// with additional cases, in case of null nodes
			left -> right = join(left -> right,right);
		}
		else{													// that follow basically the same algorithm
			left -> right = right;
			right -> parent = left;
		}
		return left;
	}
	else {
		if(right -> left != NULL){			
			right -> left = join(left, right -> left);
		}
		else{
			right -> left = left;
			left -> parent = right; 
		}
		return right;
	}	
}



node* delete(node* Tree, int key){									// Function that deletes a node
	if(key > Tree -> key && Tree -> right != NULL){					// the key is greater and the right node exists
		Tree -> right = delete(Tree -> right,key);
	}
	else if(key < Tree -> key && Tree -> left != NULL){				// The key is lesser and the left node exists
		Tree -> left = delete(Tree -> left, key);
	}
	else if(key == Tree -> key){									// The key is found
		if(Tree -> right == NULL && Tree -> left == NULL){			// If the node is a leaf
			if(Tree -> parent != NULL){								// the parent is checked
				free(Tree);											// and accordingly treated
				return NULL;
			}
			else{
				Tree -> key = -1;									// If it is a starting node
				return Tree;
			}

		}else if(Tree -> right == NULL){							// In case the right node is null
			if(Tree -> parent != NULL)								// the tree is shifted(basically how the join function works)
				Tree -> left -> parent = Tree -> parent;
			else
				Tree -> left -> parent = NULL;						// When is a root 
			node* temp = Tree -> left;
			free(Tree);
			return temp;
		}else if(Tree -> left == NULL){								// Same as above, but for the left node
			if(Tree -> parent != NULL)
				Tree -> right -> parent = Tree -> parent;
			else
				Tree -> right -> parent = NULL;
			node* temp = Tree -> right;
			free(Tree);
			return temp;
		}else{
			node* temp = join(Tree -> left, Tree -> right);			// In case both are available
			if(Tree -> parent != NULL)								// Checked wheter it is a root or not
				temp -> parent = Tree -> parent;
			else
				temp -> parent = NULL;								// to prevent segmentation faults
			free(Tree);
			return temp;
		}
	}else
	return Tree;

}

node* inputhandler(char x[], node* Tree){							// Handles the input to a BST from a file
	int i = 2;
	int buffer = 0;
	node* Tree2 = (node*)malloc(sizeof(node));
	Tree2 -> left = NULL;
	Tree2 -> right = NULL;
	Tree2 -> parent = NULL;
	Tree2 -> key = -1;
	FILE* fp = fopen("output.txt","a");
	while(x[i] != '\n' && x[i] != '\0'){	
		int n = countNodes(Tree);									// To extract each number from a given string
		buffer = 0;
		while(x[i] != ' ' && x[i] != '\n' && x[i] != '\0'){
			if(x[i] < '0' || x[i] > '9'){
				++i;
				continue;
			}

			buffer = buffer*10 + (int)(x[i] - 48);
			++i;
		}
		if(buffer)													// Checking if any number was given in the line
			Tree = decider(Tree,&Tree2,buffer);
		else{
			fprintf(fp, "false\n");
			fclose(fp);
			return Tree;
		}
		++i;
		if(countNodes(Tree) == n){									// if input is not succesfull
			fprintf(fp, "false\n");
			fclose(fp);
			return Tree;
		}
	}
	fprintf(fp, "true\n");											// If the input is succesfull
	fclose(fp);
	return Tree;
}

node* decider(node* Tree,node** Tree2, int key){					// Function that chooses whether to insert at root or not
	int n = countNodes(Tree);
	int r = 0;
	if(n > 0)				
		r = rand()%(n);													// Calculates a random possibility
	else{
		node* tmp = Insertrec(Tree,Tree2,key);						// In case the tree is empty, to prevent divison by zero error 
		return tmp;
	}
	if(r < n -1){
		return Insertrec(Tree,Tree2,key);							// Case 1, considering major amount of case
	}
	else{															// Otherwise, the insertatroot function
		node* tmp = NULL;											// is called at that root itself
		if(Tree -> parent != NULL)									// , inserting a new node at that root
			tmp = Tree -> parent;
		Tree -> parent = NULL; 
		printf("%d\n", Tree ->key );
		Tree =  Insertatroot(Tree,Tree2,key);
		Tree -> parent = tmp;
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

node* deletehandler(char x[], node* Tree){							// Handles deleting a from a BST and inputting to a file
	int i = 2;
	int buffer = 0;														
	FILE* fp = fopen("output.txt","a");							// To extract each number from a given string
		int n = countNodes(Tree);
		buffer = 0;
		while(x[i] != ' ' && x[i] != '\n' && x[i] != '\0'){
			if(x[i] < '0' || x[i] > '9'){
				++i;
				continue;
			}
			buffer = buffer*10 + (int)(x[i] - 48);
			++i;
		}
		if(buffer)											// Checking if any number was given in the line
			Tree = delete(Tree, buffer);
		else{
			fprintf(fp, "false\n");
			fclose(fp);
			return Tree;
		}
		
		if(countNodes(Tree) == n){
			fprintf(fp, "false\n");
			fclose(fp);
			return Tree;
		}
		++i;
	
	fprintf(fp, "true\n");												// In case it is succesfull
	fclose(fp);
	return Tree;
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
void finder(char x[],node** Tree){								// Function used to find a key and output to a file 
	int i = 2;
	int buffer = 0;
	int k = 0;
	FILE* fp = fopen("output.txt","a");
		while(x[i] != ' ' && x[i] != '\n' && x[i] != '\0'){
			if(x[i] < '0' || x[i] > '9'){
				++i;
				continue;
			}
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
	
	fprintf(fp, "true, Depth = %d\n",k);						// Otherwise, it gives true
	fclose(fp);
}

void printersub(char x[], node** Tree){							// Handles printing of subtrees onto a file
	int i = 2;
	int buffer = 0;
	int k = 0;
	FILE* fp = fopen("output.txt","a");						// To extract each number from a given string
		while(x[i] != ' ' && x[i] != '\n' && x[i] != '\0'){
			if(x[i] < '0' || x[i] > '9'){
				++i;
				continue;
			}
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

void main(){										// Reads from a file, and chooses the dfunction accordingly
	char input[] = "input.txt";
	char output[] = "output.txt";
	node* Tree = (node*)malloc(sizeof(node));
	Tree -> left = NULL;
	Tree -> right = NULL;
	Tree -> parent = NULL;
	Tree -> key = -1;
	FILE* fp = fopen(input,"r");
	FILE* fop = fopen(output,"w");	
	fclose(fop);
	char buffer[100];
	fgets(buffer,100,fp);
	int lines = toint(buffer);
	for (int i = 0; i < lines; ++i){
		if(fgets(buffer,100,fp) == NULL){
			printf("Annachi lines exhausted\n");
		}
		int j = 0;
		switch(buffer[0]){								// Choosing which function to use, according to the first character of each line 
			case '1':
					Tree = inputhandler(buffer,Tree);
					break;
			case '2':
					Tree = deletehandler(buffer,Tree);
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
}


