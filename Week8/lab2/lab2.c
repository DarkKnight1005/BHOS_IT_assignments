#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<stdbool.h>

void handler(char *source, char *ints, char *nonints, int size){
    int j = 0, k = 0, i = 0;
    for(i = 0; i < size; i++){
        if(source[i] >= 48 && source[i] <= 57){
            ints[j] = source[i];
            j++;
        }else{
            nonints[k] = source[i];
            k++;
        }
    }
}

int main() {

    char source[] = "hwbq87r3bffdvgh9g8!@y843fblwp8u4heno)(&^hufhh";
    char ints[256];
    char nonints[256];
    handler(source, ints, nonints, sizeof(source)/sizeof(char));
    printf("ints: %s \n nonints: %s \n", ints, nonints);
    return 0;
}