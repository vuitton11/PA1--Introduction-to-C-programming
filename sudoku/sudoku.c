#include <stdio.h>
#include <stdlib.h>
/*Sudoku: Contains 2 part
 *File contains 9 numbers on each line, not seperated, thus is considered one number
 *Part 1) Correctness checking:
 *Checks to see if the solved sudoku is solved correctly
 *Part 2) Solvability:
 *sperated by a space for the missing number, could contain up 2 two missing vales AT MOST
 *if not solved completely, then see if the sudoku is solvable
 *INFO: 9 by 9 matrix
 */

/*Global Variables*/
int **sudokeTable, temp;
int array[] = {1,2,3,4,5,6,7,8,9};

/*Allocates space for the sudoku matrix by using malloc*/
void createTable(){
	int i;
	sudokeTable = (int**) malloc(sizeof(int*) * 9);
	for(i = 0; i < 9; i++){
		sudokeTable[i] = (int*) malloc(sizeof(int) * 9);
	}
}

/*Frees all allocated space*/
void freeTable(){
	int i;
	for(i = 0; i < 9; i++){
		free(sudokeTable[i]);
	}
	free(sudokeTable);
}

/*Prints table -> Debugging purpose*/
void printTable(){
	int i, j;
	for (i = 0; i < 9; i++){
		for (j = 0; j < 9; j++){
			printf("%d ",sudokeTable[i][j]);
		}
		printf("\n");
	}
}

/*If part1 is valid then continues to check the sloutions
 *determines if the solution is valid by adding all the index of each:
 *row, column, and sub-matrix to see if their total value is equal to 45
 *1+2+3+4+5+6+7+8+9 = 45
 If not, then the solution is invalid
 */
void part1(){
	int i, j, k, total, holder1 = 0, holder2 = 0;

	//printf(Checking rows for valid inputs\n);
	/*Checking all rows*/
	for(i = 0; i < 9; i++){
		total = 0;
		for(j = 0; j < 9; j++){
			total += sudokeTable[i][j];
		}
		if(total != 45){
			printf("incorrect\n");
			return;
		}
	}

	//printf("Continue to column check\n");
	
	/*Checks if each column is valid*/
	for(i = 0; i < 9; i++){
		total = 0;
		for(j = 0; j < 9; j++){
			total += sudokeTable[j][i];
		}
		if(total != 45)
		{
			printf("incorrect\n");
			return;
		}
	}
	//printf("Continue to sub-matrix check\n");

	/*Checks if each sub-matrix is valid*/
	for(i = 0; i < 9; i++){
		total = 0;
		for(j = 0; j < 3; j++){
			for(k = 0; k < 3; k++){
				total += sudokeTable[j+holder1][k+holder2];
				//printf("%d ", sudokeTable[j+holder1][k+holder2]);
			}
			//printf("\n");
		}
		if(total != 45){
			printf("incorrect\n");
			return;
		}
		holder2+=3;
		if((i+1) % 3 == 0 && i != 0){
			holder1 += 3;
			holder2 = 0;
		}
	}

	printf("correct\n");
}

/*Returns 1 if not solvable 
 *Returns 0 if solvable*/
int part2_1(int row1, int col1){
	//printf("part2_1\n");
	int i, j, total1 = 0, total2 = 0, missing = 0;
	for(i = 0; i < 9; i++){
			total1 += sudokeTable[i][col1];
			total2 += sudokeTable[row1][i];
		}
		if(total1 != total2){
			//printf("unsolvable1\n");
			return 1;
		}else{	//Checks its submatrix
			missing = 45 -total2;
			for(i = 0; i < 3; i++){
				for(j = 0; j < 3; j++){
					if(sudokeTable[(row1-(row1%3))+i][(col1-(col1%3))+j] == missing){
						//printf("unsolvable2\n");
						return 1;
					}
				}
			}
			//printf("solvable\n");
			return 0;
		}
}

