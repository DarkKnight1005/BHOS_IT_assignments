#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<stdbool.h>

#define BUF_SIZE 10000
#define BRED -1

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
    for(k = 0; k < strlen(str); k++){
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
        if((!(str[k] >= 48 && str[k] <= 57) && isNumStart) || k == strlen(str) - 1){
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
            memset(substr, NULL, sizeof(substr)/sizeof(char));
            isNumStart = false;
        }
    }
    free(substr);
    memset(str, NULL, sizeof(str)/sizeof(char));

    printf("Welcome to Fallout 3 hacking minigame! \nThe passphrase contains %d letters. \n \n", arr[0]);

    for(int i = 0; i < arr[1]; i++){
        tries = arr[1] - i;
        printf("you have %d tries left: ", tries);
        scanf("%s", str);
        //printf("\n");
        if(strcmp(str, "!quit") == 0){
            return 0;
        }
        if(strlen(str) != arr[0]){
            printf("Wrong number of characters, try again. \n");
            i --;
        }else{
            if(strcmp(str, password) == 0){
                printf("correct, here's how you did: \n");
                printf("%s \n", str);
                for(int j = 0; j < strlen(str); j++){
                    printf("+");
                }
                printf("\n");
                printf("you win.");
                break;
            }else{
                printf("incorrect, here's how you did: \n");
                printf("%s \n", str);
                for(int k = 0; k < strlen(str); k++){
                    if(str[k] == password[k]){
                        printf("+");
                    }else if(strchr(password, str[k]) != NULL){
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