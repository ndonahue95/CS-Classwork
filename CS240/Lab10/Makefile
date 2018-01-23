all: word_count

word_count: word_count.c
	gcc -Werror -Wall -std=c99 -g -o word_count word_count.c
clean:
	rm -rf word_count *out *txt
