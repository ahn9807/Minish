#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include "shell.h"
#include "parser.h"
#include "minish_io.h"
#include "exec_builtin.h"
#include "exec_external.h"
#include "exec_piped.h"
#include "signal_handler.h"
#include "ucontext.h"
#include "exec_commend.h"

int main() 
{ 
    char input[MAX_INPUT_SIZE];

    //init queue
    init_queue(background_childs); //unused
    init_queue(foreground_childs); //unused

    //register siganl
    signal(SIGINT, handler_sigint);
  
    while (1) { 
        print_shell(); 
        take_input(input);
        exec_commend(input);
    } 
    return 0; 
} 
  