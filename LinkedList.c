/* 
 Programmes: TJ Shrestha and Thomas Raddatz
 The following program is a linked list. It takes in string arguments from the command line. First, we check if the word already exists in the linked list with findNode(). If it does, then the word is deleted from the linked list with deleteNode(). Otherwise, if an argument starts with an uppercase letter, it is inserted in the beginning with insertAtBeginning(). If an arguments starts with a lowercase letter it is inserted at the end with insertAtTheEnd();
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/*
 Creates the structure Node, typedefined to the alias Node with the
 following members:
 data: a char* to the string value.
 next: a Node* to the next node in the linked list.
 */
typedef struct Node
{
    char* data;
    struct Node* next;
} Node;

/*
 Creates the structure LinkedList, typedefined to the alias LinkedList
 with the following member : 
 head: a Node* to the sentinel node 'head', the beginning of the linked list.
 */
typedef struct LinkedList {
    Node* head;
} LinkedList;

/*
 Function and global variable declarations
 */
LinkedList list;
void insertAtBeginning( LinkedList* list, char element[]);
void insertAtTheEnd( LinkedList* list, char element[]);
void deleteNode( LinkedList* list, char element[]);
int findNode( LinkedList list, char element[]);
void displayLinkedList( LinkedList list);

/* 
 Main function, takes in the command line arguments and inserts strings into or deletes strings from the linked list based on the program's specifications.
 */
int main(int argc, char *argv[]) {
    
    /*If there are no arguments, then return with an error.*/
    if (argc == 1 ) {
        printf("ERROR: must read atleast an argument.\n");
        return 0;
    }
    else {
    /*The head of the linked list is a sentinel node and holds the value of null.*/
    list.head = (Node*) malloc (sizeof(Node));
    list.head->data = NULL;
    list.head->next = NULL;
    
    for (int i = 1; i < argc; i++) {
        if (isupper(argv[i][0])) {
            
            if ( findNode(list, argv[i]) == 1)
                deleteNode(&list, argv[i]);
            else
                insertAtBeginning(&list, argv[i] );
        }
        
        else {
            if (findNode(list,argv[i]) == 1)
                deleteNode(&list, argv[i]);
            else
                insertAtTheEnd(&list, argv[i]);
        }
    }
    
    displayLinkedList(list);
    return 1;
    }
}

/*
 Takes in a pointer to the linked list and the string we want to insert as parameters
 Allocates memory for a new node and copies the string into the Node's data pointer using strcpy(char* destination, const char* source).
 Then inserts the new node into the beginning of the linked list after the sentinel head node.
 */
void insertAtBeginning(LinkedList* list, char element[]) {
    
    Node *newNode = (Node*)malloc(sizeof(Node));
    newNode->data = (char*)malloc(strlen(element) * sizeof(char));
    
    strcpy(newNode->data, element);
    newNode->next = NULL;
    
    Node *temp = list->head->next;
    list->head->next = newNode;
    newNode->next = temp;
    

}

/*
 Takes in a pointer to the linked list and the string we want to insert as parameters.
 Allocates memory for a new node and copies the string into the Node's data pointer using strcpy(char* destination, const char* source).
 Then does a current walk and inserts the new node at the end of the linked list
 */
void insertAtTheEnd(LinkedList* list, char element[]) {
    
    Node *newNode = (Node*)malloc(sizeof(Node));
    
    newNode->data = (char*)malloc(strlen(element) * sizeof(char));
   
    strcpy(newNode->data, element);
    newNode->next = NULL;
    
    Node *curr = list->head;

    while (curr->next != NULL) {
        curr = curr->next;
    }
    
    curr->next = newNode;
}

/*
 Takes in a pointer to the linked list and the string that we want to delete as parameters.
 Does a current walk to the node containing the string that we want to delete, comparing each node's data value to the string parameter with strcmp(const char* string1, const char* string2)
 */
void deleteNode(LinkedList* list, char element[]) {
    
    Node *curr = list->head;
    curr = curr->next;
    
    while (curr != NULL) {
        
        /* If strcmp() returns 0, then the two strings match. Now delete the node containing that string from the linked list.*/
        if (strcmp(element, curr->data) == 0) {
            
            Node *temp = curr->next;
            
            free(curr->data);
            free(curr);
            
            curr = temp;
        }
        curr = curr->next;
    }
}

/*
 Takes in the linked list and the string that we are looking for.
 Does a current walk, comparing each node's string value with the string that we are looking for with strcmp(const char* string1, const char* string2)
 If we have found the string in the linked list, return 1 for true. 
 */

int findNode(LinkedList list, char element[]) {
    Node *curr = list.head;
    
    while (curr->next != NULL) {
        if (strcmp(element, curr->next->data) == 0) {
            return 1;                       // 1 means true
        }
        curr = curr->next;
    }
    return 0;                               // 0 means false
}

/*
 Does a current walk through the linked list and prints the string value contained in each node.
 */
void displayLinkedList(LinkedList list) {
    
    printf("%s", "The list:- ");
    
    Node *curr = list.head->next;
    
    while (curr->next != NULL) {
        printf("%s, ", curr->data);
        curr = curr->next;
    }
    
    printf("%s\n", curr->data);
}
