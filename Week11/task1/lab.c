#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//stin, stdout, stderr

#define BUF_SIZE 1280

int cc = 0;

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
  char str[BUF_SIZE];
  str[BUF_SIZE-1] = '\0';
  
    while(my_fgets(str, BUF_SIZE-1, infile)){
    printf("%s", str);
  }

  // memset(str, 0, sizeof(str)/sizeof(char));

  // while(my_fgets(str, BUF_SIZE-1, infile)){
  //   printf("%s", str);
  // }

  
  return(0);
}