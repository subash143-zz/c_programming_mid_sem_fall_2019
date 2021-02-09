#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void my_strncpy(char *source, char *destination){
	while(*source != '\0'){
		*destination = *source;
		destination++;
		source++;
	}
	destination = '\0';
}

// Returns true if s is a number else false 
int isNumber(char *s) {
    for (int i = 0; i < strlen(s); i++) {
       if(!(s[i] >= '0' && s[i] <= '9')) return 0;
    }
    return 1;
}

int main(int argc, char *argv[]){

	if(argc != 4){
		printf("Please provide 3 arguments in following order:\n1. String\n2. Integer\n3. String\n");
		exit(EXIT_FAILURE);
	}

	if(isNumber(argv[2]) == 0){
		printf("Second argument must be a number. Exiting.....\n");
		exit(EXIT_FAILURE);	
	}

	//Getting commandline arguments
	int second = atoi(argv[2]);
	char *first = (char *)malloc(sizeof(char)* strlen(argv[1]));
	char *third = (char *)malloc(sizeof(char)* strlen(argv[3]));

	my_strncpy(argv[1], first);
	my_strncpy(argv[3], third);


	//checking the index to make sure that it is valid
	if(second > strlen(first)){
		printf("Invalid input. Exiting....\n");
		exit(EXIT_FAILURE);
	}	

	//finding the length of new string and allocating memory for it
	int new_string_length = strlen(first) + strlen(third) + 1;
	char *new_string = (char *)malloc(sizeof(char)* (new_string_length));

	//Storing part of first string before index
	for(int i = 0; i < second; i++){
		new_string[i] = first[i];
	}

	//Storing last argument
	for(int i = 0; i < strlen(third); i++){
		new_string[second + i] = third[i];
	}

	//Storing remaining part of first string after index
	for(int i = 0; i < strlen(first) - second; i++ ){
		int new_index = (second + strlen(third) + i);
		new_string[new_index] = first[second + i];
	}

	//Adding sentinel at the end
	new_string[new_string_length]  = '\0';

	printf("%s\n", new_string);

	return 0;
}