#include <stdio.h>
#include <stdbool.h>

void printMaze(char **maze, const int HT, const int WD); // prints the maze

void solveMaze(char **maze, int *lastest_path[], const int HT, const int WD, int y, int x); // draws a path to the exit on the maze string

void encode2Darr(char **maze, const int HT, const int WD);

void decode2Darr(char **maze, const int HT, const int WD);

bool isSteped(int *array[2], int size, int i, int j);

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
    int a[HT*WD];
    int b[HT*WD];
    int *latest_path[2] = {a,b};

    for (int i=0; i<HT ; i++)		// filling the 2D char array
	maze[i]=&mazeStr[i*WD];

    encode2Darr(maze, HT, WD);
    
    solveMaze(maze, latest_path, HT, WD, 0, 0);

    decode2Darr(maze, HT, WD);
    
    printMaze(maze, HT, WD);
   
    return 0;
}

//Assuming the initial coordinate is 0;0
//Assuming the route exists for all cases
//Assuming there can be several routes butfunction drawing one of them
//Assuming borders as 0
//Assuming open routes  as 1
//Assuming checked and unsutable routes as 5
//Assuming target as 2
//Assuming founded route as 7


void solveMaze(char **maze, int *latest_path[], const int HT, const int WD, /*Why is these needed: x, and y ?*/ int y, int x){
    
    // solve recursively
    // however you might want to mark wrong paths with some other character
    // your functions should be able to solve other such mazes
    bool stucked = false;
    bool div_founded = false;
    bool triggered = false;
    int _a[HT*WD];
    int _b[HT*WD];
    int *arr_coordinates_hash[2] = {_a, _b};
    int arr_coordinates_hash_div[2][HT*WD];
    int count = 0;
    int _j = 0;
    int _jj = 0;
    int i = 0;
    int j = 0;

    while(!stucked && !triggered){
        if(maze[i][j + 1 < WD ? j + 1 : j] == (j + 1 < WD ? '2' : '0')){
                triggered = true;
        }
        if(maze[i + 1 < HT ? i + 1 : i][j] == (i + 1 < HT ? '2' : '0')){
                triggered = true;
        }
        if(maze[i][j - 1 >= 0 ? j - 1 : j] == (j - 1 >= 0 ? '2' : '0')){
                triggered = true;
        } 
        if(maze[i - 1 >= 0 ? i - 1 : i][j] == (i - 1 >= 0 ? '2' : '0')){
                triggered = true;
        } 
        if(((maze[i][j + 1 < WD ? j + 1 : j] == (j + 1 < WD ? '1' : '0')) || (maze[i][j + 1 < WD ? j + 1 : j] == (j + 1 < WD ? '5' : '0')))){
            count ++;
	    }
	    if(((maze[i + 1 < HT ? i + 1 : i][j] == (i + 1 < HT ? '1' : '0')) || (maze[i + 1 < HT ? i + 1 : i][j] == (i + 1 < HT ? '5' : '0')))){
	        count ++;
	    }
	    if(((maze[i][j - 1 >= 0 ? j - 1 : j] == (j - 1 >= 0 ? '1' : '0')) || (maze[i][j - 1 >= 0 ? j - 1 : j] == (j - 1 >= 0 ? '5' : '0')))){
	        count ++;
	    } 
	    if(((maze[i - 1 >= 0 ? i - 1 : i][j] == (i - 1 >= 0 ? '1' : '0')) || (maze[i - 1 >= 0 ? i - 1 : i][j] == (i - 1 >= 0 ? '5' : '0')))){
	        count ++;
	    } 
	    if(count >= 3){
	    	if(_jj == (HT*WD)/2){
	        	maze[arr_coordinates_hash[0][_j-1]][arr_coordinates_hash[1][_j-1]] = '5';
			}
	        arr_coordinates_hash_div[0][_jj] = i;
	        arr_coordinates_hash_div[1][_jj] = j;
	        _jj++;
	    }
	    count = 0;
	    
	    
        if(((maze[i][j + 1 < WD ? j + 1 : j] == (j + 1 < WD ? '1' : '0')) || (maze[i][j + 1 < WD ? j + 1 : j] == (j + 1 < WD ? '2' : '0'))) && !isSteped(arr_coordinates_hash, _j, i, j+1)){
            arr_coordinates_hash[0][_j] = i;
            arr_coordinates_hash[1][_j] = j + 1;
            _j++;
            j++;
            if(maze[i][j] == '2'){
                triggered = true;
            }
        }
        else if(((maze[i + 1 < HT ? i + 1 : i][j] == (i + 1 < HT ? '1' : '0')) || (maze[i + 1 < HT ? i + 1 : i][j] == (i + 1 < HT ? '2' : '0'))) && !isSteped(arr_coordinates_hash, _j, i + 1, j)){
            arr_coordinates_hash[0][_j] = i + 1;
            arr_coordinates_hash[1][_j] = j;
            _j++;
            i++;
            if(maze[i][j] == '2'){
                triggered = true;

            }
        }
        else if(((maze[i][j - 1 >= 0 ? j - 1 : j] == (j - 1 >= 0 ? '1' : '0')) || (maze[i][j - 1 >= 0 ? j - 1 : j] == (j - 1 >= 0 ? '2' : '0'))) && !isSteped(arr_coordinates_hash, _j, i, j-1)){
            arr_coordinates_hash[0][_j] = i;
            arr_coordinates_hash[1][_j] = j - 1;
            _j++;
            j--;
            if(maze[i][j] == '2'){
                triggered = true;
            }
        } 
        else if(((maze[i - 1 >= 0 ? i - 1 : i][j] == (i - 1 >= 0 ? '1' : '0')) || (maze[i - 1 >= 0 ? i - 1 : i][j] == (i - 1 >= 0 ? '2' : '0'))) && !isSteped(arr_coordinates_hash, _j, i-1, j)){
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
            for(int m = 0; m < _j ; m++){
            	if(!(arr_coordinates_hash[0][m] == arr_coordinates_hash_div[0][_jj - 1 >= 0 ? _jj-1 : 0] && arr_coordinates_hash[1][m] == arr_coordinates_hash_div[1][_jj - 1 >= 0 ? _jj-1 : 0])){

            		maze[arr_coordinates_hash[0][m]][arr_coordinates_hash[1][m]] = '1';
            	}else{

            		maze[arr_coordinates_hash[0][m]][arr_coordinates_hash[1][m]] = '1';
            		break;
				}
        }
        if(latest_path[0][_j-1] == arr_coordinates_hash[0][_j-1] &&  latest_path[1][_j-1] == arr_coordinates_hash[1][_j-1]){
					maze[arr_coordinates_hash[0][_j-1]][arr_coordinates_hash[1][_j-1]] = '5';
				}
				for(int m = 0; m < _j ; m++){
            	latest_path[0][m] = arr_coordinates_hash[0][m];
            	latest_path[1][m] = arr_coordinates_hash[1][m];
                
            }
            stucked = true;
        }
    }
    if(!triggered){
        solveMaze(maze, latest_path, HT, WD, 0, 0);
    }else{
        for(int m = 0; m < _j-1 ; m++){
            maze[arr_coordinates_hash[0][m]][arr_coordinates_hash[1][m]] = '7';
        }
    }
}


bool isSteped(int *array[2], int size, int i, int j){
	
	for(int _k = 0; _k < size - 2; _k++){
		if(array[0][_k] == i && array[1][_k] == j)
		return true;
	}
	return false;
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
    maze[0][0] = '.';

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