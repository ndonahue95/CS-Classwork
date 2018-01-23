#include <stdio.h>

int main()
{  
   char first[30];
   char last[30];

    printf("Enter your first name: ");
   scanf("%s", first);
       printf("Enter your last name: ");
   scanf("%s", last);
   
   printf("Hello, %s %s.\n", first, last);
   
   return 0;
}