//Checks 
void part2_2(int row1, int col1, int row2, int col2 ){
	int i, j, counter = 0, total = 0, answer;
	int buff[2];
	/*Checks to see if there is more than 1 unknown in a row or col or submatrix*/
	if(row1 == row2){
		for(i = 0; i < 9; i++){	//Finds the total of the row
			total += sudokeTable[row1][i];
		}
		for(i = 0; i < 9; i++){
			for (j = 0; j < 9; j++){
				if(array[i] == sudokeTable[row1][j]){
					buff[counter] = sudokeTable[row1][j];
					counter++;
					break;
				}
				else if(array[i] != sudokeTable[row1][j] && j == 8){
					buff[counter] = array[i];
					counter++;
				}
			}
			if(counter == 2){
				break;
			}
		}
		if(total + buff[0] + buff[1] == 45){
			printf("solvable\n");
			return;
		}else{
			printf("unsolvable\n");
			return;
		}
	}
	else if(col1 == col2){
		for(i = 0; i < 9; i++){	//Finds the total of the col
			total += sudokeTable[i][col1];
		}
		for(i = 0; i < 9; i++){
			for (j = 0; j < 9; j++){
				if(array[i] == sudokeTable[j][col1]){
					buff[counter] = sudokeTable[j][col1];
					counter++;
					break;
				}
				else if(array[i] != sudokeTable[j][col1] && j == 8){
					buff[counter] = array[i];
					counter++;
				}
			}
			if(counter == 2){
				break;
			}
		}
		if(total + buff[0] + buff[1] == 45){
			printf("solvable\n");
			return;
		}else{
			printf("unsolvable\n");
			return;
		}

	}
	else if(((row1-(row1%3))+(col1-(col1%3))) == ((row2-(row2%3))+(col2-(col2%3)))){
		for(i = 0; i < 3; i++){	//Finds the total submatrix
				for(j = 0; j < 3; j++){
					total += sudokeTable[(row1-(row1%3))+i][(col1-(col1%3))+j];
				}
			}
		for(i = 0; i < 3; i++){	
			for(j = 0; j < 3; j++){
				if(array[i] == sudokeTable[(row1-(row1%3))+i][(col1-(col1%3))+j]){
					buff[counter] = sudokeTable[j][col1];
					counter++;
					break;
				}
				else if(array[i] != sudokeTable[(row1-(row1%3))+i][(col1-(col1%3))+j] && j == 8){
					buff[counter] = array[i];
					counter++;
				}
			}
			if(counter == 2){
				break;
			}
		}
		if(total + buff[0] + buff[1] == 45){
			printf("solvable\n");
			return;
		}else{
			printf("unsolvable\n");
			return;
		}
	}else{	//No 2 unknown in the same space
		answer = part2_1(row1, col1);
		if(answer == 1){
			printf("unsolvable\n");
			return;
		}else{
			answer = part2_1(row2, col2);
			if(answer == 1){
				printf("unsolvable\n");
				return;
			}else{
				printf("solvable\n");
				return;
			}
		}
	}
}

/*Checks if the arguement is correct
 *Reads the file and places the numbers into the table
 *Determines which part of the project to excute part1 or part2
 *If a space character is read it will place a 0 inplace of a space in the table
 *and stores the position of the space in row1 and col1, if there is a second space
 *stores the position in row2 and col2
 *as well as excute part2, If not then part1 will excute
 */
void work(int argc, char const *argv){
	int row1, col1, row2, col2, answer;
	if(argc != 2){
		printf("error\n");
		return;
	}
	FILE *ptr = fopen(argv, "r");
	if(ptr == NULL){
		printf("error\n");
		return;
	}
	char input;
	int i = 0, j = 0, part = 1;
	temp = 0;
	while(fscanf(ptr, "%c", &input) != EOF){
		//printf("%c ", input );
		if(j == 9){
			i++;
			j = 0;
		}
		if(input == ' '){	//Counts the spaces
			part = 2;
			sudokeTable[i][j] = 0;
			if(temp == 0){
				row1 = i;
				col1 = j;
				temp++;
			}
			else if(temp == 1){
				row2 = i;
				col2 = j;
				temp++;
			}else{	//If more than 2 spaces are found, exit program
				printf("error\n");
				return;
			}
			j++;
		}
		else if(input == '\n'){	//ignores the newline character
			continue;
		}else{
			sudokeTable[i][j] = input - '0'; //Converts the char into a int
			j++;
		}
	}
	//printTable();
	if(part == 1){
		//printf("part1\n");
		part1(row1, col1);
	}else{
		if (temp == 1){ //One unknown variable
			//printf("part2_1\n");
			answer = part2_1(row1, col1);
			if(answer == 0){
				printf("solvable\n");
			}else{
				printf("unsolvable\n");
			}
		}else{	//Two unknown variable
		//printf("part2_2\n");
		part2_2(row1, col1, row2, col2);
		}
	}
	fclose(ptr);
}

int main(int argc, char const *argv[]){
	createTable();
	work(argc, argv[1]);
	freeTable();
	//printf("free\n");
	return 0;
}
