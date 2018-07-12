#include <stdio.h>
#include <stdlib.h>
/*bst: Binary search tree - 3 main components*/

typedef struct node{	//data structure for the bst
	int input;	//data 
	struct node *left; //left pointer
	struct node *right; //right pointer

}binaryTree;

int check;


/*Argument check to see if the argument counter is = 2*/
void argueChecker(int argc){
	if(argc != 2){
		printf("error\n");
		exit(0);
	}
}

/*Searches the tree and determines if present or not
 *Does this recursively
 */
void searchTree(binaryTree* node, int data){
	check = 0;
	// base case - hit leaf node
	if(node == NULL){	//Not in the tree
		//printf("NULL\n");
		check = 1;
		return;
	}
	if(data == node->input){
		//printf("FOUND\n");
		check = 0;
		return;
	}

	// In order traversal
	if(data < node->input){
	searchTree(node->left, data);
	}
	// CHECK IF INPUT NODE IS IN INPUT TREE
	else{
		searchTree(node->right, data);
	}

	return;
}

/*Prints the tree recurisively
 *In order
 */
void printTree(binaryTree** node){

	binaryTree* ptr = *node;
	binaryTree* temp = *node;
	// base case - hit leaf node
	if(ptr == NULL){
		//printf("\n");
		return;
	}
	printf("(");
	//printf("%d", ptr->input);
	printTree(&ptr->left);
	printf("%d", temp->input);
	printTree(&ptr->right);
	printf(")");
}

/*Frees all the allocated space in the tree*/
void deleteTree(binaryTree* node){

	// base case - hit leaf node
	if(node == NULL){
		//printf("\n");
		return;
	}

	deleteTree(node->left);
	//printf("Deleteing Node : %d\n", root->input);
	deleteTree(node->right);
	free(node);
}

/*Inserts the number into the tree recursively
 *Then places the leaf nodes null
 */
void insert2Tree(binaryTree** root, int number){
	binaryTree* ptr = *root;
	if(ptr == NULL){
		ptr = (binaryTree*)malloc(sizeof(binaryTree));
		ptr->input = number;
		ptr->left = NULL;
		ptr->right = NULL;
		*root = ptr;
		printf("inserted\n");
		return;
	}
	if(ptr->input == number){
		printf("duplicate\n");
	}
	if(number < ptr->input){
		insert2Tree(&ptr->left, number);
	} 
	if(number > ptr->input){
		insert2Tree(&ptr->right, number);
	}
}

// Deletes a node from the tree
binaryTree* deleteNode(binaryTree	* root, int number){
	check = 0;
	binaryTree *ptr = root;
	// Case 1 -> Tree empty
	if(ptr == NULL){
		check = 1;
		return root;
	}

	// number is in left subtree
	if (root->input > number){
		deleteNode(root->left, number);
	}

	// number is in right subtree
	if(root->input < number){
		deleteNode(root->right, number);
	}

	// number is at root
	if(root->input == number){
		if(root->right == NULL && root->left == NULL){
			binaryTree* node = root;
			free(root);
			return node;
		}
		// root only has  right child, just swap value
		else if(root->left == NULL){
			binaryTree* node = root->right;
			free(root);
			return node;

		}
		// root only has a left child, just swap value
		else if(root->right == NULL){
			binaryTree* node = root->left;
			free(root);
			return node;
		}
		// root has 2 children, must find in order predecessor
		else{
			binaryTree* node = root->right;
			while(node->right != NULL){
				node = node->right;
			}
				// swap data values
			root->input = node->input;
		}
		// recursive call to delete IOP (leaf node)
		root->right = deleteNode(root->right, number);
	}
	return root;

}

int main(int argc, char *argv[]){
	argueChecker(argc);
	FILE *fp = fopen(argv[1], "r");
	if(fp == NULL){
		printf("error\n");
		exit(0);
	}
	binaryTree* node = NULL;
	//insert2Tree(&node, 10);
	//printTree(&node);
	char action;
	int number;
	//int isPresent;
	while(fscanf(fp, "%c %d\n", &action, &number) != EOF){
		switch(action){
			case 'i':
				//printf("insert: %d\n", number);
				insert2Tree(&node, number);
				//searchTree();
				//printTree(node);
				break;
			case 's':
				//printf("search: %d\n", number)
				//printf("If I see this more than 3 times, ima pop off on a nigga");
				searchTree(node, number);
				if(check == 0){
					printf("present\n");
				}else{
					printf("absent\n");
				}
				break;
			case 'p':
				printTree(&node);
				printf("\n");
				break;
			case 'd':
				//printf("delete\n");
				deleteNode(node, number);
				if(check == 0){
					printf("present\n");
				}else{
					printf("absent\n");
				}
				break;
			default:
				printf("error\n");
		}
		//inTree = 'n';
		//binaryT = root;
	}
	//printf("done reading the file\n");
	fclose(fp);
	//printTree(&node);
	deleteTree(node);
	return 0;
}