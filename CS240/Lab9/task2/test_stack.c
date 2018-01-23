#include "stack.h"

void printStack(int pos) {
	int i = 0;
	for(i = 0; i < pos; i++) {
		printf("%d ", stack[i]);
	}
	printf("\n");
}

/* test case 1 */
void test1() {
	Stack();
	printStack(0);
}

/* test case 2 */
void test2() {
	Stack();

	push(1);
	push(2);
	push(3);

	printStack(3);
}

/* test case 3 - ignore */
/*
void test3() {
	int i = 0;
	for(i = 0; i < 9; i++) {
		push(i+1);
	}
	printStack(9);
}
*/

/* test case 4 */
void test4() {
	Stack();
	push(1);
	push(2);
	pop();
	pop();
	pop();
	push(1);
	printStack(1);
}

/* test case 5 */
void test5() {
	Stack();
	push(1);
	push(2);
	push(3);
	pop();
	push(4);
	pop();
	pop();
	push(5);
	printStack(2);
}

/* test case 6 */
void test6() {
	Stack();
	int i;
	for(i = 0; i < 12; i++) {
		push(i+1);
	}
	printStack(12);
}

int main(int argc, char * argv[]) {
	if(argc < 2) {
		printf("Usage: Test test1|test2|...\n");
		exit(1);
	}

	char * test = argv[1];
	printf("Running %s\n", test);

	if(test[4] == '1') {
		test1();
	}
	else if(test[4] == '2') {
		test2();
	}
	/*
	else if(test[4] == '3') {
		test3();
	}
	*/
	else if(test[4] == '4') {
		test4();
	}
	else if(test[4] == '5') {
		test5();
	}
	else if(test[4] == '6') {
		test6();
	}
	else {
		printf("Test not found!\n");
		exit(1);
	}

	return 0;
}
