/*
********************************************************************
*   Compile using: gcc -g -Wall -std=gnu99 wordhash2.c -o wordhash2
********************************************************************
*/



#ifndef WORDHASH2_H_
	#include "wordhash2.h"
#endif

	// This function will extract tokens from file - one word at a time
	// A word is defined by a sequence of non-whitespace characters surrounded
	// on both sides by one or more whitespace characters
	// Your code MUST be able to handle consecutive whitespace characters
	// while extracting the tokens!
char* get_token(FILE *fp) {

	char *token = calloc(WORD_SIZE, sizeof(char));
	boolean eof_flag = ( fscanf(fp," %s ", token) == 1 )? false : true;	// true if end-of-file reached, false otherwise
	
	if (eof_flag) {	
		return NULL;	// reached end of file --> return NULL
	}	
	
	// Otherwise return token
	printf("\nRaw token = %s",token);
	return token;
	
}
 

void init_hash_table(struct hash_entry hash_table[]) {
	for (int i = 0; i < HASH_TABLE_SIZE;i++) {
		hash_table[i].head = NULL;
		hash_table[i].count = 0;
	}

	return;
}


struct node* find_dup_token(struct node* const head, char *token) {
	// This function will determine if the token you are trying to
	// insert already exists in the linked list.
	// If exists, then it will return a pointer to the node containing 
	// the duplicate token. Otherwise, it will return NULL 
	struct node *ptr = head;
	while(ptr != NULL){
		if(strcmp(ptr->data, token) == 0){
			return ptr;
		}
		ptr = ptr -> next;
	}
	return NULL;
}


	// This function will insert a token into the correct location
	// of the hash table. However, if the token already exists
	// in the hash table then only the 'freq' field is updated for 
	// the corresponding existing duplicate-token node.
	// Otherwise, the token is inserted at the end of the correct
	// location in the hash table.
void insert_in_hash_table(struct hash_entry hash_table[], char *token) {

    char first_letter = token[0];
    int index_of_corresponding_hash_table = (int)(first_letter - 65);
    struct hash_entry *hash_location = &hash_table[index_of_corresponding_hash_table];
    struct node *duplicate_node = (struct node*) malloc(sizeof(struct node *));

    if(hash_location->head != NULL &&  (duplicate_node = find_dup_token(hash_location->head, token)) != NULL){
		duplicate_node->freq++;
	}
	else{
    	if(hash_location->head == NULL) hash_location->count++; //Counting the NULL when any node is added
	    struct node *to_add = (struct node*) malloc(sizeof(struct node *));
	    to_add->data = token;
	    to_add->next = hash_location->head;
	    to_add->freq = 1;
	    hash_location->head = to_add;
	    hash_location->count++;
	}
	return;
}



void print_hash_table(struct hash_entry hash_table[]) {
	for (int i = 0;i < HASH_TABLE_SIZE;i++) {
		printf("\n(%c, %d) :: \t",i + 65, (hash_table[i].head != NULL ? hash_table[i].count : 0));		// character value in A-Z range
		
		// Now traverse linked list of hash_table[i]
		struct node *ptr = hash_table[i].head;
		while (ptr != NULL) {
			printf("(%s, %d) --> ",ptr->data, ptr->freq);
			ptr = ptr->next;
		}
			printf("NULL\n");
	}

	return;
}



void delete_hash_table(struct hash_entry hash_table[]) {
	for (int i = 0; i < HASH_TABLE_SIZE; i++) {
		if (hash_table[i].head != NULL) {
			struct node *ptr = hash_table[i].head->next;
			struct node *prev = hash_table[i].head;
			do {

				free(prev);
				prev = ptr;
				ptr = (prev != NULL) ? prev->next : NULL;
				
			} while (prev != NULL);
		}
		hash_table[i].head = NULL;
	}
	return;
}


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


int main(int argc, char *argv[]) {
	char* word = NULL;

	struct hash_entry hash_table[HASH_TABLE_SIZE];
	init_hash_table(hash_table);	

	FILE *fp = NULL;
	if (argc > 1) {
		if ((fp = fopen(argv[1],"r")) == NULL) {
			fprintf(stderr,"\nError in opening file %s. Exiting...\n",argv[1]);
			exit(EXIT_FAILURE);
		}
	}
	
	int tokens_count = 0, raw_tokens_count = 0;

	while ((word = get_token(fp)) != NULL) {
		// first convert token to upper case
		to_uppercase(word);
		++raw_tokens_count;
		// If word starts with a letter, then insert into hash table
		if (word[0] >= 'A' && word[0] <= 'Z') {		// insert into hash table
			++tokens_count;
			printf("\nToken to insert into hash table: %s", word);
			insert_in_hash_table(hash_table, word);
		}
		else{
			free(word);
		}
	}

	print_hash_table(hash_table);

	delete_hash_table(hash_table);

	printf("\nTotal raw tokens found = %d", raw_tokens_count);
	printf("\nTotal tokens inserted into hash table = %d\n", tokens_count);
	
	return 0;
}
