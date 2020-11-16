#include <stdio.h>
#include <unistd.h>
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

        //remove_padding(argv_prev);
        exec_commend(argv_prev);
        exit(0);
    } 
    else
    {
        wait(NULL);

        pid_t childpid_piped;

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

            //remove_padding(argv_next);
            exec_commend(argv_next);
            exit(0);
        } else {
            wait(NULL);
            print_shell();
        }
    }

    return;
} 