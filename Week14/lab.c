#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<stdbool.h>

char swappeds[1000];
int ind = 0;

typedef struct Node {

    char data[256];
    struct Node *next;
} Node_t;

void append(Node_t **head_ref, char *new_data) {
    Node_t *new_node = (Node_t *) malloc(sizeof(Node_t));
    Node_t *last = *head_ref;
    strcpy(new_node->data, new_data);
    new_node->next = NULL;
    while (last->next != NULL)
        last = last->next;
    last->next = new_node;
}

void swap(Node_t **head_ref, char *swapper_char){
    Node_t *prev = *head_ref;
    Node_t *_tmp = NULL;
    bool bb = true;
    while (bb){
        if(strcmp(prev->next->data, swapper_char) != 0){
           prev = prev->next;
        }else{
            _tmp = prev->next->next->next;
            bb = false;
        }
    }
    Node_t *tmp = prev->next;
    swappeds[ind] = atoi(prev->next->data);
    ind++;
    swappeds[ind] = atoi(prev->next->next->data);
    ind++;
    prev->next = prev->next->next;
    prev->next->next = tmp;
    prev->next->next->next = _tmp;
} 

void print_list(Node_t *node) {
    printf("result:");
    while (node != NULL) {
        printf("%s ", node->data);
        node = node->next;
    }
    printf("\n");
}


int main() {
    //NOTE!!! Should we change the other positions if once again 5 is enetered or if one of 5's is already changed it means that no more 5's can be changed ?
    Node_t *head = (Node_t *) malloc(sizeof(Node_t));
    char str[256];
    bool isDone = false;
    bool isSwapped = false;
    printf("Enter numbers to add to your list:\n");
    while(!isDone){
        scanf("%s", str);
        if(strcmp(str, "DONE") == 0){
            isDone = true;
        }else{
            append(&head, str);
        }
    }
    isDone = false;
    while(!isDone){
        scanf("%s", str);
        if(strcmp(str, "DONE") == 0){
            isDone = true;
        }else{
            int num = atoi(str);
            for (int i = 0; i < ind; i++)
            {
                if(swappeds[i] == num){
                    isSwapped = true;
                    break;
                }
            }
            if(!isSwapped){
                swap(&head, str);
                print_list(head);
            }else{
                isSwapped = false;
                printf("No swap candidates found. Try again:\n");
            }
        }
    }

    printf("\n");


    return 0;
}