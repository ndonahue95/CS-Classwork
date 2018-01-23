/*
 * Simple implementation of insertion sort and selection sort to
 * sort an int array in Descending order.
 */

#include <stdio.h>
#include <stdlib.h>
#include "sorts.h"

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

    int opt = 0;
    do {
      printf("How do you want to sort the array?\n");
      printf("1.Insert Sort\n2.Select Sort\n");
      scanf("%d", &opt);
      if (opt == 1){
        printf("You chose insert sort.\n");
      }
      else if (opt == 2){
        printf("You chose select sort\n");
      }
      else {
        opt = -1;
        printf("Not a valid option!\n\nPlease choose again.\n");
      }
    }while (opt == -1);

    printf("Array Before sorted is: \n");
    print_array(array, num);

     if (opt == 1){
      insert_sort(array, num);
    }

    if (opt == 2){
      select_sort(array, num);
	}

	printf("Array After sorted is: \n");
	print_array(array, num);
	return 0;
}
