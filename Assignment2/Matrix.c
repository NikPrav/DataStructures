void createMolecule (/char alphain[]){
	struct node* atemp;
	struct node* btemp;	
	int i=strlen(alphain)-1;
    while (i>=0){
    	atemp=malloc(sizeof(struct node));
		btemp=malloc(sizeof(struct node));
    	atemp->hor=NULL;
	    btemp->hor=NULL;

		if (alphain[i]==',')
			--i;
		else {

			atemp->molecule=alphain[i];
			btemp -> molecule = conju(alphain[i]);
			// printf ("Paripadi nadakkuva makkale  \n");
			if(alphahead==NULL){
				atemp -> ver = btemp;
				btemp -> ver = atemp;
				alphahead=atemp;
				betahead=btemp;
				// printf ("Paripadi thodangi  \n");
			}
			else {
				atemp -> ver = btemp;
				btemp -> ver = atemp;
				atemp->hor=alphahead;
				alphahead=atemp;
				btemp->hor=betahead;
				betahead=btemp;
				// printf ("Enta mwona mass  \n");
			}
			--i;
			// printf ("alphahead %c  \n",alphahead->molecule);
			// printf ("betahead %c  \n",betahead->molecule);
			//


		}    
    }
 //    if(alphahead != NULL)
	// 	printf("Enthokkayo onde mwonee \n" );
	// else
	// 	printf("oombi \n" );
    // printf ("Functioninu erangi \n");
    // free(atemp);
    // free(btemp);
    return;
}

void printChain (int eid){/*struct node* alphahead, struct node* betahead*/
	int c=0;
	struct DNA* temp=(struct DNA*)malloc(sizeof(struct DNA));
	struct node* atemp;
	struct node* btemp;
	temp =elements;
	int flag =1;
	while(temp ->next != NULL && flag){
		if(temp -> id == eid)
			flag = 0;
		else
			temp=temp -> next ;
	}
	if(temp -> id == eid )
	{
		atemp = temp -> ahead;
		btemp = temp -> bhead;


	// atemp=
	// btemp=;

	// printf ("Functionil Kerii \n");

		while(atemp->hor != NULL){


			// printf ("Loopil Kerii \n");
			printf("%c-",atemp -> molecule );
			atemp = atemp->hor;
			++c;
		}

		//printf ("Loopil Kerathe poi \n");
		printf("%c \n",atemp -> molecule );
		
		for (int i = 0; i <= c; ++i)	{
			printf("| ");
		}
		printf("\n");
		while(btemp->hor != NULL){
			printf("%c-",btemp -> molecule );
			btemp=btemp->hor;
		}
		printf("%c \n",btemp -> molecule );
		// printf ("Functioninu erangi \n");
		// free(atemp);
	 //    free(btemp);
	}
	else
		printf("Molecule not found\n");
	return;

}

