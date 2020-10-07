#include <stdio.h>
#include <stdbool.h>

void printMaze(char **maze, const int HT, const int WD); // prints the maze

void solveMaze(char **maze, const int HT, const int WD, int y, int x); // draws a path to the exit on the maze string

void encode2Darr(char **maze, const int HT, const int WD);

void decode2Darr(char **maze, const int HT, const int WD);


int main(){
    char mazeStr[] ="  ##############"
                    "#     #     ####"
                    "# ####* ### ####"
                    "#    ###### ####"
                    "#### # #### ####"
                    "#    # #### ####"
                    "#### # #### ####"
                    "####        ####"
                    "################";
    const int HT = 9;
    const int WD = 16;
    char *maze[HT];

    for (int i=0; i<HT ; i++)		// filling the 2D char array
	maze[i]=&mazeStr[i*WD];

    encode2Darr(maze, HT, WD);
    
    solveMaze(maze, HT, WD, 0, 0);

    decode2Darr(maze, HT, WD);
    
    printMaze(maze, HT, WD);
   
    return 0;
}

//Assuming the initial coordinate is 0;0
//Assuming the route exists for all cases
//Assuming borders as 0
//Assuming open routes  as 1
//Assuming checked and unsutable routes as 5
//Assuming traget as 2
//Assuming founded route as 7


void solveMaze(char **maze, const int HT, const int WD, /*Why is these needed: x, and y ?*/ int y, int x){
    
    // solve recursively
    // however you might want to mark wrong paths with some other character
    // your functions should be able to solve other such mazes
    bool stucked = false;
    bool div_founded = false;
    bool triggered = false;
    //bool cond1, cond2, cond3, cond4;
    int arr_coordinates_hash[2][HT*WD];
    int arr_coordinates_hash_div[2][HT*WD];
    int count = 0;
    //int _i = 0;
    int _j = 0;
    int _jj = 0;
    int i = 0;
    int j = 0;


    while(!stucked || !triggered){
        if(((maze[i][j + 1 < WD ? j + 1 : j] == (j + 1 < WD ? '1' : '0')) || (maze[i][j + 1 < WD ? j + 1 : j] == (j + 1 < WD ? '2' : '0'))) && !(arr_coordinates_hash[0][_j-2] == i && arr_coordinates_hash[1][_j-2] == j + 1)){
            arr_coordinates_hash[0][_j] = i;
            arr_coordinates_hash[1][_j] = j + 1;
            _j++;
            j++;
            if(maze[i][j] == '2'){
                triggered = true;
            }
        }
        else if(((maze[i + 1 < HT ? i + 1 : i][j] == (i + 1 < HT ? '1' : '0')) || (maze[i + 1 < HT ? i + 1 : i][j] == (i + 1 < HT ? '2' : '0'))) && !(arr_coordinates_hash[0][_j-2] == i + 1 && arr_coordinates_hash[1][_j-2] == j)){
            arr_coordinates_hash[0][_j] = i + 1;
            arr_coordinates_hash[1][_j] = j;
            _j++;
            i++;
            if(maze[i][j] == '2'){
                triggered = true;

            }
        }
        else if(((maze[i][j - 1 >= 0 ? j - 1 : j] == (j - 1 >= 0 ? '1' : '0')) || (maze[i][j - 1 >= 0 ? j - 1 : j] == (j - 1 >= 0 ? '2' : '0'))) && !(arr_coordinates_hash[0][_j-2] == i && arr_coordinates_hash[1][_j-2] == j - 1)){
            arr_coordinates_hash[0][_j] = i;
            arr_coordinates_hash[1][_j] = j - 1;
            _j++;
            j--;
            if(maze[i][j] == '2'){
                triggered = true;
            }
        } 
        else if(((maze[i - 1 >= 0 ? i - 1 : i][j] == (i - 1 >= 0 ? '1' : '0')) || (maze[i - 1 >= 0 ? i - 1 : i][j] == (i - 1 >= 0 ? '2' : '0'))) && !(arr_coordinates_hash[0][_j-2] == i - 1 && arr_coordinates_hash[1][_j-2] == j)){
            arr_coordinates_hash[0][_j] = i - 1;
            arr_coordinates_hash[1][_j] = j;
            _j++;
            i--;
            if(maze[i][j] == '2'){
                triggered = true;
            }
        } 
        else{
            //stuck
            for(int m = 0; m < _j ; m++){
                maze[arr_coordinates_hash[0][m]][arr_coordinates_hash[1][m]] = '5';
            }
            for(int m = 0; m < HT*WD ; m++){
                for(int n = 0; n < 2; n++){
                   arr_coordinates_hash[n][m] = NULL;
                }
            }
            for(int i = 0; i < HT; i++){
                for(int j = 0; j < WD; j++){
                    if(((maze[i][j + 1 < WD ? j + 1 : j] == (j + 1 < WD ? '1' : '0')) || (maze[i][j + 1 < WD ? j + 1 : j] == (j + 1 < WD ? '5' : '0'))) && maze[i][j] == '5'){
                        count ++;
                    }
                    if(((maze[i + 1 < HT ? i + 1 : i][j] == (i + 1 < HT ? '1' : '0')) || (maze[i + 1 < HT ? i + 1 : i][j] == (i + 1 < HT ? '5' : '0'))) && maze[i][j] == '5'){
                        count ++;
                    }
                    if(((maze[i][j - 1 >= 0 ? j - 1 : j] == (j - 1 >= 0 ? '1' : '0')) || (maze[i][j - 1 >= 0 ? j - 1 : j] == (j - 1 >= 0 ? '5' : '0'))) && maze[i][j] == '5'){
                        count ++;
                    } 
                    if(((maze[i - 1 >= 0 ? i - 1 : i][j] == (i - 1 >= 0 ? '1' : '0')) || (maze[i - 1 >= 0 ? i - 1 : i][j] == (i - 1 >= 0 ? '5' : '0'))) && maze[i][j] == '5'){
                        count ++;
                    } 
                    if(count >= 3){
                        arr_coordinates_hash_div[0][_jj] = i;
                        arr_coordinates_hash_div[1][_jj] = j;
                        _jj++;
                    }
                    count = 0;
                }
            } 
            for(int m = 0; m < _jj; m++){
                maze[arr_coordinates_hash_div[0][m]][arr_coordinates_hash_div[1][m]] = '6';
            }
            i = 0;
            j = 0;
            for(int m = 0; m < _jj; m++){
               while(!div_founded){
                if(((maze[i][j + 1 < WD ? j + 1 : j] == (j + 1 < WD ? '1' : '0')) || (maze[i][j + 1 < WD ? j + 1 : j] == (j + 1 < WD ? '5' : '0')) || (maze[i][j + 1 < WD ? j + 1 : j] == (j + 1 < WD ? '6' : '0'))) && !(arr_coordinates_hash[0][_j-2] == i && arr_coordinates_hash[1][_j-2] == j + 1)){
                        arr_coordinates_hash[0][_j] = i;
                        arr_coordinates_hash[1][_j] = j + 1;
                        _j++;
                        j++;
                        if(maze[i][j] == '6'){
                            div_founded = true;
                        }
                    }
                    else if(((maze[i + 1 < HT ? i + 1 : i][j] == (i + 1 < HT ? '1' : '0')) || (maze[i + 1 < HT ? i + 1 : i][j] == (i + 1 < HT ? '5' : '0')) || (maze[i + 1 < HT ? i + 1 : i][j] == (i + 1 < HT ? '6' : '0'))) && !(arr_coordinates_hash[0][_j-2] == i + 1 && arr_coordinates_hash[1][_j-2] == j)){
                        arr_coordinates_hash[0][_j] = i + 1;
                        arr_coordinates_hash[1][_j] = j;
                        _j++;
                        i++;
                        if(maze[i][j] == '6'){
                            div_founded = true;
                        }
                    }
                    else if(((maze[i][j - 1 >= 0 ? j - 1 : j] == (j - 1 >= 0 ? '1' : '0')) || (maze[i][j - 1 >= 0 ? j - 1 : j] == (j - 1 >= 0 ? '5' : '0')) || (maze[i][j - 1 >= 0 ? j - 1 : j] == (j - 1 >= 0 ? '6' : '0'))) && !(arr_coordinates_hash[0][_j-2] == i && arr_coordinates_hash[1][_j-2] == j - 1)){
                        arr_coordinates_hash[0][_j] = i;
                        arr_coordinates_hash[1][_j] = j - 1;
                        _j++;
                        j--;
                        if(maze[i][j] == '6'){
                            div_founded = true;
                        }
                    } 
                    else if(((maze[i - 1 >= 0 ? i - 1 : i][j] == (i - 1 >= 0 ? '1' : '0')) || (maze[i - 1 >= 0 ? i - 1 : i][j] == (i - 1 >= 0 ? '5' : '0')) || (maze[i - 1 >= 0 ? i - 1 : i][j] == (i - 1 >= 0 ? '6' : '0'))) && !(arr_coordinates_hash[0][_j-2] == i - 1 && arr_coordinates_hash[1][_j-2] == j)){
                        arr_coordinates_hash[0][_j] = i - 1;
                        arr_coordinates_hash[1][_j] = j;
                        _j++;
                        i--;
                        if(maze[i][j] == '6'){
                            div_founded = true;
                        }
                    }  
                }
                for(int l = 0; l < _j ; l++){
                maze[arr_coordinates_hash[0][l]][arr_coordinates_hash[1][l]] = '1';
                }
                for(int l = 0; l < HT*WD ; l++){
                    for(int k = 0; k < 2; k++){
                    arr_coordinates_hash[k][l] = NULL;
                    }
                }
                i = 0;
                j = 0;
                div_founded = false;
            }
            
            stucked = true;
        }
    }
    if(!triggered){
        solveMaze(maze, HT, WD, 0, 0);
    }else{
        for(int m = 0; m < _j-1 ; m++){
            maze[arr_coordinates_hash[0][m]][arr_coordinates_hash[1][m]] = '7';
        }
    }
}

