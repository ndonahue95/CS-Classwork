#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "file.h"
void get_head(){
	head = (node*)malloc(sizeof(node));
        head->data = 17;
}
void get_node(int count){
	get_head();
	int i = 0;
	for(;i<count;i++){
		node * n = (node*)malloc(sizeof(node));
		n->data =(count-i) + 5;
		append(n);
	}
}
//how we test one node 1,3,5
int test1Node(){
	node * n = head;
	if(n == NULL){
		printf("head node is null\n");
		return 0;
	}
	if(n->data != 17){
		printf("issue with the head node data\n");
		return 0;
	}
	n = n->next;
	if(n == NULL){
                printf("second node is null\n");
                return 0;
        }
	if(n->data != 6){
		printf("second node data is wrong\n");
		return 0;
	}
	return 1;
}
//how we test 5 nodes for test 2,4,6
int test5Node(){
	node * n = head;
        if(n == NULL){
                printf("head node is null\n");
                return 0;
        }
        if(n->data != 17){
                printf("issue with the head node data\n");
                return 0;
        }
        n = n->next;
        if(n == NULL){
                printf("second node is null\n");
                return 0;
        }
        if(n->data != 6){
                printf("second node data is wrong\n");
                return 0;
        }
	n = n->next;
	if(n == NULL){
		printf("thrid item is null\n");
		return 0;
	}
	if(n->data != 7){
		printf("thrid item is data is wrong\n");
		return 0;
	}
	n = n->next;
        if(n == NULL){
                printf("fourth item is null\n");
		return 0;
        }
        if(n->data != 8){
                printf("fourth item is data is wrong\n");
		return 0;
        }
	n = n->next;
        if(n == NULL){
                printf("fifth item is null\n");
		return 0;
        }
        if(n->data != 9){
                printf("fifth item is data is wrong\n");
		return 0;
        }
	n = n->next;
        if(n == NULL){
                printf("sixth item is null\n");
		return 0;
        }
        if(n->data != 10){
                printf("sixth item is data is wrong\n");
		return 0;
        }
	return 1;
}
void free_list(){
	node * n = head;
	while(n){
		node * temp = n->next;
		free(n);
		n = NULL;
		n = temp;
	}
}
void test1(){
	remove("temp.bin");
	get_node(1);
	write_node("temp.bin");
	head->next = NULL;
	/*read_node_inst("temp.bin",1);
	print();
	int ret = test1Node();
	free_list();
	if(ret == 0){
                printf("failed test case 1\n");
        }
	return ret;*/	
}
void test2(){
	remove("temp.bin");
	get_node(5);
        write_node("temp.bin");
	head->next = NULL;
        /*read_node_inst("temp.bin",5);
        print();
	int ret = test5Node();
        free_list();
	if(ret == 0){
                printf("failed test case 2\n");
        }
	return ret;*/
}
int test3(){
	/*remove("temp.bin");
	get_node(1);
        write_node_inst("temp.bin");
	head->next = NULL;*/
        get_head();
	read_node("temp.bin");
        print();
	int ret = test1Node();
        free_list();
	if(ret == 0){
                printf("failed test case 3\n");
        }
	return ret;
}
int test4(){
	/*remove("temp.bin");
	get_node(5);
        write_node_inst("temp.bin");
	head->next = NULL;*/
        get_head();
	read_node("temp.bin");
        print();
	int ret = test5Node();
        free_list();
	if(ret == 0){
                printf("failed test case 4\n");
        }
	return ret;
}
int test5(){
	remove("temp.bin");
	get_node(1);
        write_node("temp.bin");
	head->next = NULL;
        read_node("temp.bin");
	int ret = test1Node();
        print();
        free_list();
	if(ret == 0){
                printf("failed test case 5\n");
        }
        return ret;
}
int test6(){
	remove("temp.bin");
	get_node(5);
        write_node("temp.bin");
	head->next = NULL;
        read_node("temp.bin");
        print();
        int ret = test5Node();
	free_list();
	if(ret == 0){
		printf("failed test case 6\n");
	}
        return ret;
}
             
int main(int argc,char*argv[]){
	//remove("temp.bin");
	if(argc == 2){
		if(!strcmp(argv[1],"test1")){
			test1();
		}
		else if(!strcmp(argv[1],"test2")){
			test2();
                }
		else if(!strcmp(argv[1],"test3")){
			test3();
                }
		else if(!strcmp(argv[1],"test4")){
			test4();
                }
		else if(!strcmp(argv[1],"test5")){
			test5();
                }
		else if(!strcmp(argv[1],"test6")){
			test6();
                }
	}
	else{
		printf("usage: ./test_file testn\n");
	}
	return 1;
}
