#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*Anagram: Sorting
 *Only given lower-case letter
 *Sort in order 
 */

int main(int argc, char *argv[])
{
	int i, j;
	for(i = 0; i < strlen(argv[1]); i++){
		for(j = i; j < strlen(argv[1]); j++){
			if(argv[1][i] > argv[1][j]){ //compares the values of the char to see if one of them is a smaller value
				char temp = argv[1][i]; //Holds the value of the char
				argv[1][i] = argv[1][j];
				argv[1][j] = temp;
			}
		}
	}
	printf("%s\n", argv[1]);
	return 0;
}