// C program for insertion sort 
#include <math.h> 
#include <stdio.h>
#include <time.h> 
#include <sys/time.h>
#include <stdlib.h>

/* Function to sort an array using insertion sort*/
void insertionSort(int arr[], int n) 
{ 
	int i, key, j; 
	for (i = 1; i < n; i++) { 
		key = arr[i]; 
		j = i - 1; 

		/* Move elements of arr[0..i-1], that are 
		greater than key, to one position ahead 
		of their current position */
		while (j >= 0 && arr[j] > key) { 
			arr[j + 1] = arr[j]; 
			j = j - 1; 
		} 
		arr[j + 1] = key; 
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

// A utility function to print an array of size n 
void printArray(int arr[], int n) 
{ 
	int i; 
	for (i = 0; i < n; i++) 
		printf("%d ", arr[i]); 
	printf("\n"); 
} 

/* Driver program to test insertion sort */
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
 	tp=fopen("timeISrand.txt","w");
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
		insertionSort(array, N);

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

 
