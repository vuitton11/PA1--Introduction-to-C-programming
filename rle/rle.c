#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/*rle: String Operations II
 *Takes a single arguement
 *Compresses a string for each repeating letter or punctuation 
 *-If the compress string it longer than the orginal string, print orginal string
 *-If the string contains a # program must print "error" and nothing else
 */
int main(int argc, char *argv[])
{
	int length = strlen(argv[1]); //Gets the length of the string
	char buffer[256], temp[256]; //buffer holds the char and the number of times it has appeared
	temp[0] = '\0';	//To avoid garbage values that would be detected from the strcat function 
	int i,j,counter = 0;
	for(i = 0; i < length; i++){
		for(j = i; j < length; j++){
			if(isdigit(argv[1][j])){  //Checks to see if the string contains a #
				printf("error\n");
				exit(0);
			}
			/*If at the last index, will concat the strings 
			 *Then compare the length of the new string to the orginal and print out the string accordingly
			 */
			if(argv[1][i] == argv[1][j] && j == length-1){
				counter++;
				sprintf(buffer, "%c%d", argv[1][i], counter); //Places the chars and ints into buffer
				strcat(temp, buffer);	//Concat the strings
				if(length < strlen(temp)){
						printf("%s\n", argv[1]);
					}else{
					printf("%s\n", temp);
				}
				return 0;
			}
			else if(argv[1][i] == argv[1][j]){	//If the charcters match its a hit
				counter++;
			}else{	/*If not the last index, will concatinate the char and counter with the new string*/
				sprintf(buffer, "%c%d", argv[1][i], counter);
				strcat(temp, buffer);
				i = counter + i -1;
				counter = 0;
				break;
			}
		}
	}
	return 0;
}
