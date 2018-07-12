#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
/*Yell: String Operations I
 *Takes in a paramters of string and outputs them in caps 
 */

int  main(int argc, char *argv[])
{
	if(argc != 2){
		printf("error\n");
		return 0;
	}
	int i;
	for(i = 0; i < strlen(argv[1]); i++){  //Iterates through each index of the string of the size of the string
		printf("%c",(toupper(argv[1][i])));  //Prints a char of the capital version of the letter
	}
	printf("\n");
	return 0;
}

