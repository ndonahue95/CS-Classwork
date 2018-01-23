/*
 * Simple implementation of bubble sort to
 * sort an int array in ascending order.
 */

#include <stdio.h>
#include <stdlib.h>
#include "bubble_sort.h"

void print_array(int array[], int num){
	int i;
	printf("[ ");
	for (i = 0; i < num; i++){
		if (i != num-1){
			printf("%d, ", array[i]);
		}
		else {
			printf("%d ]\n\n", array[i]);
		}
	}
}

int main(){
		// number of input elements
		int num = 0;
		// Get number of inputs from user
		printf("Please enter number of elements\n");
		scanf("%d", &num);

		printf("Please enter %d integers\n", num);

    	// create an array to save input numbers
		int array[num];

		int i;
		// Get the input elements
		for (i = 0; i < num; i++){
			scanf("%d", &array[i]);
		}
		printf("Array Before sorted is: \n");
		print_array(array, num);

		bubble_sort(array, num);

		printf("Array After sorted is: \n");
		print_array(array, num);
		return 0;
}
