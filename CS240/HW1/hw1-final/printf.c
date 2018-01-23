#include <stdio.h>
	
int main(){
	int num1 = 4;
	int num2 = 67;
	char letter = 'y';
	double decimal = 56.72;
	char * word = "CS240 is really fun";
    
    printf("I am about to print the values of variables\n");

    printf("The value of num1 is %d and the value of num2 is %d\n", num1, num2);

    printf("The value of letter is %c\n", letter);

    printf("The value of decimal is %lf\n", decimal);

    printf("The value of word is %s\n", word);

    printf("\"This is a quote\" and '\\' is a slash\n");

	return 0;
}
