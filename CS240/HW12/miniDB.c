//
//  miniDB.c
//
//
//  Created by Nicholas Donahue on 11/16/16.
//
//

#include "miniDB.h"

struct Node * head;
int createdHead = 0;

char * dbFileName;
char * cmFileName;
char * opFileName;

// prints the entire databsae
// ONLY FOR LOCAL TESTING
//      !!!
void printDB() {
    
    struct Node * tempNode = head;
    
    printf("Movie Database:\n");
    
    while(tempNode != NULL) {
        
        printf("Title: %s\n",tempNode->movieData->title);
        printf("Released: %s\n",tempNode->movieData->date);
        printf("Director: %s\n",tempNode->movieData->director);
        printf("ID: %d\n\n",tempNode->movieData->movieID);
        
        tempNode = tempNode->next;
        
    }
    
    printf("\n");
    
}

// create the initial database from csv file
void createDatabase() {
    
    FILE *fp;
    char buffer[513];
    
    fp = fopen(dbFileName, "r");
    
    while (fp != NULL && !feof(fp)) {
        
        fgets(buffer, 513, fp);
        
        // meh
        if (strchr(buffer, ',') != NULL && buffer[0] != '\n' && buffer[1] != '\n' && buffer[2] != '\n') {
            
            char * token = strtok(buffer, ",");
            
            struct Node * nodeToAdd = (struct Node *) malloc(sizeof(struct Node));
            nodeToAdd->next = NULL;
            nodeToAdd->prev = NULL;
            
            int runNum = 0;
            struct Movie * movieToAdd = (struct Movie *) malloc(sizeof(struct Movie));
            
            while (token != NULL) {
                
                if (runNum == 0) {
                    
                    strcpy(movieToAdd->title, token);
                    
                    runNum++;
                    
                } else if (runNum == 1) {
                    
                    strcpy(movieToAdd->date, token);
                    
                    // remove annoying space
                    memmove(movieToAdd->date, movieToAdd->date+1, strlen(movieToAdd->date));
                    
                    runNum++;
                    
                } else if (runNum == 2) {
                    
                    strcpy(movieToAdd->director, token);
                    
                    // remove annoying space
                    memmove(movieToAdd->director, movieToAdd->director+1, strlen(movieToAdd->director));
                    
                    runNum++;
                    
                } else {
                    
                    movieToAdd->movieID = atoi(token);
                    
                }
                
                token = strtok(NULL, ",");
                
            }
            
            nodeToAdd->movieData = movieToAdd;
            
            if (createdHead == 0) {
                
                head = nodeToAdd;
                
                createdHead = 1;
                
            } else {
                
                struct Node * tempNode = head;
                
                while(tempNode->next != NULL)
                    tempNode = tempNode->next;
                
                tempNode->next = nodeToAdd;
                nodeToAdd->prev = tempNode;
                
            }
            
        }
        
    }
    
    fclose(fp);
    
}

// saves database to file
void saveDatabase() {
    
    FILE *dbFile;
    char toWrite[513];
    
    dbFile = fopen(dbFileName, "w+");
    
    struct Node * tempNode = head;
    
    while(tempNode != NULL) {
        
        snprintf(toWrite, sizeof(toWrite), "%s, %s, %s, %d\n", tempNode->movieData->title, tempNode->movieData->date, tempNode->movieData->director, tempNode->movieData->movieID);
        
        fputs(toWrite, dbFile);
        
        tempNode = tempNode->next;
        
    }
    
    fclose(dbFile);
    
}

// find entry in the list
int findInList(int type, struct Node * listHead, char * data, int idata) {
    
    // type 1 = ID
    // type 2 = DIRECTOR
    // type 3 = DATE
    // type 4 = TITLE
    
    struct Node * tempNode = listHead;
    
    while (tempNode != NULL) {
        
        if (type == 1) {
            
            if (tempNode->movieData->movieID == idata) {
                
                return 1;
                
            }
            
        } else if (type == 2) {
            
            if (!strcmp(tempNode->movieData->director, data)) {
                
                return 1;
                
            }
            
        } else if (type == 3) {
            
            if (!strcmp(tempNode->movieData->date, data)) {
                
                return 1;
                
            }
            
        } else if (type == 4) {
            
            if (!strcmp(tempNode->movieData->title, data)) {
                
                return 1;
                
            }
            
        }
        
        tempNode = tempNode->next;
        
    }
    
    return 0;
}

