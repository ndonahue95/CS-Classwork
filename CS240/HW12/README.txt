-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
	HW 12 - README

   by Nicholas Donahue

	CS 240 @ PURDUE U
-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

Included Files:
- miniDB.c 	->	Raw c file to be compiled and create the executable
- miniDB.h 	->	Header file for the miniDB.c
- README.txt 	-> 	This README file
- MakeFile 	-> 	The included makefile used to create the ‘minidb’ executable

Usage:
./minidb database.csv commands.csv outputFile.txt

database.csv		->	database file
commands.csv		->	commands file
outputFile.txt		->	output file (all output here)

Thought Process:
For this project, I took my time to review a wide range of implementation methods. After consideration I chose to order my database of movie files in a doubly linked list. For teach movie data I created a structure to store their specific variables. 

For my doubly linked list I had the following structure as it’s node:

struct Node {
    struct Node* next;			->	Pointer to next node
    struct Node* prev;			->	Pointer to previous node
    
    struct Movie * movieData;		->	Pointer to movieData struct (see below)
};

For my movieData I used the following structure:

struct Movie {
    char title[50];			->	Title of the movie
    char date[12];			->	Date movie released
    char director[40];			->	Director’s name
    int movieID;			->	The unique ID of the movie
};

By organizing the data into this ‘Movie’ structure I was able to easily keep track and manage the unique information between movies in each node. 

For the DISPLAY method (the most tricky in my opinion), I simply organized the linked list in ascending order and then based on the requested print sort I used the doubly linked list to my advantage by simply printing the list backwards instead of having to re-sort the entire list for ascending and descending. Entries with matching Dates, Titles, or Directors will be sorted by their respected IDs.

For LOOKUP I chose not to do the extra credit wildcard (*).

For parsing strings from files I used the file I/O library of C and used tokens and strtok to separate commas (,), spaces ( ), and slashes (/).


Methods: 

void createDatabase()
	Reads initial database file and creates linked list

void saveDatabase()
	Saves the linked list to the database file

int findInList(int type, struct Node * listHead, char * data, int idata)
	Finds node in linked list, returns 1 if found 0 if not.

int findInListBETTER(struct Node * listHead, int idCheck) 
	Finds node in linked list, returns 1 if found 0 if not. BY ID ONLY.

void parseCommand(char buffer[513])
	Reads in line-by-line the command to be run and executes it.


Final Notes:
I really enjoyed the open-endedness of this project. I have seen a lot of disagreement from the Piazza and other peers but I want to submit my opinion that this was a challenging yet enjoyable learning experience. Some people might say this is ‘leaving us in the dark’ but I disagree, this was perfect for a final HW assignment. Have a great holiday!

