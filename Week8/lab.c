#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<stdbool.h>


bool isErr = false;

typedef struct Node {

    char data[256];
    struct Node *next;
} Node_t;

void print_list(Node_t *node) {
    while (node != NULL) {
        printf("%s ", node->data);
        node = node->next;
    }
}

void free_up(Node_t *node) {
    while (node != NULL) {
        free(node);
        node = node->next;
    }
}

void push(Node_t **head_ref, char *new_data) {
    Node_t *new_node = (Node_t *) malloc(sizeof(Node_t));
    //new_node->data = new_data;
    strcpy(new_node->data, new_data);
    new_node->next = (*head_ref);
    (*head_ref) = new_node;
} 

void append(Node_t **head_ref, char *new_data) {
    Node_t *new_node = (Node_t *) malloc(sizeof(Node_t));
    Node_t *last = *head_ref;
    strcpy(new_node->data, new_data);
    new_node->next = NULL;
    while (last->next != NULL)
        last = last->next;
    last->next = new_node;
}

void insertAfter(Node_t *prev_node, char *new_data) {
    if (prev_node == NULL) {
        printf("ERROR: previos node is NULL");
        return;
    }
    Node_t *new_node = (Node_t *) malloc(sizeof(Node_t));
    strcpy(new_node->data, new_data);
    new_node->next = prev_node->next;
    prev_node->next = new_node;
}

void deleteNode(Node_t **head_ref, char *key) 
{ 
    Node_t *temp = *head_ref;
    Node_t *prev;

    if (temp != NULL && strcmp(temp->data, key) == 0) { 
        *head_ref = temp->next;  
        free(temp);              
        return; 
    } 
    while (temp != NULL && strcmp(temp->data, key) != 0) { 
        prev = temp; 
        temp = temp->next; 
    } 
    if (temp == NULL){ 
        printf("There is no such user \n");
        isErr = true;
        return; 
    }
    prev->next = temp->next; 
    free(temp); 
} 
  

int main() {

    Node_t *head = (Node_t *) malloc(sizeof(Node_t));
    Node_t *second = (Node_t *) malloc(sizeof(Node_t));
    Node_t *third = (Node_t *) malloc(sizeof(Node_t));
    char input[256];
    bool quit = 0;

    strcpy(head->data, "Turgut");
    head->next = NULL;
    append(&head, "Nazrin");
    append(&head, "Nigar");
    append(&head, "Kamran");
    append(&head, "Eljan");

    print_list(head);
    printf("\n");

    while(!quit) {
    scanf("%s" , input);
    if (strcmp(input,"quit") == 0) {
        quit = 1;
        free_up(head);
    }
    else if (strcmp(input,"admit") == 0) {
        deleteNode(&head, head->data);
    }
    else{
        deleteNode(&head, input);
        if(!isErr){
        append(&head, input);
        }
        isErr = false;
    }

    print_list(head);
    printf("\n");

    }

    return 0;
}