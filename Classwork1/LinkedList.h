#include<stdio.h>
#include<stdlib.h>

typedef struct node Node;
typedef struct List List;




struct node
{
    int data;
    struct node* next;
};
struct List{
    struct node* head;
    int size;
};


struct List createList()
{
    struct List L;
    L.head=malloc(sizeof(struct node));
    L.size=0;
    return L;
};
void PrintList(struct List *L){
    struct node* temp= L->head;
    printf("DEBUG: PosPrint \n");
    for(int i=0;i<L->size;++i){
        printf("%d \n",temp->data);
        temp=temp->next;
        printf("DEBUG: PosPrintLoop %d \n",i);
    }
    printf("%c \n",temp->data);
    // free(temp);

}

void Insert(struct List *L, int E, int pos){
    printf("DEBUG: Pos1 \n");
    printf("Size: %d \n",L->size);
    if(pos<=L->size){
        struct node* El;
        struct node* temp;
        struct node* temp1;
        struct node X;

        X.data=E;
        // X.next=NULL;
        printf("DEBUG: Pos4 \t");
        
        El=&X;
        temp=L->head;
        temp1=L->head->next;
        if(pos==0)
        {
            
            El->next=L->head;
            L->head->next=El;
                                
        }
        else
        if(pos<L->size)
        {           
        
            for(int i=1;i<pos;++i)
            {
                temp=temp1;
                temp1=temp1->next;
            }
            El->next=temp1;
            temp->next=El;
             
        }
        else
        {
            for(int i=0;i<pos;++i)
            {
                temp=temp->next;
            }
            temp->next=El;

            
        }
        // free(temp);
        // free(temp1);
        // free(El);
        // free(temp1);
        
    }   
    else
    {
        printf("Invalid, List out of Bounds");
        L->size-=1;
    }
    L->size+=1;
    PrintList(L);
    // return(L);
    
}


void del(){
 
}

int Find(struct List* L,int RollNumberToBeFound){

}



void FindAndDelete(struct List* L,int RollNumberToBeRemoved){

}