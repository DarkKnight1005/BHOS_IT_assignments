#include "stdio.h"
#include "string.h"

#define MAX_VAL 100000

void swapStrings(char *destination, char *source);           

int main(){
    char str1[MAX_VAL] = "My World";
    char str2[MAX_VAL] = "Hello";
    // define and initialize str1
    // define and initialize str2

    printf("str1: %s, str2: %s\n",str1,str2);
    swapStrings(str1,str2);
    printf("str1: %s, str2: %s\n",str1,str2);

    return 0;
}

void swapStrings(char *destination, char *source){

    char _tempStr[MAX_VAL];
    int _strlenDest = strlen(destination);
    int _strlenSource = strlen(source);
    for (int i = 0; i < _strlenDest; i++)
    {
        _tempStr[i] = destination[i];
        destination[i] = NULL;
    }
    for (int i = 0; i < _strlenSource; i++)
    {
        destination[i] = source[i];
        source[i] = NULL;
    }
    for (int i = 0; i < _strlenDest; i++)
    {
        source[i] = _tempStr[i];
    }
    

    // swaps contents of two strings
    // implement this function without using any built in functions
}