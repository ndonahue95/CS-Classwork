#include <stdio.h>
	
int main(){
	char name[100];
	int age;
	long number;
	printf("Enter your name: ");

	/*scan string from stdin and store it in variable name*/
    scanf("%99s", name);


	printf("Enter your age: ");

	/*scan age from stdin and store it in variable age*/
    scanf("%d", &age);


	printf("Enter your phone number: ");

	/*scan phone number from stdin and store it in number*/
    scanf("%ld", &number);


	printf("\n");
	printf("Your name is: %s\n", name);
	printf("Your age is: %d\n", age);
	printf("Your phone number is %ld\n", number);
	return 0;
}
