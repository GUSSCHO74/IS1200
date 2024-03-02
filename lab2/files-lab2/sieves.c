#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define COLUMNS 6
int current_column = 0;

bool print_stuff = true;

void print_number(int n){
	printf("%10i ", n);

	if (++current_column >= COLUMNS){
		printf("\n");
		current_column = 0;
	}
}

void print_sieves(int n){
	// all values initially set to false (they're potentially prime), 
    // where true values are composites
	bool markings[n - 1] = {};

	for (int i = 2; i <= sqrt(n); i++){
        // i++ if index already marked, else execute code under
		if (markings[i - 2]) continue; 

		for (int j = pow(i, 2); j <= n; j += i)
			markings[j - 2] = true;
	}

	if (print_stuff){
		for (int i = 2; i <= n; i++){
			if (!markings[i - 2])
				print_number(i);
		}

		printf("\n");
	}
}

int main(int argc, char *argv[])
{
	if(argc >= 2){
		if (argc >= 3 && strcmp(argv[2], "no_print") == 0)
			print_stuff = false;
        
		print_sieves(atoi(argv[1]));
	}
	else
		printf("Please state an integer number.\n");

	return 0;
}