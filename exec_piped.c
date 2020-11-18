#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "shell.h"
#include "exec_piped.h"
#include "exec_external.h"
#include "exec_commend.h"
#include "exec_builtin.h"
#include "minish_io.h"
#include "parser.h"

void exec_piped(char* argv_prev, char* argv_next)
{ 
    //fd 0 is read and 1 is write
    int fd[2];
    pid_t childpid;
    pid_t childpid_piped;

    pipe(fd);

    if((childpid = fork()) == -1)
    {
        printf("Minish Internal error failed to fork child process\n");
        exit(1);
    }

    if(childpid == 0)
    {
        close(fd[0]);
        dup2(fd[1], STDOUT_FILENO);
        close(fd[1]);

        char* argvs[MAX_INPUT_SIZE];

        parse_space(argv_prev, argvs);
        //remove_padding(argv_prev);
        if(execvp(argvs[0], argvs) == -1) {
            fprintf(stderr, "Minish internal error - Could not make execv child process [%s]\n", argvs[0]);
            exit(0);
        }
    } 
    else
    {
        waitpid(childpid, &prev_child_status, 0);

        if((childpid_piped = fork()) == -1)
        {
            printf("Minish Internal error failed to fork child process\n");
            exit(1);
        }

        if(childpid_piped == 0)
        {
            close(fd[1]);
            dup2(fd[0], STDIN_FILENO);
            close(fd[0]);

            char* argvs[MAX_INPUT_SIZE];

            parse_space(argv_next, argvs);
            //remove_padding(argv_prev);
            if(execvp(argvs[0], argvs) == -1) {
                fprintf(stderr, "Minish internal error - Could not make execv child process [%s]\n", argvs[0]);
                exit(0);
            }
        } else {
            waitpid(childpid_piped, &prev_child_status, 0);
            fflush(stdout);
        }
    }

    return;
} 