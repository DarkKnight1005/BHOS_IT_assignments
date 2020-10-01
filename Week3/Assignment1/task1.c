#include "stdio.h"
#include "string.h"
void swapArrays(int a1[], int a2[], int len);           
void print2DArr(int *arr2D[], int rows, int columns);

int main(){
    int a1[] = {1,2,3,4,5};
    int a2[] = {0,0,0,0,0};
    int len = sizeof(a1)/sizeof(int);

    int *arr2D[2] = {a1,a2};
                                    
    print2DArr(arr2D, 2, len);
    swapArrays(a1, a2, len);
    printf("\n");
    print2DArr(arr2D, 2, len);
    return 0;
}
void swapArrays(int a1[], int a2[], int len){
    int _temp[len];
    
    for (int i = 0; i < len; i++)
    {
        _temp[i] = a1[i];
    }
    for (int i = 0; i < len; i++)
    {
        a1[i] = a2[i];
    } 
    for (int i = 0; i < len; i++)
    {
        a2[i] = _temp[i];
    }
    
}
void print2DArr(int *arr2D[], int rows, int columns){
    for(int i=0; i<rows; i++){
        for (int j = 0; j < columns; j++){
            if(i == rows-1 && j == columns-1){
                printf("%d", arr2D[i][j]);
            }else{
                printf("%d ", arr2D[i][j]);
            }
        }
        
    }
    // prints contents of the 2D array in a flattened shape
    // eg: [[1,2],[3,4]] will be printed as 1 2 3 4\n
    // make sure there is no empty ' ' printed after the last element
}