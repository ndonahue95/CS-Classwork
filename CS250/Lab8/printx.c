#include <stdlib.h>
#include <stdio.h>


char * hexString(int dec) {
    char * hexadecimalNumber = malloc(sizeof(char) * 100);


    
    int i = 1;
    
    while(dec!=0){

      //To convert integer into character
      //if( temp < 10)
      //     temp =temp + 48;
      //else
      //   temp = temp + 55;

      hexadecimalNumber[i++] = dec % 16;
        
      dec = dec / 16;
  }

    return hexadecimalNumber;

}

int main() {

    //long int decimalNumber;

   // printf("Enter any decimal number: ");
    //scanf("%ld",&decimalNumber);

    //char * str = hexString(decimalNumber);

    //int i = 5,j;
    //for(j = i -1 ;j> 0;j--)
    //  printf("%c",str[j]);

  return 0;

}
