#include <stdio.h>
#include "exec_commend.h"
#include "exec_piped.h"
#include "exec_redirected.h"
#include "parser.h"
#include "minish_io.h"
#include "shell.h"

int exec_commend(char* in) {
    char* argv_in[MAX_INPUT_SIZE]; 
    char* argv_later[MAX_INPUT_SIZE]; 
    int shell_execute_mode = 0;

    shell_execute_mode = parse_input(in, argv_in, argv_later); 

    switch (shell_execute_mode)
    {
        case SHELL_EXTERNAL:
            exec_external(argv_in);
            break;
        case SHELL_BUILTINT:
            exec_builtin(argv_in);
            break;
        case SHELL_PIPED:
            exec_piped(argv_in[0], argv_later[0]);
            break;
        case SHELL_REDIRECT_LEFT:
            exec_redirect(argv_in[0], argv_later[0], REDIRECT_LEFT);
            break;
        case SHELL_REDIRECT_RIGHT:
            exec_redirect(argv_in[0], argv_later[0], REDIRECT_RIGHT);
            break;
        case SHELL_NOTING:
            break;
        default:
            printf("Failed to interpretate input...\n");
            break;
    }

    return shell_execute_mode;
}

