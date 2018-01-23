#include <stdio.h>


int main()                                                                        // Main function

{
    
    int a,b,flag;                                                                          // Define variables
    
    flag=2;                                                                                 // Initialize variables
    
    printf("Enter the first number: ");
    
    scanf("%d",&a);                                                                 // Input First number
    
    printf("Enter the second number: ");
    
    scanf("%d",&b);                                                                  // Input second number
    
    if ( a>b)
        
        flag=1;
    
    else if (a < b)
        
        flag=0;
    
    if( flag==1)
        
        printf( "%d is strictly greater than %d by %d.\n", a,b, a-b);
    
    else if(flag==0)
        
        printf( "%d is strictly greater than %d by %d.\n", b,a, b-a);
    
    else
        
        printf( "%d and %d are equal.\n", b,a);
    
    
}

