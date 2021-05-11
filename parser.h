#ifndef _PARSER_H_
#define _PARSER_H_

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

void shell_free_args(char **argv);
char** shell_process_line(int *argc);

#endif
