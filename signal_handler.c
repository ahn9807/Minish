#include "signal_handler.h"
#include "shell.h"
#include "minish_io.h"
#include <signal.h>
#include <stdio.h>
#include <unistd.h>

int print_last = 0;

void handler_sigint() {
    printf("\n");
    fflush(stdout);
}