int findInListBETTER(struct Node * listHead, int idCheck) {
    
    struct Node * tempNode = listHead;
    
    while (tempNode != NULL) {
        
        if (tempNode->movieData->movieID == idCheck) {
            
            return 1;
            
        }
        
        tempNode = tempNode->next;
        
    }
    
    return 0;
    
}

// write output to file
void writeOutput(char str[513]) {
    
    FILE * fp = fopen(opFileName, "a");
    
    fputs(str, fp);
    
    fclose(fp);
    
}

// parses a command from the csv file
void parseCommand(char buffer[513]) {
    
    // handle blank lines
    if (buffer[0] == '\n' || buffer[1] == '\n')
        return;
    
    char * token = strtok(buffer, ",");
    
    // ADD command
    if (!strcmp(token, "ADD")) {
        
        // advance one for the command
        token = strtok(NULL, ",");
        
        int runNum = 0;
        struct Movie * movieToAdd = (struct Movie *) malloc(sizeof(struct Movie));
        
        while (token != NULL) {
            
            if (runNum == 0) {
                
                strcpy(movieToAdd->title, token);
                
                // remove annoying space
                memmove(movieToAdd->title, movieToAdd->title+1, strlen(movieToAdd->title));
                
                runNum++;
                
            } else if (runNum == 1) {
                
                strcpy(movieToAdd->date, token);
                
                // remove annoying space
                memmove(movieToAdd->date, movieToAdd->date+1, strlen(movieToAdd->date));
                
                runNum++;
                
            } else if (runNum == 2) {
                
                strcpy(movieToAdd->director, token);
                
                // remove annoying space
                memmove(movieToAdd->director, movieToAdd->director+1, strlen(movieToAdd->director));
                
                runNum++;
                
            } else {
                
                movieToAdd->movieID = atoi(token);
                
            }
            
            token = strtok(NULL, ",");
            
        }
        
        // check invalid date
        
        int ABORT = 0;
        
        int month;
        int day;
        int year;
        
        char dateTemp[12];
        strcpy(dateTemp, movieToAdd->date);
        
        char * dateToken = strtok(dateTemp, "/");
        month = atoi(dateToken);
        
        dateToken = strtok(NULL, "/");
        day = atoi(dateToken);
        
        dateToken = strtok(NULL, "/");
        year = atoi(dateToken);
        
        if (month > 12 || month < 1)
            ABORT = 1;
        
        if (year > 9999 || year < 1000)
            ABORT = 1;
        
        if (day > 31 || day < 1)
            ABORT = 1;
        
        // check if in database already
        
        if (!ABORT) {
            
            if (createdHead == 0) {
                
                struct Node * nodeToAdd = (struct Node *) malloc(sizeof(struct Node));
                nodeToAdd->next = NULL;
                nodeToAdd->prev = NULL;
                nodeToAdd->movieData = movieToAdd;
                
                head = nodeToAdd;
                
                createdHead = 1;
                
            } else {
                
                struct Node * tempNode = head;
                int dupeFound = 0;
                
                while (tempNode != NULL) {
                    
                    if (tempNode->movieData->movieID == movieToAdd->movieID) {
                        dupeFound = 1;
                        break;
                    }
                    
                    tempNode = tempNode->next;
                    
                }
                
                if (!dupeFound) {
                    
                    struct Node * nodeToAdd = (struct Node *) malloc(sizeof(struct Node));
                    nodeToAdd->next = NULL;
                    nodeToAdd->prev = NULL;
                    nodeToAdd->movieData = movieToAdd;
                    
                    tempNode = head;
                    
                    while(tempNode->next != NULL)
                        tempNode = tempNode->next;
                    
                    tempNode->next = nodeToAdd;
                    nodeToAdd->prev = tempNode;
                    
                } else {
                    
                    free(movieToAdd);
                    
                }
                
            }
            
        } else {
            
            free(movieToAdd);
            
        }
        
    } else if (!strcmp(token, "EDIT")) {     // EDIT command
        
        // advance one for the command
        token = strtok(NULL, ",");
        
        int runNum = 0;
        int movieID;
        char feature[513];
        char data[513];
        
        while (token != NULL) {
            
            if (runNum == 0) {
                
                movieID = atoi(token);
                
                runNum++;
                
            } else if (runNum == 1) {
                
                strcpy(feature, token);
                
                // remove annoying space
                memmove(feature, feature+1, strlen(feature));
                
                runNum++;
                
            } else {
                
                strcpy(data, token);
                
                // remove annoying space
                memmove(data, data+1, strlen(data));
            }
            
            token = strtok(NULL, ",");
            
        }
        
        // remove '\n' from data var
        int i = 0;
        
        while(data[i] != '\0')
        {
            i++;
            
        }
        if (data[i-1] == '\n')
            data[i-1] = '\0';
        
        // find the entry in the database
        
        struct Node * tempNode = head;
        int dupeFound = 0;
        
        while (tempNode != NULL) {
            
            if (tempNode->movieData->movieID == movieID) {
                dupeFound = 1;
                break;
            }
            
            tempNode = tempNode->next;
            
        }
        
        if (dupeFound) {
            if (!strcmp(feature, "TITLE")) {
                
                strcpy(tempNode->movieData->title, data);
                
            } else if (!strcmp(feature, "DIRECTOR")) {
                
                strcpy(tempNode->movieData->director, data);
                
            } else if (!strcmp(feature, "DATE")) {
                
                strcpy(tempNode->movieData->date, data);
                
            }
        }
        
    } else if (!strcmp(token, "REMOVE")) {     // REMOVE command
        
        // advance one for the command
        token = strtok(NULL, ",");
        
        int movieID = atoi(token);
        
        // find the entry in the database
        
        struct Node * tempNode = head;
        int dupeFound = 0;
        
        while (tempNode != NULL) {
            
            if (tempNode->movieData->movieID == movieID) {
                dupeFound = 1;
                break;
            }
            
            tempNode = tempNode->next;
            
        }
        
        if (dupeFound) {
            struct Node * next = tempNode->next;
            struct Node * prev = tempNode->prev;
            
            
            if (prev != NULL)
                prev->next = next;
            
            // last in list
            if (next != NULL)
                next->prev = prev;
            
            free(tempNode);
            
            tempNode = NULL;
            
        }
        
    } else if (!strcmp(token, "LOOKUP")) {     // LOOKUP command
        
        // advance one for the command
        token = strtok(NULL, ",");
        
        int runNum = 0;
        char feature[513];
        char data[513];
        
        while (token != NULL) {
            
            if (runNum == 0) {
                
                strcpy(feature, token);
                
                // remove annoying space
                memmove(feature, feature+1, strlen(feature));
                
                runNum++;
                
            } else {
                
                strcpy(data, token);
                
                // remove annoying space
                memmove(data, data+1, strlen(data));
            }
            
            token = strtok(NULL, ",");
            
        }
        
        // remove '\n' from data var
        int i = 0;
        
        while(data[i] != '\0')
        {
            i++;
            
        }
        if (data[i-1] == '\n')
            data[i-1] = '\0';
        
        // does it exist at all in db?
        
        struct Node * tempNode = head;
        int dupeFound = 0;
        
        struct Node * lookupHeadNode = (struct Node *) malloc(sizeof(struct Node));
        lookupHeadNode->next = NULL;
        lookupHeadNode->prev = NULL;
        lookupHeadNode->movieData = NULL;
        
        struct Node * currNode = lookupHeadNode;
        
        while (tempNode != NULL) {
            
            if (!strcmp(feature, "TITLE")) {
                
                if (!strcmp(tempNode->movieData->title, data)) {
                    
                    if (!dupeFound) {
                        
                        lookupHeadNode->movieData = tempNode->movieData;
                        
                        dupeFound = 1;
                        
                    } else {
                        
                        struct Node * nodey = (struct Node *) malloc(sizeof(struct Node));
                        nodey->next = NULL;
                        nodey->prev = currNode;
                        nodey->movieData = tempNode->movieData;
                        
                        currNode->next = nodey;
                        
                        currNode = currNode->next;
                        
                    }
                    
                }
                
            } else if (!strcmp(feature, "DIRECTOR")) {
                
                if (!strcmp(tempNode->movieData->director, data)) {

                    if (!dupeFound) {
                        
                        lookupHeadNode->movieData = tempNode->movieData;
                        
                        dupeFound = 1;
                        
                    } else {
                        
                        struct Node * nodey = (struct Node *) malloc(sizeof(struct Node));
                        nodey->next = NULL;
                        nodey->prev = currNode;
                        nodey->movieData = tempNode->movieData;
                        
                        currNode->next = nodey;
                        
                        currNode = currNode->next;
                        
                    }
                    
                }
                
            } else if (!strcmp(feature, "DATE")) {
                
                if (!strcmp(tempNode->movieData->date, data)) {

                    if (!dupeFound) {
                        
                        lookupHeadNode->movieData = tempNode->movieData;
                        
                        dupeFound = 1;
                        
                    } else {
                        
                        struct Node * nodey = (struct Node *) malloc(sizeof(struct Node));
                        nodey->next = NULL;
                        nodey->prev = currNode;
                        nodey->movieData = tempNode->movieData;
                        
                        currNode->next = nodey;
                        
                        currNode = currNode->next;
                        
                    }
                    
                }
                
            } else if (!strcmp(feature, "ID")) {
            
                if (tempNode->movieData->movieID == atoi(data)) {
                    
                    lookupHeadNode->movieData = tempNode->movieData;
                        
                    dupeFound = 1;
                 
                }
                
            }
            
            tempNode = tempNode->next;
            
        }
        
        struct Node * readNode = lookupHeadNode;
        
        // -----
        
        char toWriteOMG[513];
        
        snprintf(toWriteOMG, sizeof(toWriteOMG), "%s, %s, %s\n", buffer, feature, data);
        
        writeOutput(toWriteOMG);
        
        // ----- 
        
        while (readNode != NULL && lookupHeadNode->movieData != NULL) {
            
            char toWrite[513];
            
            snprintf(toWrite, sizeof(toWrite), "%s, %s, %s, %d\n", readNode->movieData->title, readNode->movieData->date, readNode->movieData->director, readNode->movieData->movieID);
            
            writeOutput(toWrite);
            
            readNode = readNode->next;
        }
        
    } else if (!strcmp(token, "DISPLAY")) {     // DISPLAY command
        
        // advance one for the command
        token = strtok(NULL, ",");
        
        int runNum = 0;
        char feature[513];
        int _order;
        int _max;
        
        while (token != NULL) {
            
            if (runNum == 0) {
                
                strcpy(feature, token);
                
                // remove annoying space
                memmove(feature, feature+1, strlen(feature));
                
                runNum++;
                
            } else if (runNum == 1) {
                
                _order = atoi(token);
                
                runNum++;
                
            } else {
                
                _max = atoi(token);
                
            }
            
            token = strtok(NULL, ",");
            
        }
        
        
        // get a count
        
        struct Node * tempNode = head;
        int _count = 0;
        
        while (tempNode != NULL) {
            
            tempNode = tempNode->next;
            
            _count++;
            
        }
        
        
        // hmmmmm
        _count--;
        
        // sorting (oh boy)
        
        // sorting : get head
        
        struct Node * newHead = (struct Node *) malloc(sizeof(struct Node));
        newHead->next = NULL;
        newHead->prev = NULL;
        newHead->movieData = head->movieData;
        
        struct Node * runNode = head;
            
            while (runNode != NULL && runNode->movieData != NULL) {
                
                if (!strcmp(feature, "ID")) {
                    
                    if (runNode->movieData->movieID < newHead->movieData->movieID) {
                        
                        newHead->movieData = runNode->movieData;
                        
                    }
                    
                } else if (!strcmp(feature, "DIRECTOR")) {
                   
                    if (strcmp(runNode->movieData->director, newHead->movieData->director) > 0) {
                        
                        newHead->movieData = runNode->movieData;
                        
                    } else if (strcmp(runNode->movieData->director, newHead->movieData->director) == 0) {
                        
                        if (runNode->movieData->movieID > newHead->movieData->movieID) {
                            
                            newHead->movieData = runNode->movieData;
                            
                        }
                        
                    }
                    
                } else if (!strcmp(feature, "TITLE")) {
                    
                    if (strcmp(runNode->movieData->title, newHead->movieData->title) > 0) {
                        
                        newHead->movieData = runNode->movieData;
                        
                    } else if (strcmp(runNode->movieData->title, newHead->movieData->title) == 0) {
                        
                        if (runNode->movieData->movieID > newHead->movieData->movieID) {
                            
                            newHead->movieData = runNode->movieData;
                            
                        }
                        
                    }
                    
                } else if (!strcmp(feature, "DATE") && !findInListBETTER(newHead, runNode->movieData->movieID)) {
                    
                    // build runNode date
                    
                    char * dateString = strdup(runNode->movieData->date);
                    
                    dateString = strtok(dateString, "/");
                    int _runMonth = atoi(dateString);
                    
                    dateString = strtok(NULL, "/");
                    int _runDay = atoi(dateString);
                    
                    dateString = strtok(NULL, "/");
                    int _runYear = atoi(dateString);
                    
                    
                    // build newNode date
                    
                    char * dateString2 = strdup(newHead->movieData->date);
                    
                    dateString2 = strtok(dateString2, "/");
                    int _newMonth = atoi(dateString2);
                    
                    dateString2 = strtok(NULL, "/");
                    int _newDay = atoi(dateString2);
                    
                    dateString2 = strtok(NULL, "/");
                    int _newYear = atoi(dateString2);
                    
                    
                    // do werk
                    
                    if (_runYear > _newYear) {
                        
                        newHead->movieData = runNode->movieData;
                        
                    } else if (_runYear == _newYear) {
                        
                        if (_runMonth > _newMonth) {
                            
                            newHead->movieData = runNode->movieData;
                            
                        } else if (_runMonth == _newMonth) {
                            
                            if (_runDay > _newDay) {
                                
                                newHead->movieData = runNode->movieData;
                                
                            } else if (_runDay == _newDay) {
                                
                                if (runNode->movieData->movieID > newHead->movieData->movieID) {
                                    
                                    newHead->movieData = runNode->movieData;
                                    
                                }
                            }
                            
                        }
                        
                    }
                    
                }
                
                runNode = runNode->next;
                
            }
        
        // sorting : do werk
        
        int i;
        struct Node * prevNode = newHead;
        
        for (i = 0; i < _count; i++) {
            
            struct Node * newNode = (struct Node *) malloc(sizeof(struct Node));
            newNode->next = NULL;
            newNode->prev = prevNode;
            newNode->movieData = head->movieData;
            
            // make newNode movieData one not in the list
            
            struct Node * OMGletsbedone = head;
            
            while (findInListBETTER(newHead, OMGletsbedone->movieData->movieID)) {
                
                OMGletsbedone = OMGletsbedone->next;
                
            }
            
            newNode->movieData = OMGletsbedone->movieData;
            
            runNode = head;
            
            
            
            
            prevNode->next = newNode;
                            
                while (runNode != NULL) {
                    
                    if (!strcmp(feature, "ID")) {
                        
                        if (runNode->movieData->movieID < newNode->movieData->movieID && !findInListBETTER(newHead, runNode->movieData->movieID)) {
                            
                            newNode->movieData = runNode->movieData;
                            
                        }
                        
                    } else if (!strcmp(feature, "DIRECTOR")) {
                        
                        if (strcmp(runNode->movieData->director, newNode->movieData->director) > 0 && !findInListBETTER(newHead, runNode->movieData->movieID)) {
                            
                            newNode->movieData = runNode->movieData;
                            
                        } else if (strcmp(runNode->movieData->director, newNode->movieData->director) == 0 && !findInListBETTER(newHead, runNode->movieData->movieID)) {
                            
                            if (runNode->movieData->movieID > newNode->movieData->movieID) {
                                
                                newNode->movieData = runNode->movieData;
                                
                            }
                            
                        }
                        
                    } else if (!strcmp(feature, "TITLE")) {
                        
                        if (strcmp(runNode->movieData->title, newNode->movieData->title) > 0 && !findInListBETTER(newHead, runNode->movieData->movieID)) {
                            
                            newNode->movieData = runNode->movieData;
                            
                        } else if (strcmp(runNode->movieData->title, newNode->movieData->title) == 0 && !findInListBETTER(newHead, runNode->movieData->movieID)) {
                            
                            if (runNode->movieData->movieID > newNode->movieData->movieID) {
                                
                                newNode->movieData = runNode->movieData;
                                
                            }
                            
                        }
                        
                    } else if (!strcmp(feature, "DATE") && !findInListBETTER(newHead, runNode->movieData->movieID)) {
                        
                        // build runNode date
                        
                        char * dateString = strdup(runNode->movieData->date);
                        
                        dateString = strtok(dateString, "/");
                        int _runMonth = atoi(dateString);
                        
                        dateString = strtok(NULL, "/");
                        int _runDay = atoi(dateString);
                        
                        dateString = strtok(NULL, "/");
                        int _runYear = atoi(dateString);
                        
                        
                        // build newNode date
                        
                        char * dateString2 = strdup(newNode->movieData->date);
                        
                        dateString2 = strtok(dateString2, "/");
                        int _newMonth = atoi(dateString2);
                        
                        dateString2 = strtok(NULL, "/");
                        int _newDay = atoi(dateString2);
                        
                        dateString2 = strtok(NULL, "/");
                        int _newYear = atoi(dateString2);
                        
                        
                        // do werk
                        
                        if (_runYear > _newYear) {
                            
                            newNode->movieData = runNode->movieData;
                                                        
                        } else if (_runYear == _newYear) {
                            
                            if (_runMonth > _newMonth) {
                                
                                newNode->movieData = runNode->movieData;

                            } else if (_runMonth == _newMonth) {
                                
                                if (_runDay > _newDay) {
                                    
                                    newNode->movieData = runNode->movieData;
                                    
                                } else if (_runDay == _newDay) {
                                    
                                    if (runNode->movieData->movieID > newNode->movieData->movieID) {
                                        
                                        newNode->movieData = runNode->movieData;
                                        
                                    }
                                    
                                }
                                       
                            }
                            
                        }
                        
                    }
                    
                    runNode = runNode->next;
                    
                }
                
            prevNode = prevNode->next;
            
        }
        
        
        // printing methods
        
        struct Node * readNode = newHead;
        
        // -----
        
        char toWriteOMG[513];
        
        snprintf(toWriteOMG, sizeof(toWriteOMG), "%s, %s, %d, %d\n", buffer, feature, _order, _max);
        
        writeOutput(toWriteOMG);
        
        // -----
        
        if (_order == 0) {
            
            // ascending
            
            while (readNode->next != NULL)
                readNode = readNode->next;
            
            while (readNode != NULL && readNode->movieData != NULL && (_max-- > 0)) {
                
                char toWrite[513];
                
                snprintf(toWrite, sizeof(toWrite), "%s, %s, %s, %d\n", readNode->movieData->title, readNode->movieData->date, readNode->movieData->director, readNode->movieData->movieID);
                
                writeOutput(toWrite);
                
                readNode = readNode->prev;
            }
            
        } else {
            
            // descending
        
            while (readNode != NULL && readNode->movieData != NULL && (_max-- > 0)) {
                
                char toWrite[513];
                
                snprintf(toWrite, sizeof(toWrite), "%s, %s, %s, %d\n", readNode->movieData->title, readNode->movieData->date, readNode->movieData->director, readNode->movieData->movieID);
                
                writeOutput(toWrite);
                
                readNode = readNode->next;
            }
            
        }
        
    }
    
}

int main(int argc, char* argv[]) {
    
    if (argc < 4)
        return -1;
    
    dbFileName = argv[1];
    cmFileName = argv[2];
    opFileName = argv[3];
    
    // create database
    createDatabase();
    
    //printDB();
    
    // lez do this: commands
    FILE * commandsFile;
    char buffer[513];
    
    commandsFile = fopen(cmFileName, "r");
    
    while (commandsFile != NULL && !feof(commandsFile)) {
        
        fgets(buffer, 513, commandsFile);
        
        // parse that command boi
        // MAKE SURE ITS VALID DOE
        
        if (strchr(buffer, ',') != NULL)
            parseCommand(buffer);
        
    }
    
    fclose(commandsFile);
    
    
    saveDatabase();
    
    return 0;
    
}










