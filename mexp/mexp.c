#include <stdio.h>
#include <stdlib.h>
#include <math.h>
/*mexp: Matrix Exponentiation
 *Multiply the Matrix to itself (n -1) times
 *Takes a file as an arguement
 *First line determines the size
 *The rest are the values to place in the matrix, with the exception of the first line
 *The last line is the exponent -> n
 *n >= 0
 */

/*Global Vars*/
int **matrixA, **matrixB, **matrixC, size;
FILE *ptr;

/*Allocates space for both matrix A and B*/
void createMatrix(int size){
	matrixA = (int **)malloc(sizeof(int *) * size);
	matrixB = (int **)malloc(sizeof(int *) * size);
	matrixC = calloc(size, sizeof(int *));

	int i;
	for (i = 0; i < size; i++)
	{
		matrixA[i] = (int *)malloc(sizeof(int) * size);
		matrixB[i] = (int *)malloc(sizeof(int) * size);
		matrixC[i] = calloc(size, sizeof(int));
	}
}

/*Multiplies the matrix together and stores the answer into matrix C
 *Then stores the inputs from matrix C into matrix A
 *Then resets all values in matrix C to 0
 */
void multiply(){
	int i, j, k;
	for(k = 0; k < size; k++){
		for (i = 0; i < size; i++){
			for (j = 0; j < size; j++){
				matrixC[k][i] += matrixA[k][j] * matrixB[j][i];
			}
		}
	}
	for (i = 0; i < size; i++){
		for (j = 0; j < size; j++){
			matrixA[i][j] = matrixC[i][j];
			matrixC[i][j] = 0;
		}
	}
}

/*Reads the file
 *Allocates space for the size of the matrix
 *Places the inputs into the Matrix
 */
void inputVals(char *argv){
	ptr = fopen(argv, "r");
	if(ptr == NULL){  //If the file doesnt exist, end the program
		printf("error\n");
		exit(0);
	}
	int input, i, j, n, k;
	fscanf(ptr, "%d\n", &size); //Gets the size of the matrix
	
	createMatrix(size); //Calls function to allocate space for the matrix A and B

	char useless; //Holds a space charcter / new line character
	
	/*Reads the the file and inputs the values into Matrix A and B*/
	for (i = 0; i < size; i++){
		for (j = 0; j < size; j++){
			fscanf(ptr, "%d%c", &input, &useless);
			matrixA[i][j] = input;
			matrixB[i][j] = input;
		}
	}

	fscanf(ptr, "%d\n", &n);	// Gets the exponent
	if(n == 0){ //if the exponent print 1
		for (i = 0; i < size; i++){
			for (j = 0; j < size; j++){
				matrixA[i][j] = 1;
			}
		}
	}else{
		for(k = 0; k < n-1; k++){
			multiply();
		}
	}
}

/*Prints matrix A which contains the answer*/
void printResult(){
	int i,j;
	for (i = 0; i < size; i++){
		for (j = 0; j < size; j++){
			if(j == size -1){
			   printf("%d",matrixA[i][j]);
			}else{			
			printf("%d ",matrixA[i][j]);
			}
		}
		printf("\n");
	}
}

/*Frees all the allocated space from all the matrix*/
void freeMatrix(){
	int i;
	for (i = 0; i < size; i++){
		free(matrixA[i]);
		free(matrixB[i]);
		free(matrixC[i]);
	}
	free(matrixA);
	free(matrixB);
	free(matrixC);
	fclose(ptr); //Closes the file
}


int main(int argc, char *argv[])
{
	inputVals(argv[1]);
	printResult();
	freeMatrix();
	return 0;
}
