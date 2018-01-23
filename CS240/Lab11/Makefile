
CC = gcc -g -Wall -Werror -std=c99

all: test_queue

test_queue: test_queue.c Queue_List.c
	$(CC) -o test_queue test_queue.c Queue_List.c

clean:
	rm -f *.o *.out test_queue total.txt
