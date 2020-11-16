#include "parser.h"
#include "exec_builtin.h"
#include "exec_redirected.h"
#include "shell.h"
#include <stdio.h>
#include <string.h>

int parse_pipe(char* in, char** out1, char** out2) 
{ 
    out1[0] = strsep(&in, "|"); 
    out2[0] = in;

    if (out2[0] == NULL) {
        return 0;
    } else {
        return 1;
    }
} 

int parse_redirect(char* in, char** out1, char** out2, int* direction) 
{ 
    out1[0] = strsep(&in, ">"); 
    out2[0] = in;

    if (out2[0] == NULL) {
        char* temp = out1[0];
        out1[0] = strsep(&temp, "<");
        out2[0] = temp;

        if(out2[0] == NULL) {
            return 0;
        } else {
            *direction =  REDIRECT_LEFT;
            return 1;
        }
    } else {
        *direction = REDIRECT_RIGHT;
        return 1;
    }
} 

int parse_get_next(char* in, char** out) {
    char* out1 = strsep(&in, "|><"); 
    out[0] = strsep(&in, "|><");

    if (out[0] == NULL) {
        return 0;
    } else {
        return 1;
    }
}

void remove_padding(char** file) {
    int index = 0;
    while((*file)[index] == ' ') {
        index++;
        (*file)++;
    }

    index = strlen(*file) -1;
    while((*file)[index] == ' ') {
        (*file)[index] = '\0';
        index--;
    }
}

void parse_space(char* in, char** out) 
{ 
    int index = 0;
    char* modified_in = in;

    while(modified_in[index] == ' ') {
        index++;
        modified_in++;
    }

    index = 0;
  
    out[0] = strsep(&modified_in, " ");

    while (out[index++] != NULL)
    {
        out[index] = strsep(&modified_in, " ");
        
        if(out[index] == NULL) {
            break;
        }

        if(strlen(out[index]) == 0) {
            index -= 1;
        }
    }
} 

/**
 * return argvs of input
 * if piped or redirected, 
 * return two segements
 */
int parse_input(char* str, char** argv, char** later_argv) 
{ 
    if(strlen(str) == 0) {
        return SHELL_NOTING;
    }

    char* out1;
    char* out2;
    int redirect_direction = 0;

    if(parse_pipe(str, &out1, &out2)) {
        argv[0] = out1;
        later_argv[0] = out2;

        return SHELL_PIPED;
    } // parse redirect

    if(parse_redirect(str, &out1, &out2, &redirect_direction)) {
        argv[0] = out1;
        later_argv[0] = out2;

        return redirect_direction == REDIRECT_LEFT ?  SHELL_REDIRECT_LEFT : SHELL_REDIRECT_RIGHT;
    }

    parse_space(str, argv);

    if(check_builtin(argv[0])) {
        return SHELL_BUILTINT;
    } else {
        return SHELL_EXTERNAL;
    }
} 
  