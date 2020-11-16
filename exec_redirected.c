#include <stdio.h>
#include <unistd.h>
#include "shell.h"
#include "exec_redirected.h"
#include "exec_external.h"
#include "exec_commend.h"
#include "exec_builtin.h"
#include "minish_io.h"
#include "parser.h"

void exec_redirect(char* argv_prev, char* argv_next, int direction)
{ 
    pid_t child_process_pid = fork();

    if(child_process_pid == -1) {
        printf("Minish internal error - Could not fork child process\n");
        exit(-1);
    }

    if(child_process_pid == 0) {
        if(direction == REDIRECT_RIGHT) {

            remove_padding(&argv_next);
            printf("%s\n", argv_next);
                fflush(stdout);
            FILE* file_fp = fopen(argv_next, "w+");
            dup2(fileno(file_fp), STDOUT_FILENO);
            exec_commend(argv_prev);
            fclose(file_fp);
        } else {
            remove_padding(&argv_next);
            printf("%s\n", argv_next);
            fflush(stdout);
            FILE* file_fp = fopen(argv_next, "r");
            if(file_fp == NULL) {
                printf("minish: %s: No such file or directory\n", argv_next);
                return;
            }
            dup2(fileno(file_fp), STDIN_FILENO);
            exec_commend(argv_prev);
            fclose(file_fp);
        }

        exit(0);
    } else {
        wait();
    }


    return;
} 