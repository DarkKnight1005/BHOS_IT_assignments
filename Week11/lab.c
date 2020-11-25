#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//stin, stdout, stderr

#define BUF_SIZE 12800

char *my_fgets(char *str, int size_num, FILE *_infile){

    int count = 0;
    char *_char;
    //size_num--;
    _char = str;
    char buf[BUF_SIZE];
    buf[BUF_SIZE-1] = '\0';  
    int k = 0;

    for(int i = k; i < size_num; i++){
        fread(buf, k, i - k, _infile);
        if(buf[i-1] == '\n' || buf[i-1] == '\0' || buf[i-1] == 0){
            k = i;
            fprintf(stdout,"%s",buf);
            memset(buf, 0, BUF_SIZE);
        }
        //if(fread(buf, k, i - k, _infile) == 0){break;}
    }
}

int main(int argc, char** argv){
  if (argc < 2 ){
    fprintf(stderr, "needs at least one argument");
    exit(1);
  }

  FILE* infile = fopen(argv[1], "r");
  char *str[128];

  my_fgets(*str, 127, infile);
  
//   char buf[BUF_SIZE];
//   buf[BUF_SIZE-1] = '\0';  
 
//   while ( fread(buf, 1, sizeof(buf)-1, infile) !=0 ){
//   	fprintf(stdout,"%s",buf);
// 	memset(buf, 0, BUF_SIZE);
//   }

  return(0);
}