all: merging

merging: test_merging.c merging.c
	gcc -Werror -Wall -std=c99 -g -o merging test_merging.c merging.c
clean:
	rm -rf merging *out *txt
