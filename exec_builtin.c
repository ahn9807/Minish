#include "exec_builtin.h"
#include "exec_commend.h"
#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
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
    if(!strcmp("help", input)) {
        return 4;
    }
    if(!strcmp("cap", input)) {
        return 100;
    }
    if(!strcmp("path", input)) {
        return 5;
    }
    if(!strcmp("status", input)) {
        return 6;
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
    case 5:
        if(parsed[1] != NULL && parsed[2] != NULL) {
            if(setenv(parsed[1], parsed[2], 1) != 0) {
                printf("minish: setting PATH variable is failed\n");
            }
        } else if(parsed[1] != NULL) {
            printf("usage: path_name path_value\n");
        }
        printf("PATH :%s\n",(getenv("PATH")!=NULL)? getenv("PATH") : "getenv returned NULL");
        break;
    case 6:
        printf("exit status was %d\n", prev_child_status);
        break;
    case 4:
        printf(" \
MINISH Help\n \
These shell commands are defined internally.  Type `help' to see this list.\n\n \
quit, pwd, cd ,help, path, status(not working correctly), cap\n \
");
        break;
    case 100:
        printf("Green one is not zelda\n");
        exec_commend("bash");
        break;
    default: 
        break; 
    } 
  
    return 0; 
} 
