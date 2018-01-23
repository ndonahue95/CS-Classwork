void bubble_sort(int array[], int num){
    int a, b, swap;
    
    for (a = 0; a < (num-1); a++) {
        for (b = 0; b < (num-a-1); b++) {
            if (array[b] > array[b+1]) { // note this is increasing order
                swap = array[b];
                array[b] = array[b+1];
                array[b+1] = swap;
            }
        }
    }
    
}
