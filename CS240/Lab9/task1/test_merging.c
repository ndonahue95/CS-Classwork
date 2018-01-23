#include <stdio.h>
#include <stdlib.h>
#include "merging.h"

/* test case 1 */
void test1(){
	int nums1[] = {2, 3, 7, 9};
	int nums2[] = {4, 9, 10, 12, 13};
    int * result = merging(nums1, nums2, 4, 5);
    printf("Merged Array: ");
    int i = 0;
    for (i = 0; i < 9; i++) {
    	printf("%d ", result[i]);
    }
    printf("\n");
    free(result);
}

/* test case 2 */
void test2() {
	int nums1[] = {2, 10, 23, 24, 30, 31};
	int nums2[] = {1, 5, 18, 22, 40};
    int * result = merging(nums1, nums2, 6, 5);
    printf("Merged Array: ");
    int i = 0;
    for (i = 0; i < 11; i++) {
    	printf("%d ", result[i]);
    }
    printf("\n");
    free(result);
}

void test3() {
	int nums1[] = {1, 3, 5, 7, 9};
	int nums2[] = {2, 4, 6, 8, 10};
    int * result = merging(nums1, nums2, 5, 5);
    printf("Merged Array: ");
    int i = 0;
    for (i = 0; i < 10; i++) {
    	printf("%d ", result[i]);
    }
    printf("\n");
    free(result);
}

void test4() {
	int nums1[] = {1, 2, 3, 4, 5};
	int nums2[] = {6, 7, 8, 9, 10};
    int * result = merging(nums1, nums2, 5, 5);
    printf("Merged Array: ");
    int i = 0;
    for (i = 0; i < 10; i++) {
    	printf("%d ", result[i]);
    }
    printf("\n");
    free(result);
}

void test5() {
	int nums1[] = {54, 66, 78, 123, 243, 567};
	int nums2[] = {145, 167, 200, 222};
    int * result = merging(nums1, nums2, 6, 4);
    printf("Merged Array: ");
    int i = 0;
    for (i = 0; i < 10; i++) {
    	printf("%d ", result[i]);
    }
    printf("\n");
    free(result);
}

int main(int argc, char ** argv) {

	char * test;

	if (argc <2) {
		printf("Usage: merging test1|test2|...test5\n");
		exit(1);
	}

	test = argv[1];
	printf("Running %s\n", test);
	if (test[4]=='1' ) {
		test1();
	}
	else if (test[4]=='2' ) {
		test2();
	}
	else if (test[4]=='3' ) {
		test3();
	}
	else if (test[4]=='4' ) {
		test4();
	}
	else if (test[4]=='5' ) {
		test5();
	}
	else {
		printf("Test not found!!\n");
		exit(1);
	}

	return 0;

}