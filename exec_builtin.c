#include "exec_builtin.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int check_builtin(char* input) {
    if(!strcmp("quit", input)) {
        return 1;
    } 
    if(!strcmp("pwd", input)) {
        return 2;
    } 
    if(!strcmp("cd", input)) {
        return 3;
    }
    if(!strcmp("cap", input)) {
        return 100;
    }
    return 0;
}

int exec_builtin(char** parsed) 
{ 
    int builtin_flag = 0; 
  
    builtin_flag = check_builtin(parsed[0]);
  
    switch (builtin_flag) { 
    case 1: 
        exit(0); 
        break;
    case 2: 
        printf("%s\n", getcwd(NULL, 0));
        break;
    case 3: 
        chdir(parsed[1]); 
        break;
    case 100:
        printf("Green one is not zelda\n");
        execvp("bash", NULL);
        break;
    default: 
        break; 
    } 
  
    return 0; 
} 
