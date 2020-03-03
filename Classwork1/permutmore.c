#include<stdio.h>
#include<stdlib.h>

int Arr[]={1,2,3,4,5,6,7,8,9,10,11,12};
int size=sizeof(Arr)/sizeof(Arr[0]);
int * rem(int *array,int index ) {

   int *r=malloc(4*size); 
   for(int i=0;i<size-1;++i)
   {
        
        if(i<index)
            r[i]=array[i];
        else
            r[i]=array[i+1];  
   }
   r[2]=0;


   return r;
}

void fout(int *r){
    FILE *fp;
    fp=fopen("permsv2.txt","a");
    
    for(int i=0;i<size;++i){
        fprintf(fp,"%d",r[i]);
        fprintf(fp," ");
        printf("%d",r[i]);
        printf(" ");
    }
    fprintf(fp,"\n");
    printf("\n");
    fclose(fp);
}

void perm(int *r,int *ar, int s,int index){
    int *temp;
    
    for(int i=0;i<s;++i){
        r[index]=ar[i];
        //printf("i %d s %d ",i,s);
        //printf("\n");
        //out(ar);
        //if(s==9)
        //printf("%d",i);
        temp=rem(ar,i);
        //out(ar);
        //out(temp);        

        if(s==1)
            fout(r);
        else
            perm(r,temp,s-1,index+1);
    }
    return;
       
    
}

void main()
{

 
    //printf("%d",sizeof(Ar));
    int *array=Arr;
    int *r=malloc(sizeof(Arr));
    perm(r,array,size,0);

    //r=rem(array,3);
    //out(r);
    
}
