#ifndef _SHELL_H_
#define _SHELL_H_

#include "queue.h"
#include <ucontext.h>
#include <setjmp.h>

#define MAX_INPUT_SIZE 128

enum shell_mode {
    SHELL_BUILTINT,
    SHELL_EXTERNAL,
    SHELL_PIPED,
    SHELL_REDIRECT_RIGHT,
    SHELL_REDIRECT_LEFT,
    SHELL_INVALID,
    SHELL_NOTING,
};

static int current_child = -1;
static jmp_buf main_context;

typedef struct _child_info {
    int pid;
} child_info_t; //unused

queue_t* foreground_childs; //unused
queue_t* background_childs; //unused

#endif