#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>


#define COLUMNS 6
int count = 0;

int is_prime(int n){
  for(int i = 2; i < n; i++){
    if(n % i == 0)
      return 0;
  }
  return 1;
}

void print_number(int n){
  printf("%10d", n);
  count++;

  if (count == COLUMNS) {
      printf("\n");
      count = 0;
  }
}

void print_sieves(int n) {
    // Create array of boolean values on heap
    bool *A = (bool*)malloc((n - 1) * sizeof(bool));

    for (int i = 2; i <= n; i++) {
        A[i] = true;
    }

    // sieve of Eratosthenes algorithm
    for (int i = 2; i <= sqrt(n); i++) {
        if (A[i] == true) {
            for (int j = i * i; j <= n; j += i)
                A[j] = false;
        }
    }

    // Print primes
    for (int i = 2; i <= n; i++) {
        if (A[i] && is_prime(i)) 
            print_number(i);
    }

    printf("\n");
    
    // Release allocated memory
    free(A);
}

int main(int argc, char *argv[]){
  if(argc == 2)
    print_sieves(atoi(argv[1]));
  else
    printf("Please state an interger number.\n");
  return 0;
}