

#include <stdio.h>
#include <string.h>


int myprintf(char *format, ...) {

    void *start = &format;
    int i;
    char * str;

    start += sizeof(char*);

    for (i = 0; i < strlen(format); i++) {

        if (format[i] == '%') {

            switch (format[i+1]) {

                case 'c':

                    putchar(*((char*)start)); 
                    start += sizeof(char*);

                    break;

                case 's':

                	str = *((char**)start);
                    
                	int i = 0;
                	while (str[i] != '\0') {
	                    putchar(str[i]); 
	                    i++;
	                }
                    
                    start += sizeof(char**);

                    break;

                case 'x':

                    printx(*((int*)start));
                    start += sizeof(int);
                    break;

                case 'd':

                    // TODO

                    break;
            }

            i++;

        } else {

            putchar(format[i]);

        }

    }

}

int main() {

	myprintf("Hello, %s! Welcome to my lab %c file.\n", "Grader", '8');

	myprintf("Here I will %s %s %s", "demonstrate", " my ", "lab's features.\n");

	myprintf("Hex for 65535, 41394, 0, and 9999: %x %x %x %x\n", 65535, 41394, 0, 9999);

	myprintf("All %s in %c so you can see even with %x the %c %s are %s! :)\n", "the tests", '1', 5555, '_', "*TESTESTEST*", "working");
    

	return 0;
}
