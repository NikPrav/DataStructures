// Shell Sort in C programming

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <stdlib.h>


void shellSort(int array[], int n){
  for (int gap = n/2; gap > 0; gap /= 2){
    for (int i = gap; i < n; i += 1) {
      int temp = array[i];
      int j;
      for (j = i; j >= gap && array[j - gap] > temp; j -= gap){
        array[j] = array[j - gap];
      }
      array[j] = temp;
    }
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
void printArray(int array[], int size){
  for(int i=0; i<size; ++i){
     printf("%d  ", array[i]);
  }
  printf("\n");
}
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
 	tp=fopen("timeShSrand.txt","w");
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
		shellSort(array, N);

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
