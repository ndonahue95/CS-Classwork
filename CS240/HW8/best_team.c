#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "best_team.h"

// Position meanings
const char * position_name[5] = {"Point Guard",
    "Shooting Guard",
    "Small Forward",
    "Power Forward",
    "Center"};


Team * initializeTeam() {
    Team * head = NULL;
    head = malloc(sizeof(Team));
    if (head == NULL) {
        return NULL;
    }
    
    head->_numOfPlayers = 0;
    head->_players[0] = NULL;
    
    return head;
}

// current pointer
Player * currPos;

// Returns something like "02,12,3,8,5,6,4,3,Russell" from file
// Returns 1 line from file for every function call
// Second call will return second line, etc.
char * inputFile(FILE *fd) {
    char * buffer = (char *) malloc(200 * sizeof(char));
    char * bufferptr = buffer;
    *bufferptr = fgetc(fd);
    while (*bufferptr != EOF && *bufferptr != '\0' && *bufferptr != '\n') {
        bufferptr++;
        *bufferptr = fgetc(fd);
    }
    *bufferptr = '\0';
    return buffer;
}

// ugh
char *tofree;

Player * parsePlayer(char * str) {
    // TODO: malloc size of a player, add the details from string to Player type
    
    char *token, *string;
    
    tofree = strdup(str);
    
    string = tofree;
    
    int i = 0;
    int info[8];
    char * name;
    
    while ((token = strsep(&string, ",")) != NULL) {
        // case of name
        if (i == 8) {
            name = strdup(token);
        } else {
            info[i] = atoi(token);
        }
        
        i++;
    }
    
    Player * p = (Player *) malloc(sizeof(Player));
    
    p->_shirtNum = info[0];
    p->_age = info[1];
    p->_pos = info[2];
    p->_name = name;
    p->_next = NULL;
    
    // build them stats...
    stats toStat;
    toStat._pass = info[3];
    toStat._shoot = info[4];
    toStat._speed = info[5];
    toStat._block = info[6];
    toStat._height = info[7];
    
    p->_stats = toStat;
    
    
    free(tofree);
    
    return p;
}

void loadData(FILE * fd) {
    // TODO: load all data from file to allPlayers
    // Don't forget to free the buffer returned by inputFile
    
    char * next = inputFile(fd);
    int createdHead = 0;
    while (*next != EOF && *next != '\0' && *next != '\n') {
        Player * pl = parsePlayer(next);
        
        if (createdHead == 0) {
            allPlayers = pl;
            currPos = pl;
            createdHead = 1;
        } else {
            currPos->_next = pl;
            currPos = pl;
        }
        
        free(next);
        next = inputFile(fd);
    }
    
    free(next);
}

Player * findBestPlayer(int pos) {
    // TODO: iterate through allPlayers
    // Returns the pointer to the best player for the specified pos
    
    currPos = allPlayers;
    
    Player * theBest = allPlayers;
    
    // TODO: null check?
    
    while (currPos != NULL) {
        if (pos == 0) {
            if (theBest->_stats._pass < currPos->_stats._pass)
                theBest = currPos;
        } else if (pos == 1) {
            if (theBest->_stats._shoot < currPos->_stats._shoot)
                theBest = currPos;
        } else if (pos == 2) {
            if (theBest->_stats._speed < currPos->_stats._speed)
                theBest = currPos;
        } else if (pos == 3) {
            if (theBest->_stats._block < currPos->_stats._block)
                theBest = currPos;
        } else if (pos == 4) {
            if (theBest->_stats._height < currPos->_stats._height)
                theBest = currPos;
        }
        
        currPos = currPos->_next;
        
        // WHY LORD WHY
        if (currPos == NULL)
            break;
    }
    
    return theBest;
}

int buildBestTeam(Team * t) {
    // TODO: utilize findBestPlayer(pos) to build the best team
    // order of players has to be PG SG SF PF C
    
    int i;
    
    for (i = 0; i < 5; i++) {
        Player * toAdd = findBestPlayer(i);
        t->_players[i] = toAdd;
        t->_numOfPlayers = i + 1;
    }
    
    return t->_numOfPlayers;
}

void freePlayer(Player * p) {
    // TODO: free allocated memory in p
    
    free(p->_name);
    free(p);
}

void freeTeam(Team * t) {
    //printf("\n\n%s\n\n", tofree);
    
    //free(tofree);
    
    int i;
    
    for (i = 0; i < t->_numOfPlayers; i++) {
        freePlayer(t->_players[i]);
    }
    
    free(t);
    
    // TODO: free allocated memory in t, utilize freePlayer(p)
}

void print(Team * t) {
    printf("=========================\n");
    printf("      The Best Team      \n");
    printf("=========================\n\n");
    int i;
    for (i = 0; i < t->_numOfPlayers; i++) {
        printf("Name     : %s\n", t->_players[i]->_name);
        printf("Age      : %d\n", t->_players[i]->_age);
        printf("Shirt #  : %d\n", t->_players[i]->_shirtNum);
        printf("Position : %s\n\n", position_name[t->_players[i]->_pos]);
    }
}
