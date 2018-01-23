#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

//________________________SETTINGS__________________________

#define WORDLEN 100
#define AUTO_HIST_SCALE 120

//Maximum initial WordList size
int MAX_LIST_LEN = 25;

//Total distinct words encountered
int nWords = 0;

//Symbol for discrete unit of histogram
char symbolHistogram = '|';

//Scale applied to Histogram
//customScale > 0 acts as multiplier
//customScale <= 0 invokes Auto Scaling based on most frequent word
double customScale = 0;

//______________________________________________________________________

//Input file pointer
FILE * fp;


//________________________________STRUCT______________________________________
//TODO: Define structure called "WordCount"
//Also, define a pointer called "WordList" to this structure here (Array of structures)
//Then, malloc this defined structure in main


typedef struct WordCount{
    char * word;                // The word
    int numWord;                // Number of occurances of this word
} WordCount;

WordCount ** WordList;

//______________________________________________________________________

char buffer[WORDLEN];
int pos = 0;

//_________NEXTWORD: Given to students: Returns nextword in file_______

static char * nextWordInFile() {
	char c;
	while((c=fgetc(fp)) != EOF) {
		if((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9')) {
			buffer[pos++] = c;
			buffer[pos] = '\0';
		}
		else {
			if(pos > 0) {
				pos = 0;
				return strdup(buffer);
			}
		}
	}
	return NULL;
}

//________________________Helper Functions______________________________

char * toLower(char * word) {
	//Helper to convert a word to lower case
	char * s = word;
	while(*s) {
		if(*s >= 'A' && *s <= 'Z') {
			*s += ' ';
		}
		s++;
	}
	return word;
	
}


int getWordIndex(char * word) {
	//Helper to get i-th word from array of structures
	//Could additionally be used to check existence of a word in the array
	for(int i = 0; i < nWords; i++) {
		if(!strcmp(WordList[i]->word, word)) {
			return i;
		}
	}
	return -1;
	
}

void help() {
	printf("SYNTAX: ./WordCount <filename> [ --sort-lex | --sort-num ] --histogram?\n");
}

void printStruct() {
	//Helper to print your structure
	//Traverse and print members with their count
	/*
	   word1 word_count
	   .
	   .
	   .
	   wordN word_count
	   */


}

//_________________________________________________________________________

//_________________________Task 1: WordCount_______________________________

/*
 *Update <wordList> with every new word encountered
 *With repeated instance of a word, only update <count>
 *New entries: Realloc if greater than macro<MAX_LIST_LEN>
 */

void wordCount() {
    
    // teh word
    char * theWord = nextWordInFile();
    
    // Check if exists
    int i;
    for (i = 0; i < nWords; i++) {
       if (strncmp(WordList[i]->word, theWord) == 0
    }
    
}

//________________________________________________________________
//_________________________Task 2: Flags (Optional)_______________________________
//Task 2 a) : Sorting Alphabetically (Ascending)

void sortLex() {
	//TODO: Your Implementation here

}

//Task 2 b) : Sorting by frequencies (Descending)

void sortNum() {
	//TODO: Your Implementation here

}

//________________________________________________________________

//___________________Extra Credit: Histogram______________________

void plotHistogram(double scale, char symbol) {

}

//_____________________________________________________________________

int main(int argc, char **argv) {
	//WordCount array
	//Malloc your structure array here
    WordList = (WordCount**)malloc(MAX_LIST_LEN * sizeof(WordCount*));

	//Reads file with <filename> given by ARGV[1]
	//nextWordInFile returns words from file pointed by FILE * fp
	if(argc == 2) {
		fp = fopen(argv[1], "r");
		if(!fp) return 0;

		//Call your WordCount method and sorting methods HERE as needed by your flags
		//TIP: Remember to change argc condition with additional flags. Current implementation only works for 2 arguments
	}
	else {
		help();
	}


	//TODO: Use argc and argv to check for flags

	return 0;
}
