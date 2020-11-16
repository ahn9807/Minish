#include <stdio.h>
#include "exec_external.h"
#include "shell.h"
#include <unistd.h>

void exec_external(char** argv) 
{ 
    pid_t child_process_pid = fork();

    if(child_process_pid == -1) {
        printf("Minish internal error - Could not fork child process\n");
        exit(-1);
    }

    if(child_process_pid == 0) {
        if(execvp(argv[0], argv) == -1) {
            printf("Minish internal error - Could not make execv child process [%s]\n", argv[0]);
        }
    } else {
        wait(NULL);
        current_child = -1;
    }
} 