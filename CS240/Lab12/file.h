#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct node{
	int data;
	struct node * next;
}node;
node * head;
//prints all of linked-list starting with head
void print();
//append node to start of list
void append(node *n);
//get last returns last node in linked-list while removing it from the list
node * getLast();
void read_node(char * filename);
void write_node(char * filename);


