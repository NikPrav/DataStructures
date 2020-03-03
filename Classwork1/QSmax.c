/* C implementation QuickSort */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <stdlib.h>

// A utility function to swap two elements 
void swap(int* a, int* b) 
{ 
	int t = *a; 
	*a = *b; 
	*b = t; 
} 

/* This function takes last element as pivot, places 
the pivot element at its correct position in sorted 
	array, and places all smaller (smaller than pivot) 
to left of pivot and all greater elements to right 
of pivot */
int partition (int arr[], int low, int high) 
{ 
	int pivot = arr[high]; // pivot 
	int i = (low - 1); // Index of smaller element 

	for (int j = low; j <= high- 1; j++) 
	{ 
		// If current element is smaller than the pivot 
		if (arr[j] < pivot) 
		{ 
			i++; // increment index of smaller element 
			swap(&arr[i], &arr[j]); 
		} 
	} 
	swap(&arr[i + 1], &arr[high]); 
	return (i + 1); 
} 

/* The main function that implements QuickSort 
arr[] --> Array to be sorted, 
low --> Starting index, 
high --> Ending index */
void quickSort(int arr[], int low, int high) 
{ 
	if (low < high) 
	{ 
		/* pi is partitioning index, arr[p] is now 
		at right place */
		int pi = partition(arr, low, high); 

		// Separately sort elements before 
		// partition and after partition 
		quickSort(arr, low, pi - 1); 
		quickSort(arr, pi + 1, high); 
	} 
} 

/* Function to print an array */
void printArray(int arr[], int size) 
{ 
	int i; 
	for (i=0; i < size; i++) 
		printf("%d ", arr[i]); 
	printf("n"); 
} 

// Driver program to test above functions 
int main() 
{ 
	/*used to get the time before and after the algorithm*/
	struct timeval start, end;
	/*used for computing the time difference*/
	unsigned long long int time1, time2, time_taken=0;
	/*create an array of size 10*/
	int N = 10000;
	int array[N];
    int n=10;
    // Populate the array in desending order
    

	// File pointer to write onto a file
	FILE *tp;
 	tp=fopen("timeQS.txt","w");
	for(int i=0;i<10;++i)
	{	
		for(int j=0;j<N;++j){
        array[j]=N-j;
        }
		/*print the original content of the array*/
		// printf ("Original array: ");
		// printArray(array, N);

		/*get the time before starting the algorithm*/
		gettimeofday(&start, NULL);

		/*sort the array using bubble sort algorithm*/
		quickSort(array, 0, N - 1); 

		/*get the time after finishing the algorithm*/
		gettimeofday(&end, NULL);

		/*compute the time taken in microseconds*/
		time1 = (start.tv_sec * 1000000 + start.tv_usec);
		time2 = (end.tv_sec * 1000000 + end.tv_usec);

		/*compute the difference in time*/
		time_taken  =time2 - time1;

		/*print the sorted content of the array*/
		// printf ("Sorted array: ");
		// printArray(array, N);

		/*print the time taken to console*/
		printf ("Time taken: %lluus\n", time_taken);
		fprintf (tp,"%lluus\n", time_taken);
	}
	time_taken= time_taken/10;
	fprintf (tp,"%lluus\n", time_taken);

	/*return 0 to caller to indicate normal termination of program*/
	return 0;
	// }
	// fclose(fp);
	 fclose(tp);
    // //printArray(arr, n); 

	return 0; 
} 
