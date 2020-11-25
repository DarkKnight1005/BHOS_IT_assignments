#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//stin, stdout, stderr

#define BUF_SIZE 1280

char *my_fgets(char *str, int size_num, FILE *_infile){

    char _ch;
    int c;
    //int k = 0, i;
    memset(str, NULL, size_num);
    //str = "\0';
    for(int i = 0; i < size_num; i++){
      if(c != EOF){
        c = getc(_infile);
        str[i] = c;
        if(c == '\n'){
          str[i] = c;
            return str;
        }
      }else{
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
  
  while(my_fgets(str, BUF_SIZE-1, infile)){
    printf("%s", str);
  }

  // memset(str, 0, sizeof(str)/sizeof(char));

  // while(my_fgets(str, BUF_SIZE-1, infile)){
  //   printf("%s", str);
  // }

  
  return(0);
}