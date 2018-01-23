//
//  miniDB.h
//  
//
//  Created by Nicholas Donahue on 11/16/16.
//
//

#ifndef miniDB_h
#define miniDB_h

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Movie {
    char title[50];
    char date[12];
    char director[40];
    int movieID;
};

struct Node {
    struct Node* next;
    struct Node* prev;
    
    struct Movie * movieData;
};

#endif /* miniDB_h */
