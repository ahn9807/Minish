#ifndef _EXEC_REDIRECTED_H_
#define _EXEC_REDIRECTED_H_

typedef enum {
    REDIRECT_LEFT,
    REDIRECT_RIGHT,
} redirect_direction_t;

void exec_redirect(char* argv_prev, char* argv_next, int direction);

#endif