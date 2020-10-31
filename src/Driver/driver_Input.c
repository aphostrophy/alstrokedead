#include "../Header/input.h"
#include<stdio.h>

int main(){

	int c;
	while (1){
		c = GetInput();
		printf("Input yang dimasukkan %c!\n", c);
		printf("Nilai integernya %d!\n", c);
	}
	
}