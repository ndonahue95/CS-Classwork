all: stack

stack: test_stack.c stack.c
	gcc -Werror -Wall -std=c99 -g -o stack test_stack.c stack.c
clean:
	rm -rf stack *out *txt