void encode2Darr(char **maze, const int HT, const int WD){

    for(int i = 0; i < HT; i++){
        for(int j = 0; j < WD; j++){
            if(maze[i][j] == '#'){
                maze[i][j] = '0';
            }
            else if(maze[i][j] != '*'){
                maze[i][j] = '1';
            }
            else{
                maze[i][j] = '2';
            }
        }
    }    

}

void decode2Darr(char **maze, const int HT, const int WD){
    
    for(int i = 0; i < HT; i++){
        for(int j = 0; j < WD; j++){
            if(maze[i][j] == '1' || maze[i][j] == '5'){
                maze[i][j] = ' ';
            }
            else if(maze[i][j] == '0'){
                maze[i][j] = '#';
            }
            else if(maze[i][j] == '7'){
                maze[i][j] = '.';
            }
            else if(maze[i][j] == '2'){
                maze[i][j] = '*';
            }
        }
    }  

}



void printMaze(char **maze, const int HT, const int WD){
    
    // for (int i=0; i<HT ; i++){
	// for(int j=0; j<WD-1; j++)
	//   printf("%c",maze[i][j]);
	// printf("%c\n",maze[i][WD-1]);
    // }

    for (int i=0; i<HT ; i++){
	for(int j=0; j<WD; j++)
	  printf("%c",maze[i][j]);
	printf("\n");
    }

}