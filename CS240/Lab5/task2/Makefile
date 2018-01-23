all: sorts

sorts: main.c insert_sort.c select_sort.c
	gcc -Werror -Wall -std=c99 -g -o sorts main.c insert_sort.c select_sort.c
clean:
	rm -rf sorts *out *.o *txt 
