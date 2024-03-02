#include <stdio.h>
#include <stdint.h>

char* text1 = "This is a string.";
char* text2 = "Yet another thing.";

int list1[80];
int list2[80];
int count = 0;

void copycodes(char *p_text, int *p_list, int *p_count)
{
	for (;;)
	{
		char t0 = *p_text;  // lb  $t0, 0($a0)
		if (t0 == 0) break; // beq $t0, $0, done
		*p_list = t0;       // sw  $t0, 0($a1)

		p_text++;           // addi $a0, $a0, 1
		p_list++;           // addi $a1, $a1, 4

		                    // lw   $t1, 0($a2)
		(*p_count)++;       // addi $t1, $t1, 1
		                    // sw   $t1, 0($a2)
	}
}

void work()
{
	/*
		la  $a0,text1
		la  $a1,list1
		la  $a2,count
		jal copycodes
	*/
	copycodes(text1, list1, &count);
	/*
		la  $a0,text2
		la  $a1,list2
		la  $a2,count
		jal copycodes
	*/
	copycodes(text2, list2, &count);
}

void printlist(const int* lst){
  printf("ASCII codes and corresponding characters.\n");
  while(*lst != 0){
    printf("0x%03X '%c' ", *lst, (char)*lst);
    lst++;
  }
  printf("\n");
}

void endian_proof(const char* c){
  printf("\nEndian experiment: 0x%02x,0x%02x,0x%02x,0x%02x\n",
         (int)*c,(int)*(c+1), (int)*(c+2), (int)*(c+3));
}

int main(void){
  work();

  printf("\nlist1: ");
  printlist(list1);
  printf("\nlist2: ");
  printlist(list2);
  printf("\nCount = %d\n", count);

  endian_proof((char*) &count);

  int n = 1;
  // little endian if true
  if(*(char *)&n == 1) {
	printf("little endian\n");
  } else {
	printf("big endian\n");
  }
}