// C/C++ program to generate Worst Case of Merge Sort 
#include <stdlib.h> 
#include <stdio.h> 
  
// Function to print an array 
void printArray(int A[], int size) 
{ 
    FILE *fp;
    fp=fopen("permMS.txt","a");


    for (int i = 0; i < size; i++){ 
         fprintf(fp,"%d",A[i]);
        printf("%d ", A[i]); 
    }

    fclose(fp);
  
    printf("\n"); 
} 
  
// Function to join left and right subarray 
int join(int arr[], int left[], int right[], 
          int l, int m, int r) 
{ 
    int i; // Used in second loop 
    for (i = 0; i <= m - l; i++) 
        arr[i] = left[i]; 
  
    for (int j = 0; j < r - m; j++) 
        arr[i + j] = right[j]; 
} 
  
// Function to store alternate elemets in left 
// and right subarray 
int split(int arr[], int left[], int right[], 
          int l, int m, int r) 
{ 
    for (int i = 0; i <= m - l; i++) 
        left[i] = arr[i * 2]; 
  
    for (int i = 0; i < r - m; i++) 
        right[i] = arr[i * 2 + 1]; 
} 
  
// Function to generate Worst Case of Merge Sort 
int generateWorstCase(int arr[], int l, int r) 
{ 
    if (l < r) 
    { 
        int m = l + (r - l) / 2; 
  
        // create two auxillary arrays 
        int left[m - l + 1]; 
        int right[r - m]; 
  
        // Store alternate array elements in left 
        // and right subarray 
        split(arr, left, right, l, m, r); 
  
        // Recurse first and second halves 
        generateWorstCase(left, l, m); 
        generateWorstCase(right, m + 1, r); 
  
        // join left and right subarray 
        join(arr, left, right, l, m, r); 
    } 
} 
  
// Driver code 
int main() 
{ 
    // Sorted array 
    int arr[10000] ;
    for(int i=0; i<10000 ; ++i )
    {
        arr[i]=i;
    } 
    int n = sizeof(arr) / sizeof(arr[0]); 
  
    printf("Sorted array is \n"); 
    printArray(arr, n); 
  
    // generate Worst Case of Merge Sort 
    generateWorstCase(arr, 0, n - 1); 
  
    printf("\nInput array that will result in "
             "worst case of merge sort is \n"); 
    printArray(arr, n); 
  
    return 0; 
} 