#include <stdio.h>

int swapIntegers1(int a, int b){ //Swaping integers using "temp" varibales, and then printing them

	int _tmp;

	_tmp = a;
	a = b;
	b =_tmp;

	printf("%d, %d", a, b);
	
	return 0;	
}

int swapIntegers2(int a, int b){ //Printing given integers in reverse order

	printf("%d, %d", b, a);
	
	return 0;	
}

int main()
{
	int a, b;
	scanf("%d %d", &a, &b);
	swapIntegers1(a, b);
    printf("\n");
    swapIntegers2(a, b);
    // The functionality and resultant output of both functions are the same.

	return 0;
}

