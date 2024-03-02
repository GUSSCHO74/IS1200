#include <stdio.h>
#include <stdlib.h>

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
  printf("%10d", n); // number gets aligned within 10 digits space
  count++;
 
  // new line if row reaches 6 numbers
  if (count == COLUMNS) {
    printf("\n");
    count = 0;
  }
}

void print_primes(int n){
  for(int i = 2; i <= n; i++){
    if (is_prime(i))
      print_number(i);
  }
  printf("\n");
}

// 'argc' contains the number of program arguments, and
// 'argv' is an array of char pointers, where each
// char pointer points to a null-terminated string.
int main(int argc, char *argv[]){
  if(argc == 2)
    print_primes(atoi(argv[1]));
  else
    printf("Please state an interger number.\n");
  return 0;
}