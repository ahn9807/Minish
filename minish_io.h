#ifndef _MINISH_IO_H_
#define _MINISH_IO_H_

#define clear() printf("\033[H\033[J") 
#define MAX_DIR_SIZE 512

void take_input(char* input);
void print_shell();

#endif