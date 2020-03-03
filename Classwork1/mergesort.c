/* C program for Merge Sort */
#include <stdio.h> 
#include <time.h>
#include <time.h>
#include <sys/time.h>
#include <stdlib.h>

// Merges two subarrays of arr[]. 
// First subarray is arr[l..m] 
// Second subarray is arr[m+1..r] 
void merge(int arr[], int l, int m, int r) 
{ 
	int i, j, k; 
	int n1 = m - l + 1; 
	int n2 = r - m; 

	/* create temp arrays */
	int L[n1], R[n2]; 

	/* Copy data to temp arrays L[] and R[] */
	for (i = 0; i < n1; i++) 
		L[i] = arr[l + i]; 
	for (j = 0; j < n2; j++) 
		R[j] = arr[m + 1+ j]; 

	/* Merge the temp arrays back into arr[l..r]*/
	i = 0; // Initial index of first subarray 
	j = 0; // Initial index of second subarray 
	k = l; // Initial index of merged subarray 
	while (i < n1 && j < n2) 
	{ 
		if (L[i] <= R[j]) 
		{ 
			arr[k] = L[i]; 
			i++; 
		} 
		else
		{ 
			arr[k] = R[j]; 
			j++; 
		} 
		k++; 
	} 

	/* Copy the remaining elements of L[], if there 
	are any */
	while (i < n1) 
	{ 
		arr[k] = L[i]; 
		i++; 
		k++; 
	} 

	/* Copy the remaining elements of R[], if there 
	are any */
	while (j < n2) 
	{ 
		arr[k] = R[j]; 
		j++; 
		k++; 
	} 
} 

/* l is for left index and r is right index of the 
sub-array of arr to be sorted */
void mergeSort(int arr[], int l, int r) 
{ 
	if (l < r) 
	{ 
		// Same as (l+r)/2, but avoids overflow for 
		// large l and h 
		int m = l+(r-l)/2; 

		// Sort first and second halves 
		mergeSort(arr, l, m); 
		mergeSort(arr, m+1, r); 

		merge(arr, l, m, r); 
	} 
} 
/*populates the given array of size N with random integers*/
void populateArray(int* array, int N){
	/*seed the random number generator with time*/
	srand(time(NULL));

	/*iterate through all elements in array and populate them*/
	for (int i = 0 ; i < N; ++i)
		array[i] = rand() % 100;
}

/* UTILITY FUNCTIONS */
/* Function to print an array */
void printArray(int A[], int size) 
{ 
	int i; 
	for (i=0; i < size; i++) 
		printf("%d ", A[i]); 
	printf("\n"); 
} 

/* Driver program to test above functions */
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
 	tp=fopen("timeMSrand.txt","w");
	for(int i=0;i<10;++i)
	{	
		// Populate the array with random values
        populateArray(array,N);
		/*print the original content of the array*/
		// printf ("Original array: ");
		// printArray(array, N);

		/*get the time before starting the algorithm*/
		gettimeofday(&start, NULL);

		/*sort the array using bubble sort algorithm*/
		mergeSort(array, 0, N - 1); 

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
