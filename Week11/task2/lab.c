#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<stdbool.h>
#include<math.h>

#define BUF_SIZE 1280
#define SIZE_MAX 1000
#define BRED -7756432

int cc = 0;
int forR = 0, forL = 0;

typedef struct Node{
	int value;
	struct Node *left;
	struct Node *right;
} Node_t;

Node_t* newNode(int val){
    Node_t *node = (Node_t*) malloc(sizeof(struct Node));
    node->value = val;
    node->left = NULL;
    node->right = NULL;
    return (node);

}

Node_t *pseudoQueue[SIZE_MAX];
int front = 0;
int rear = -1;
int numCount = 0;

Node_t* top() {
   return (pseudoQueue[front]);
}

bool isEmpty() {
   return numCount == 0;
}

bool isFull() {
   return numCount == SIZE_MAX;
}

void insertToQueue(Node_t *data) {

   if(!isFull()) {
      if(rear == SIZE_MAX-1) {
         rear = -1;            
      }       
      pseudoQueue[++rear] = data;
      numCount++;
   }
}

void deleteFromQueue() {
   Node_t *data = pseudoQueue[front++];

   if(front == SIZE_MAX) {
      front = 0;
   }
   numCount--;
}

void insert(Node_t* leaf, int key) 
{ 
    insertToQueue(leaf);

    while (!isEmpty()) { 
        Node_t* temp = top();
        deleteFromQueue();

        if (!temp->left) { 
            temp->left = newNode(key); 
            break; 
        } else
            insertToQueue(temp->left); 
        if (!temp->right) { 
            temp->right = newNode(key); 
            break; 
        } else{
            insertToQueue(temp->left); 
        }
    } 
}
  

void inorder_print(Node_t *leaf){
	if(leaf != NULL){
		inorder_print(leaf->left);
		printf("%d ,", leaf->value);
		inorder_print(leaf->right);
	}
}


int max(int a, int b){

    return a > b ? a : b;
}

int findMax(Node_t *root, int maxx){

    if(root == NULL){
        return 0;
    }
    
    int left = findMax(root->left, maxx);
    int right = findMax(root->right, maxx);
    
    int maxima = max(max(left, right) + root->value, root->value);

    int maximum = max(maxima, left + right + root->value);
    
    if(maximum > maxx){
        maxx = maximum;
    }
    
    return maxima;

}

char *my_fgets(char *str, int size_num, FILE *_infile){

    char _ch;
    int c;
    memset(str, NULL, size_num);
    for(int i = 0; i < size_num; i++){
      if(c != EOF){
        c = getc(_infile);
        str[i] = c;
        if(str[i] == '\xff'){
          str[i] = '\r\n';
           return 1;
        }
        if(c == '\n'){
            return str;
        }
      }else{
        if(str[i] == '\xff'){
          str[i] = '\r\n';
          return 1;
        }
        rewind(_infile);
        break;
      }
    }
    return 0;
}

int main(int argc, char** argv){
  if (argc < 2 ){
    fprintf(stderr, "needs at least one argument");
    exit(1);
  }

  FILE* infile = fopen(argv[1], "r");
  char str[BUF_SIZE], substr[1000], charr;
  str[BUF_SIZE-1] = '\0';
  int arr[1000][1000], sub_arr[1000];
  int c;
  bool isNumStart = false;
  int st = 0, ed = 0, it = 0, high_it = 0, sub_it = 0, j = 0;
  int outInt;
  Node_t *root = NULL;
  
  while(my_fgets(str, BUF_SIZE-1, infile)){
      it = 0;
      sub_it = 0;
      for(int k = 0; k < sizeof(str)/sizeof(char); k++){
          it ++;
          if((str[k] >= 48 && str[k] <= 57) && !isNumStart){
              isNumStart = true;
              st = it;
          }
          if(!(str[k] >= 48 && str[k] <= 57) && isNumStart){
              ed = it;
              j = 0;
              for(int i = st - 1; i <= ed; i++){
                  substr[j] = str[i];
                 
                  j ++;
              }
              substr[ed+1] = '\0';
               //printf("%s", substr);
              sub_arr[sub_it] = atoi(substr) == 0 ? BRED : atoi(substr);
              sub_it ++;
              st = 0;
              ed = 0;
              memset(substr, NULL, sizeof(substr)/sizeof(char));
              isNumStart = false;
          }
      }
      for(int i = 0; i < sizeof(sub_arr)/sizeof(int); i++){
          arr[high_it][i] = sub_arr[i];
      }
      high_it ++;
      memset(sub_arr, NULL, sizeof(substr)/sizeof(int));
  }

  for(int i = 0; i < high_it; i++){
      for(int j = 0; j < sizeof(arr[high_it])/sizeof(int); j++){
         if (arr[i][j] != 0) {
            if(arr[i][j] == BRED){
                outInt = 0;
            }else {
                outInt = arr[i][j];
            }
            if(root == NULL){
                root = newNode(outInt);
            }else{
                insert(root, outInt);
                forR = 0;
                forL = 0;
            }
            //printf("%d ", outInt);
         }
      }
      //printf("\n");
  }

  inorder_print(root);

  return 0;
}