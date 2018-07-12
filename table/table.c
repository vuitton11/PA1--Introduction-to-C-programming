#include<stdio.h>
#include <stdlib.h>

/*table: Hash Tables
 *maintains and manipulates a hash table
 *Takes a single argument which is a txt file
 *table uses a hash table with 10000 buckets
 *hash function is h(n) = n mod 10000
 *2 main components to this assignment:
 *1)Insert function - inserts the item into the hash if it isnt already present
 *prints insert if so
 *if present print duplicate
 *2)Search function - checks the hash to see if the item is present or not
 *prints if it is or not
 */

typedef struct node{
	struct node * next;
	int variable;
}node;

typedef struct hash
{
	node * table[10000];
}hash;

//global variables
hash * matrix;
FILE *fp;
int buckets = 10000;	//Size of buckets
int number, hashKey;	//variable that is being read from the file along with the hashkey function
char present = 'n';

void argueChecker(int argc){	//Checks to see if the arguement counter is correct
	if(argc != 2){
		printf("error\n");
		exit(0);
	}
}

void makeHash(){	//Creates the hash by allocating the correct amount of space
	int i = 0;
	matrix = (hash*)malloc(sizeof(hash));
	for (i = 0; i < buckets; i++){
		matrix->table[i] = NULL;
	}
}

/*Searches the hash for the variable
 *If the variable is present sets the char present to = 'y'
 *Else sets the char present to = 'n'
 */
void opSearch(){
	node *bucket = matrix->table[hashKey];
	while(1){
		if(bucket == NULL){	//End of valid numbers
			//printf("null\n");
			present = 'n';
			break;
		}
		if(bucket->variable == number){	//Found
			//printf("in\n");
			present = 'y';
			break;
		}
		bucket = bucket->next; //moves to the next item in the list
	}
}

/*Operation Insert
 *Searches the hash to see if the variable we want to insert is already present
 *If so do nothing
 *Else insert
 */
void opInsert(){
	opSearch();
	if(present == 'y'){
		printf("duplicate\n");
		return;
	}else{
		printf("inserted\n");
		node *this;
		node *additional = malloc(sizeof(node));
		if(matrix->table[hashKey] == NULL){
			additional->variable = number;
			additional->next = NULL;
			matrix->table[hashKey] = additional;
		}else{
			this = matrix->table[hashKey];
			additional->variable = number;
			additional->next = this;
			matrix->table[hashKey] = additional;
		}
	}
}

/*A function for search to print whether or not the variable is present*/
void isPresent(){
	if(present == 'n'){
		printf("absent\n");
	}else if(present == 'y'){
		printf("present\n");
	}
}

/*Frees all the memory that has been allocated in the hash table*/
void destroyHash(){
	int i = 0;
	for (i = 0; i < buckets; i++){
		free(matrix->table[i]);
	}
	free(matrix);
}

/*Simulates a hashtable
 *Opens the file and continues to read the file
 *If the operation is 'i' -> insert to the hash
 *If the operation is 's' -> search the hash for the variable
 *Closes the file when fscanf is == EOF
 */
void simulateHash(char *argv){
	char action;
	fp = fopen(argv, "r");
	if(fp == NULL){	//If the file does not exist
		printf("error\n");
		exit(0);
	}
	makeHash();
	while(fscanf(fp, "%c %d\n", &action, &number) != EOF){
		hashKey = number % buckets; //Creates hash key
		//printf("n:%d - h:%d\n", number, hashKey );
		switch(action){
			case 'i': //insert function
				//printf("Do -> insert\n");
				opInsert();
				break;
			case 's': //search function
				//printf("Do -> search\n");
				opSearch();
				isPresent();
				break;
			default:	//Error file is not in proper format
			printf("error\n");
		}
		present = 'n';
	}
	fclose(fp);	//closes the file
	destroyHash();	//frees memory
}

int main(int argc, char *argv[]){
	argueChecker(argc);
	simulateHash(argv[1]);
	return 0;
}
