#include <stdio.h>
#include <stdlib.h>
#include "merging.h"

int cmpfunc (const void * a, const void * b) {
    return ( *(int*)a - *(int*)b );
}

int * merging (int * nums1, int * nums2, int size1, int size2) {
    int * newMem = malloc(size1*sizeof(int) + size2*sizeof(int));

    int i;
    
    for (i = 0; i < size1; i++) {
        newMem[i] = nums1[i];
    }
    
    for (i = 0; i < size2; i++) {
        newMem[size1 + i] = nums2[i];
    }
    
    //for (i = 0; i < size1 + size2; i++)
        //printf("\n%d\n", newMem[i]);
    
    qsort(newMem, size1 + size2, sizeof(int), cmpfunc);
    
    return newMem;
}