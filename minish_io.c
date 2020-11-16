#include <stdio.h>
#include <unistd.h>
#include "minish_io.h"

void take_input(char* input) 
{ 
    fflush(stdin);
    gets(input); 
} 
  
void print_shell() 
{ 
    char cwd[MAX_DIR_SIZE];
    char* username = getlogin();
    getcwd(cwd, sizeof(cwd)); 
    fflush(stdout);
    printf("%s:%s$ ",username, cwd); 
} 