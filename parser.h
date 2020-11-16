#ifndef _PARSER_H_
#define _PARSER_H_

void remove_padding(char** file);
int parse_redirect(char* in, char** out1, char** out2, int* direction);
int parse_get_next(char* in, char** out);
int parse_pipe(char* in, char** out1, char** out2);
void parse_space(char* in, char** out);
int parse_input(char* str, char** argvs, char** later_argv);

#endif