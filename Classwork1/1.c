 #include "LinkedList.h"
#include<stdio.h>
#include<stdlib.h>


void main()
{
    int no=0;
    printf("Enter the number of elements in the linked list:");
    scanf("%d",&no);
    printf("DEBUG: Pos3 \n");
    struct List L;
    int el=0;
    L=createList();
    
    
    for(int i=0;i<no;++i)
    {
        printf("DEBUG: Pos2 %d\n",i);
        Insert(&L,i,0);

    }
    PrintList(&L);

}