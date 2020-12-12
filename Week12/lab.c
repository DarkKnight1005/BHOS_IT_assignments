#include<stdlib.h>
#include<stdio.h>
#include<stdbool.h>

#define BUF_SIZE 10000
#define BRED -1

int my_strlen (const char *str)
{
    int len;
    for (len = 0 ;; len++){
        if (str[len] == 0){ 
            return len;
        }
    }
}

int my_strcmp(char *str1, char *str2, int size){
    for(int i = 0; i < size; i++){
        if(str1[i] != str2[i]){
            return BRED;
        }
    }
    return 0;
}

int my_strchr(char *str1, char character, int size){
    for(int i = 0; i < size; i++){
        if(str1[i] == character){
            return i;
        }
    }
    return NULL;
}

int main(int argc, char** argv){
    if (argc < 2 ){
        fprintf(stderr, "needs at least one argument");
        exit(1);
    }
    FILE* infile = fopen(argv[1], "r");
    char *str = (char*)malloc(sizeof(char)*BUF_SIZE);
    char *substr = (char*)malloc(sizeof(char)*BUF_SIZE);
    char *password = (char*)malloc(sizeof(char)*BUF_SIZE);
    int *arr = (int*)malloc(sizeof(int)*BUF_SIZE);
    bool isNumStart = false, isFisrtNumber = true;
    int st = 0, ed = 0, high_it = 0, sub_it = 0, j = 0, k = 0, i = 0, tries;
    int outInt;
    fgets(str, BUF_SIZE - 1, infile);
    sub_it = 0;
    int strLen = sizeof(str)/sizeof(char) + 1;
    for(k = 0; k < strLen; k++){
        if((str[k] >= 48 && str[k] <= 57) && !isNumStart){
            isNumStart = true;
            st = k;
            if(isFisrtNumber){
                j = 0;
                for(int i = 0; i < k - 1; i++){
                    password[j] = str[i];
                    j ++;
                }
                isFisrtNumber = false;
            }
        }
        if((!(str[k] >= 48 && str[k] <= 57) && isNumStart) || k == strLen - 1){
            ed = k;
            j = 0;
            for(int i = st; i <= ed; i++){
                substr[j] = str[i];
                j ++;
            }
            substr[ed+1] = '\0';
            arr[sub_it] = atoi(substr) == 0 ? BRED : atoi(substr);
            sub_it ++;
            st = 0;
            ed = 0;
            //free(substr);
            free(substr);
            *substr = (char*)malloc(sizeof(char)*BUF_SIZE);
            //memset(substr, NULL, sizeof(substr)/sizeof(char));
            isNumStart = false;
        }
    }
    free(substr);
    free(str);
    *str = (char*)malloc(sizeof(char)*BUF_SIZE);
    printf("Welcome to Fallout 3 hacking minigame! \nThe passphrase contains %d letters. \n \n", arr[0]);
    for(int i = 0; i < arr[1]; i++){
        tries = arr[1] - i;
        printf("you have %d tries left: ", tries);
        scanf("%s", str);
        //printf("\n");
        if(my_strcmp(str, "!quit", arr[0]) == 0){
            return 0;
        }
        if(my_strlen(str) != arr[0]){
            printf("Wrong number of characters, try again. \n");
            i --;
        }else{
            if(my_strcmp(str, password, arr[0]) == 0){
                printf("correct, here's how you did: \n");
                printf("%s \n", str);
                for(int j = 0; j < my_strlen(str); j++){
                    printf("+");
                }
                printf("\n");
                printf("you win.");
                break;
            }else{
                printf("incorrect, here's how you did: \n");
                printf("%s \n", str);
                for(int k = 0; k < my_strlen(str); k++){
                    if(str[k] == password[k]){
                        printf("+");
                    }else if(my_strchr(password, str[k], arr[0]) != NULL){
                        printf("!");
                    }else{
                        printf(".");
                    }
                }
                printf("\n");
                tries == 1 ? printf("game over.") : printf("try again.");
                printf("\n");
            }
        }
    }
    free(str);
    free(password);
    free(arr);
    
    return 0;
}