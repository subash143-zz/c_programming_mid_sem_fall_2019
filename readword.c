/*
******************************************************************
*   Compile using: gcc -g -Wall -std=gnu99 readword.c -o readword
******************************************************************
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define WORD_SIZE 50

typedef enum {false  = 0, true = 1}  boolean;


void to_uppercase(char *string){
	int count = 0;
	while(string[count] != '\0'){
		if(string[count] >= 'a' && string[count] <= 'z'){
			//Converting to uppercase
			string[count] = string[count] - 32;
		}	
		count ++;
	}
}

char* get_token(FILE *fp) {
	// This function will extract tokens from file - one word at a time
	// A word is defined by a sequence of non-whitespace characters surrounded
	// on both sides by one or more whitespace characters
	// Your code MUST be able to handle consecutive whitespace characters
	// while extracting the tokens!

	char *token = calloc(WORD_SIZE, sizeof(char));
	boolean eof_flag = ( fscanf(fp," %s ", token) == 1 )? false : true;	// true if end-of-file reached, false otherwise
	
	if (eof_flag) {	
		return NULL;	// reached end of file --> return NULL
	}
	// Otherwise return token
	printf("\nRaw token = %s",token);
	return token;
	
}
 

int main(int argc, char *argv[]) {

	if(argc != 2){
		printf("Please provide a filename as an argument!\n");
		exit(EXIT_FAILURE);
	}
	FILE *fp;
	fp = fopen(argv[1], "r");
	if(NULL == fp){
		printf("Invalid file specified. Please provide a valid filename as an argument!\n");
		exit(EXIT_FAILURE);
	}
	char *word = (char *)malloc(sizeof(char)* WORD_SIZE);
	int tokens_count = 0;
	while ((word = get_token(fp)) != NULL) { 
		++tokens_count;
		to_uppercase(word);
		printf("\nToken: %s", word);
	}
	
	free(word);

	printf("\nTotal tokens found = %d\n", tokens_count);
	
	return 0;
}
