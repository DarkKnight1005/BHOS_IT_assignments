#include <limits.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <stdbool.h>

#define STACK_CAPACITY 2 
#define N 5000

struct Stack { 
    char top; 
    unsigned capacity; 
    char* array; 
}; 

struct Stack* createStack() 
{ 
    struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack)); 
    stack->capacity = STACK_CAPACITY; 
    stack->top = '1'; 
    stack->array = (char*)malloc(stack->capacity * sizeof(char)); 
    return stack; 
} 

// deallocates the dynamic memory to prevent memory leak
void deallocStack(struct Stack* stack) 
{ 
    free(stack->array);
    free(stack);
    //printf("deallocated\n"); 
} 

int isFull(struct Stack* stack) 
{ 
    return stack->top == stack->capacity - 1; 
} 
  
bool isEmpty(struct Stack* stack) 
{ 
    return stack->top == '1'; 
} 

void resize(struct Stack* stack) 
{
    stack->capacity *= 2;
    stack->array = (char*)realloc(stack->array,stack->capacity * sizeof(char));
   // printf("stack reallocated, new length: %d\n",stack->capacity);
} 

void push(struct Stack* stack, char item) 
{ 
    if (isFull(stack)) 
        resize(stack);
    stack->array[++stack->top] = item; 
    //printf("%d pushed to stack\n", item); 
} 
  
int pop(struct Stack* stack) 
{ 
    if (isEmpty(stack)) 
        return INT_MIN; 
    return stack->array[stack->top--]; 
} 
  
int peek(struct Stack* stack) 
{ 
    if (isEmpty(stack)) 
        return INT_MIN; 
    return stack->array[stack->top]; 
} 

//assuming opening bractes as (, {, [
bool isOpeningBracket(char br){
   
    if(br == '(' || br == '{' || br == '['){

        return true;
    }else{
        return false;
    }
}

bool isAppropriate(char open, char close){
    if(('(' == open && ')' == close) || ('{' == open && '}' == close) || ('[' == open && ']' == close)){
        return true;
    }else{
        return false;
    }
}

  
int main() 
{ 
    int len = 0, i;
    bool isBalanced;
    char str[N];
    struct Stack* stack = createStack(); 
    scanf("%s", str);
    len = sizeof(str)/sizeof(char);
    for(i = 0; i < len; i++){
        if(str[i] == NULL) break;
    }
    len = i;
    if(!(len & 1)){
    for(i = 0; i < len; i++){
        if(isOpeningBracket(str[i])){
            push(stack, str[i]);
        }
        else if(isAppropriate(peek(stack), str[i])){
            pop(stack);
        }
        else{
            isBalanced = false;
            printf("Not Balanced \n");
            return 0;
        }
    }
    //isEmpty(stack) ? isBalanced = true : isBalanced = false;
    if(isEmpty(stack)){
        isBalanced = true;
    }else{
        isBalanced = false;
    }
    }else{
        isBalanced = false;
    }

    isBalanced ? printf("Balanced \n") : printf("Not Balanced \n");

    deallocStack(stack);
    return 0; 
} 