#include <stdio.h>
#include <stdlib.h>
/*list: Linked Lists
 *Takes in a single argument, which is the path to the file
 *list can contain zero or more integers
 *Must be from least to greatest
 *Must use malloc to allocate space for new nodes, and must be freed
 *2 functions:
 *1) insert: adds the data to the list, if present already do nothing
 *2) delete: removes the data from the list. If not present do nothing
 *Output: 
 *Number of nodes/n
 *Nodes from least to greatest 
 */

/*Data Type*/
typedef struct _Node {
	int data;
	struct _Node* next;
}Node;

/*Checks if argument is correct*/
void checkArgument(int argc){
	if(argc != 2){
		printf("error\n");
		exit(0);
	}
}

/*Allocates space for the new node*/
Node* createNode(int data){
	Node* node = (Node*)malloc(sizeof(Node));
	node->data = data;
	return node;
}

/*Inserts a node to the head of the list then sorts it in order*/
Node* insert(Node* head, int data){
	if(head == NULL){
		//printf("adding data to empty list\n");
		Node* node = createNode(data);
		head = node;
		node->next = NULL;
		return head;
	} 
	Node* curr = head;
	Node* prev = NULL;
	while(curr != NULL){
		if (curr->data < data){
			if(curr->data == data){
				return head;
			}
			if(curr->next != NULL){
				//printf("there's more items\n");
				if(curr->next->data < data){
					//printf("need to advance\n");
					prev = curr;
					curr = curr->next;
					continue;
				} else if(curr->next->data == data){
					return head;
				}
				Node* node = createNode(data);
				node->next = curr->next;
				curr->next = node;
				return head;
			}
			//printf("data greater\n");
			Node* node = createNode(data);
			curr->next = node;
			node->next = NULL;
			return head;
		}else {
			if(curr->data == data){
				return head;
			}
			if(prev == NULL){
				Node* node = createNode(data);
				node->next = head;
				head = node;
			}
			prev = curr;
			curr = curr->next;
			continue;
		}
		prev = curr;
		curr = curr->next;
	}
	return head;
}

/*Deletes the node from the list*/
Node* delete(Node* head, int data){
	// If list is empty
	if(head == NULL){
		return head;
	}
	
	// iterate through list and check if value exists
	Node* ptr = head;
	Node* prev = NULL;

	// case for 1 item in the list
	if(ptr->next == NULL){
		if(ptr->data == data){
			free(ptr);
			head = NULL;
			return head;
		}
	}

	while(ptr != NULL){
		// Delete node if data is in list
		if(ptr->data == data){
			/// Case for 1st item in list
			if(prev == NULL){
				head = ptr->next;
				free(ptr);
				return head;
			}
			prev->next = ptr->next;
			free(ptr);
			return head;
		}
		prev = ptr;
		ptr = ptr->next;
	}
	//printf("node doesn't exist\n");
	return head;
}

/*Prints the number of nodes are in the list*/
void printNumber(Node* head){
	int counter = 0;
	if(head == NULL){
		printf("0\n");
		return;
	}else{
		Node* ptr = head;
		while(ptr != NULL){
			ptr = ptr->next;
			counter++;
		}
		printf("%d\n", counter);
	}
}

/*Prints the entire list*/
void printList(Node* head){
	if(head == NULL){
		printf("\n");
		return;
	}else{
		Node* ptr = head;
		while(ptr != NULL){
			printf("%d ", ptr->data);
			ptr = ptr->next;
		}
		printf("\n");
	}
}

/*Frees the whole list when done*/
void deleteList(Node* head){
	if(head == NULL){
		return;
	}
	Node* curr = head;
	Node* next = head;

	while(curr != NULL){
		next = curr->next;
		free(curr);
		curr = next;
	}

	head = NULL;

}

int main(int argc, char* argv[]){
	checkArgument(argc);

	FILE * fp = fopen(argv[1], "r");
	if(fp == NULL){
		printf("error\n");
		return 0;
	}
	char action;
	int number;
	//Node head
	Node* head = NULL;

	while(fscanf(fp, "%c %d\n", &action, &number) != EOF){
		switch(action){
			case 'i': //insert function
				//printf("Do -> insert\n");
				//printf("num: %d\n", number);
				head = insert(head, number);
				//printList(head);
				break;
			case 'd': //delete function
				//printf("Do -> search\n");
				//printf("num: %d\n", number);
				head = delete(head, number);
				//printList(head);
				break;
			default:	//Error file is not in proper format
			printf("error\n");
		}
	}

	/*Debugging purpose*/
	/*printf("test\n");
	head = insert(head, 5);
	head = insert(head, 4);
	head = insert(head, 4);
	printList(head);
	printf("test\n");
	*/

	printNumber(head);//prints the number of nodes
	printList(head);//prints the list
	fclose(fp);	//closes the file
	deleteList(head);//allocates the space

	return 0;
}